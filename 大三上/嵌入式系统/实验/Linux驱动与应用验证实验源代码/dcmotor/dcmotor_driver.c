//------------------------------------直流电机（位于底板上）设备驱动程序--------------------------
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h> 
#include <linux/fs.h> 
#include <linux/slab.h> 
#include <linux/delay.h> 
#include <linux/i2c.h>
#include <linux/gpio.h> 
#include <linux/module.h>
#include <linux/io.h> 
#include <linux/ioctl.h>
#include <linux/platform_device.h> 
#include <linux/of.h>
#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/dmi.h>
#include <linux/firmware.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/input/touchscreen.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/regulator/consumer.h>
#include <linux/slab.h>
#include <linux/acpi.h>
#include <asm/unaligned.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "dc_motor"

#ifdef DEBUG
#define LOGD(fmt, args...) \
{printk(KERN_INFO "<<-Device:%s->> line %d at %s ", DEVICE_NAME, __LINE__, __func__); \
	printk(KERN_INFO fmt, ##args);}
#else
#define LOGD(fmt, args...) (void)(0);
#endif

#define LOGI(fmt, args...) {printk(KERN_INFO fmt, ##args);}
#define LOGE(fmt, args...) {printk(KERN_ERR fmt, ##args);}
#define IOCTL_MAGIC 	'D'
#define DC_MOTOR_ON 	_IO(IOCTL_MAGIC, 0) 
#define DC_MOTOR_OFF 	_IO(IOCTL_MAGIC, 1) 
#define DC_MOTOR_DIR	_IOW(IOCTL_MAGIC, 2, int)	
#define DC_MOTOR_RATE	_IOW(IOCTL_MAGIC, 3, int)
#define DC_MOTOR_RATE_1 _IOW(IOCTL_MAGIC, 4, int)
#define T1000US ((1000 * 1000) / 2)

enum {
	DEVICE_OFF,
	DEVICE_ON,
};

enum {
	CTR_DIR_PIN = 0,
	CTR_FAN_ROTATION,
};

typedef struct {
	char direction;  //0-forward   1-reverse -1-quiet
	unsigned short speed; 
	unsigned short speed1; 
} motor_para;

struct dc_motor {
	struct i2c_client *client;
	struct hrtimer timer;	
	int old_value;
	int rate_counter;
	int timer_counter;
	int rate;
	struct miscdevice misc;
	struct delayed_work work;
	motor_para dc_motor_para; //contains direction and speed
	struct gpio_desc *gpiod[2];
};

int open_flag = 0;
int dir = 0;
const unsigned char speed_level[2][6] = {{0, 1, 2, 3, 4, 5}, {5,4,3,2,1,0}};

static void ctrl_fan_rotation(struct dc_motor *dev,int val) 
{
	gpiod_set_value( dev->gpiod[0], val);
	if (val == DEVICE_ON) 
		dir = 1;
	else 
		dir = 0;
}

static void dev_reset(struct dc_motor *motor_dev,int nr, int state)
{
	gpiod_direction_output(motor_dev->gpiod[nr], state);
}

static void dc_motor_set_rate(struct dc_motor *dev, unsigned char rate)
{
	unsigned char buf[2] = {(rate >> 4) &0x0f, (rate << 4) &0xf0};
	int ret = 0, retry_val = 0;
	struct i2c_msg msg[] = 
	{
		{dev->client->addr, 0, sizeof(buf), buf},
	};
	LOGD("buf[0] = %02x, buf[1] = %02x\n", buf[0], buf[1]);
retry:
	ret = i2c_transfer(dev->client->adapter, msg, ARRAY_SIZE(msg));
	if (ret != 1) 
	{
		if (retry_val++ ==5)
			return;
		goto retry;
	}
}

static long dev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct dc_motor *dev = container_of(filp->private_data, struct dc_motor, misc);
	int data = -1;
	if (_IOC_TYPE(cmd) != IOCTL_MAGIC)
		return -ENOTTY;
	if (_IOC_NR(cmd) > 4) 
	{
		return -ENOTTY;
	}
	if (_IOC_DIR(cmd) == _IOC_WRITE) 
	{
		if (copy_from_user((void*)&data, (void *)arg, sizeof(data)))
			return -EFAULT;
	}
	switch (cmd) 
	{
		case DC_MOTOR_ON:
			if (!open_flag) 
			{
				dc_motor_set_rate(dev, 0x50);
				open_flag = 1;
				LOGD("<%s> open!!!\n", DEVICE_NAME);
			}
			break;
		case DC_MOTOR_OFF:
			dc_motor_set_rate(dev, 0x00);
			ctrl_fan_rotation(dev,DEVICE_OFF);
			open_flag = 0;
			LOGD("<%s> close!!!\n", DEVICE_NAME);
			break;
		case DC_MOTOR_DIR:
			if (open_flag) 
			{
				LOGD("<%s> change dir-->%s\n", DEVICE_NAME, data == 1 ? "foreward" : "reverse");
				ctrl_fan_rotation(dev,data);
			}
			break;
		case DC_MOTOR_RATE:
			if (open_flag) 
			{
				if (copy_from_user(&data, (void *)arg, 4))
					return -EFAULT;
				dc_motor_set_rate(dev, 0x00);
				ctrl_fan_rotation(dev,DEVICE_OFF);
				if (dir == 0)
					dc_motor_set_rate(dev, speed_level[0][data]*25+40); 
				else 
					dc_motor_set_rate(dev, (speed_level[1][data]*20));
			}
			break;
		case DC_MOTOR_RATE_1:
			if (open_flag) 
			{
				if (copy_from_user(&data, (void *)arg, 1))
					return -EFAULT;
				printk(KERN_ERR"%s:motor change rate1=>%d!!!\n",__func__, data);
				dc_motor_set_rate(dev, data);
			}
			break;
		default:
			break;
	}
	return 0;
}

static int dev_open(struct inode *inode, struct file *filp)
{
	struct dc_motor *dev_open = container_of(filp->private_data, struct dc_motor, misc);
	dev_open->gpiod[0] = devm_gpiod_get_index_optional(&dev_open->client->dev, "dc_motor_pin1", 0, GPIOD_OUT_HIGH);
	if (IS_ERR(dev_open->gpiod[0])) 
	{
		int ret = PTR_ERR(dev_open->gpiod[0]);
		dev_err(&dev_open->client->dev, "devm_gpiod_get_index_optional() failed ret: %d.\n", ret);
		return 1;
	}
	dev_open->gpiod[1] = devm_gpiod_get_index_optional(&dev_open->client->dev, "dc_motor_pin2", 0, GPIOD_OUT_HIGH);
	if (IS_ERR(dev_open->gpiod[1])) 
	{
		int ret = PTR_ERR(dev_open->gpiod[1]);
		dev_err(&dev_open->client->dev, "devm_gpiod_get_index_optional() failed ret: %d.\n", ret);
		return 1;
	}
	dc_motor_set_rate(dev_open, 0x00);
	ctrl_fan_rotation(dev_open,DEVICE_OFF);
	hrtimer_start(&dev_open->timer, ktime_set(0, T1000US), HRTIMER_MODE_REL);
	return 0;
}

static int dev_release(struct inode *inode, struct file *filp)
{
	struct dc_motor *dev = container_of(filp->private_data, struct dc_motor, misc);
	hrtimer_cancel(&dev->timer);
	dc_motor_set_rate(dev, 0x00);
	open_flag = 0;
	dev_reset(dev,0, DEVICE_OFF);
	dev_reset(dev,1, DEVICE_OFF);
	devm_gpiod_put(&dev->client->dev,dev->gpiod[0]);
	devm_gpiod_put(&dev->client->dev,dev->gpiod[1]);
	return 0;
}

ssize_t dc_motor_read(struct file *filp, char __user *buf, size_t len, loff_t * off)
{
	struct dc_motor *motor_dev = container_of(filp->private_data, struct dc_motor, misc);
	if (copy_to_user(buf, (void *)&(motor_dev->dc_motor_para), sizeof(motor_para)))
		return -EFAULT;
	return sizeof(motor_para);
}

static struct file_operations dev_fops = {
	.owner		= THIS_MODULE,
	.open		= dev_open,
	.release		= dev_release,
	.read 		= dc_motor_read,
	.unlocked_ioctl	= dev_ioctl,
};

int gpio_d17_get_value(struct dc_motor *motor_dev)
{
	int data = 0;
	gpiod_direction_input(motor_dev->gpiod[1]);
	data =  gpiod_get_value(motor_dev->gpiod[1]);
	return data == 0 ? 0 : 1;
}

static enum hrtimer_restart timer_func(struct hrtimer *timer)
{
	int val = 0;
	struct dc_motor *motor_dev = container_of(timer, struct dc_motor, timer);
	val = gpio_d17_get_value(motor_dev);
	if (val && !motor_dev->old_value) 
	{
		motor_dev->rate_counter++;
	}
	if (motor_dev->timer_counter == 1000) 
	{
		motor_dev->rate = motor_dev->rate_counter / 4;
		motor_dev->rate_counter = 0;
		motor_dev->timer_counter= 0;
		(motor_dev->dc_motor_para).speed = motor_dev->rate;
	}
	hrtimer_start(&motor_dev->timer, ktime_set(0, T1000US), HRTIMER_MODE_REL);
	motor_dev->timer_counter++;
	motor_dev->old_value = val;
	return HRTIMER_NORESTART;
}

static int dev_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int err = -1;
	struct dc_motor *dev;
	LOGD("<%s> probe\n", DEVICE_NAME);
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;
	dev = kzalloc(sizeof(struct dc_motor), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;
	dev->misc.minor = MISC_DYNAMIC_MINOR;
	dev->misc.name = DEVICE_NAME;
	dev->misc.fops = &dev_fops;
	dev->client = client;
	i2c_set_clientdata(client, dev);
	hrtimer_init(&dev->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	dev->timer.function = timer_func;
	err = misc_register(&dev->misc);
	if (err)
		goto err;
	LOGD("<%s-minor(%d)> miscdevice register successfully\n", DEVICE_NAME, dev->misc.minor);
	return 0;	
err:
	kfree(dev);
	return err;
}

static int dev_remove(struct i2c_client *client)
{
	struct dc_motor *dev = i2c_get_clientdata(client);	
	misc_deregister(&dev->misc);
	i2c_set_clientdata(client, NULL);
	kfree(dev);
	return 0;
}

static const struct i2c_device_id dev_id[] = {
	{DEVICE_NAME, 0},
	{ },
};

MODULE_DEVICE_TABLE(i2c, dev_id);

static const struct of_device_id of_my_compatible_match[] = {
	{ .compatible = "dc_motor", },
	{},
};

MODULE_DEVICE_TABLE(of, of_my_compatible_match);

static struct i2c_driver dc_motor_driver = {
	.driver		= {
		.name	= DEVICE_NAME,
		.owner	= THIS_MODULE,
		.of_match_table = of_my_compatible_match,
	},
	.probe		= dev_probe,
	.remove		= dev_remove,
	.id_table		= dev_id,
};

static int __init i2c_module_init(void)
{
	return i2c_add_driver(&dc_motor_driver);
}

module_init(i2c_module_init);

static void __exit i2c_module_exit(void)
{
	i2c_del_driver(&dc_motor_driver);
	LOGI("<%s> exit successfully\n", DEVICE_NAME);
}

module_exit(i2c_module_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Driver for FSD1's dc_motor");
MODULE_AUTHOR("Farsight yanfa <support@farsight.com.cn>");
MODULE_VERSION("V1.0");
