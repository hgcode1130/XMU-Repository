//------------------------------------温度传感器（位于MPU开发板上）设备驱动程序--------------------------
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#define LM75_REG_CONF	0x01

static const u8 LM75_REG_TEMP[3] = {
	0x00,				// input 
	0x03,				// max 
	0x02,				// hyst 
};

struct lm75_data 
{
	u16 temp[3]; 
};

static int lm75_major = 300;
static int lm75_minor = 0;
static int number_of_devices = 1;
static dev_t devno = 0;
static struct cdev cdev;
struct class* class;
struct device* dev;
static struct i2c_client *new_client;
struct lm75_data *data;

static int lm75_read_value(struct i2c_client *client)
{
	struct i2c_msg msgs[2];
	int status;
	char buf1[2];
	char buf2[2];
	msgs[0].len = 1;
	msgs[0].addr = client->addr; 				// lm75 设备地址
	msgs[0].flags = 0;					//write
	msgs[0].buf = buf1;
	msgs[0].buf[0] = LM75_REG_TEMP[0];
	msgs[1].len = 2;					//读出的数据
	msgs[1].addr = client->addr;				// lm75 设备地址 
	msgs[1].flags = I2C_M_RD;				//read
	msgs[1].buf = buf2;					//存放返回值的地址。
	status = i2c_transfer(client->adapter, msgs, 2);
	if(status < 0)
		return status;
	return (buf2[0] << 8) | buf2[1];
}

static ssize_t lm75_read(struct file *file, char __user *buff, size_t count, loff_t *offset) 
{
	int status;
	status = lm75_read_value(new_client);
	if(status < 0)
	{
		return status;
	}
	if(copy_to_user(buff, (char *)&status, sizeof(status)))
		return -EFAULT;
	return 0;
}

static int lm75_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int lm75_release(struct inode *inode, struct file *file)
{
	return 0;
}

static struct file_operations lm75_fops = {
	.owner 	= THIS_MODULE,
	.read	= lm75_read,
	.open 	= lm75_open,
	.release	= lm75_release,
};

static int lm75_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret = 0;
	new_client = client;
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA))
		return -EIO;
	data = kzalloc(sizeof(struct lm75_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	i2c_set_clientdata(client, data);
	devno = MKDEV(lm75_major, lm75_minor);
	ret = register_chrdev_region(devno, number_of_devices, "lm75");
	if(ret)
	{
		printk("failed to register device number\n");
		goto err_register_chrdev_region;
	}
	cdev_init(&cdev, &lm75_fops);
	cdev.owner = THIS_MODULE;
	ret = cdev_add(&cdev, devno, number_of_devices);
	if(ret)
	{
		printk("failed to add device\n");
		goto err_cdev_add;
	}
	class = class_create(THIS_MODULE,"lm75_class");
	if (IS_ERR(class)) 
	{
		ret = PTR_ERR(class);
		goto out_err_2;	
	}
	dev = device_create(class,NULL,devno,NULL,"temp");
	if (IS_ERR(dev)) 
	{
		ret = PTR_ERR(dev);
		goto out_err_3;	
	}
	return 0;
out_err_3:
	device_del(dev);
	class_destroy(class);
out_err_2:
	cdev_del(&cdev);
err_cdev_add:
	unregister_chrdev_region(devno, number_of_devices);
err_register_chrdev_region:
	kfree(data);
	return ret;
}

static int lm75_remove(struct i2c_client *client)
{
	cdev_del(&cdev);
	device_del(dev);
	class_destroy(class);
	unregister_chrdev_region(devno, number_of_devices);
	return 0;
}

enum lm75_type {		
	lm75,
	lm75a,
};

static const struct i2c_device_id lm75_ids[] = {
	{ "lm75", lm75, },
	{ "lm75a", lm75a, },
	{}
};

static struct i2c_driver lm75_driver = {
	.driver = {
		.name = "lm75",
	},
	.probe 	= lm75_probe,
	.remove 	= lm75_remove,
	.id_table	= lm75_ids,
};

static int __init s5pc100_lm75_init(void)
{
	return i2c_add_driver(&lm75_driver);
}

static void __exit s5pc100_lm75_exit(void)
{
	i2c_del_driver(&lm75_driver);
}

module_init(s5pc100_lm75_init);
module_exit(s5pc100_lm75_exit);

MODULE_LICENSE ("GPL");
