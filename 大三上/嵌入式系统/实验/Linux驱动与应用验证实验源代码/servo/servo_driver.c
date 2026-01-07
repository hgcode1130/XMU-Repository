//------------------------------------陀机（位于底板上）设备驱动程序--------------------------
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/of_gpio.h>
#include <asm/uaccess.h>

#define DEVICE_NAME	"servo"
#define DRIVER_NAME 	"SERVO" 

#define IOCTL_MAGIC 	'S'
#define ROTATE_0 		_IO(IOCTL_MAGIC, 0) 
#define ROTATE_30 	_IO(IOCTL_MAGIC, 1) 
#define ROTATE_60 	_IO(IOCTL_MAGIC, 2) 
#define ROTATE_90 	_IO(IOCTL_MAGIC, 3) 
#define ROTATE_120 	_IO(IOCTL_MAGIC, 4) 
#define ROTATE_150 	_IO(IOCTL_MAGIC, 5) 
#define SET_ANGLE	_IO(IOCTL_MAGIC, 6)

struct SERVO{
	struct hrtimer servo_timer_high;	//高精度定时器纳秒级
	int val;				//舵机状态
	uint32_t SERVO_GPIO;		//GPIO
	unsigned int msec;			//高电平时间微秒
	struct device_node *np;
	struct platform_device *pdev;
};

struct SERVO *servo;

static enum hrtimer_restart servo_timeout_high(struct hrtimer *timer)
{
	if(servo->val)
	{
		servo->val = 0;
		gpio_set_value(servo->SERVO_GPIO,servo->val);
		hrtimer_forward_now(&servo->servo_timer_high,ktime_set(0,(20000000-500000-(servo->msec*1000))));
	}
	else
	{
		servo->val = 1;
		gpio_set_value(servo->SERVO_GPIO,servo->val);
		hrtimer_forward_now(&servo->servo_timer_high,ktime_set(0,500000+(servo->msec*1000)));
	}
	return HRTIMER_RESTART;
}

static int rk3399_servo_open(struct inode *inode, struct file *file) 
{
	int ret;	
	servo->SERVO_GPIO = of_get_gpio(servo->np, 0);
	if (servo->SERVO_GPIO == -EPROBE_DEFER)
        		return servo->SERVO_GPIO;
	if (servo->SERVO_GPIO < 0) 
	{
    		printk("error acquiring servo gpio: %d\n", servo->SERVO_GPIO);
        		return servo->SERVO_GPIO;
    	}
    	ret = devm_gpio_request_one(&servo->pdev->dev, servo->SERVO_GPIO, 0, "servo_gpio");
    	if(ret) 
	{
    		dev_err(&(servo->pdev->dev), "error requesting servo gpio: %d\n", ret);
        		return ret;
    	}
	hrtimer_start(&servo->servo_timer_high, ktime_set(0,500000), HRTIMER_MODE_REL);
	return 0;
}


static int rk3399_servo_close(struct inode *inode, struct file *file) 
{
	gpio_free(servo->SERVO_GPIO);	
	hrtimer_cancel(&(servo->servo_timer_high));
	return 0;
}

static long rk3399_servo_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	if (_IOC_TYPE(cmd) != IOCTL_MAGIC)		//判断魔数是否一致
		return -ENOTTY;
	if (_IOC_NR(cmd) > 6)			//判断基数是否超出范围
		return -ENOTTY;
	switch(cmd) 
	{
		case SET_ANGLE:
			if(arg>=0 && arg<=180)
				servo->msec =(11 * arg); 	// 2000/180
			servo->val = 1;
			gpio_set_value(servo->SERVO_GPIO,servo->val);
			hrtimer_forward_now(&servo->servo_timer_high,ktime_set(0,500000+(servo->msec*1000)));
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static struct file_operations rk3399_servo_ops = {
	.owner		= THIS_MODULE,
	.open		= rk3399_servo_open,
	.release		= rk3399_servo_close, 
	.unlocked_ioctl	= rk3399_servo_ioctl,
};

static struct miscdevice rk3399_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &rk3399_servo_ops,
};

static int rk3399_servo_probe(struct platform_device *pdev)
{
	int ret;
	servo = kzalloc(sizeof(*servo), GFP_KERNEL);
	servo->np = pdev->dev.of_node;
	servo->pdev = pdev;
	hrtimer_init(&servo->servo_timer_high, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	servo->servo_timer_high.function = servo_timeout_high;
	ret = misc_register(&rk3399_misc_dev);
	return 0;
}

static int rk3399_servo_remove (struct platform_device *pdev)
{
	misc_deregister(&rk3399_misc_dev);
	hrtimer_cancel(&(servo->servo_timer_high));
	kfree(servo);
	return 0;
}

static int rk3399_servo_suspend (struct platform_device *pdev, pm_message_t state)
{
	return 0;
}

static int rk3399_servo_resume (struct platform_device *pdev)
{
	return 0;
}

static const struct of_device_id servo_of_match[] = {
        { .compatible = "fs_rk3399_servo" },
        {}
};

MODULE_DEVICE_TABLE(of, servo_of_match);

static struct platform_driver rk3399_servo_driver = {
	.probe = rk3399_servo_probe,
	.remove = rk3399_servo_remove,
	.suspend = rk3399_servo_suspend,
	.resume = rk3399_servo_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(servo_of_match),
	},
};

static int __init rk3399_servo_dev_init(void) 
{
	return platform_driver_register(&rk3399_servo_driver);
}

static void __exit rk3399_servo_dev_exit(void) 
{
	platform_driver_unregister(&rk3399_servo_driver);
}

module_init(rk3399_servo_dev_init);
module_exit(rk3399_servo_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("TOPEET Inc.");
MODULE_DESCRIPTION("fs rk3399 servo Driver");
