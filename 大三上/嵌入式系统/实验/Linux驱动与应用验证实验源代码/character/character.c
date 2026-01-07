//------------------------------------字符设备驱动程序--------------------------
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
#include <linux/cdev.h>
#include <linux/of_gpio.h>
#include <asm/uaccess.h>

struct cdev* cdev;		//字符设备结构体，Linux管理字符设备
struct class* class;		//类结构体
struct device* dev;		//保存设备基本信息的结构体
dev_t devnum;		//设备编号

static int farsight_open(struct inode *inode, struct file *file) 		//打开设备文件
{
	printk(KERN_NOTICE"This is driver : open function\n");
	return 0;
}

static ssize_t farsight_read(struct file *file, char *buf, size_t count, loff_t* f_pos)		//读设备文件
{
	char msg[20] = "abcdefg";
	int ret;
	printk(KERN_NOTICE"This is driver : read function\n");
	ret = copy_to_user(buf,msg,count);
	return count;
}

static ssize_t farsight_write(struct file *filp, const char *buffer, size_t count, loff_t *ppos)		//写设备文件
{
	char str[20];
	printk(KERN_NOTICE"This is driver : write function\n");
	memset(str,0,20);
	if(copy_from_user(str, buffer, count))
	{
		return -EINVAL;
	}
	printk(KERN_NOTICE"get APP buf is : %s\n",str); 
	return count;
}

static int farsight_close(struct inode *inode, struct file *file) 		//关闭设备文件
{
	printk(KERN_NOTICE"This is driver : close function\n");
	return 0;
}

static long farsight_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)		//设备文件的I/O控制
{
	switch(cmd) 
	{
		case 'a':
			printk(KERN_NOTICE"This is driver : ioctl a function\n");
            			break;
        		case 'b':
			printk(KERN_NOTICE"This is driver : ioctl b function\n");
            			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static struct file_operations farsight_ops = 		//设备文件结构体
{
	.owner		= THIS_MODULE,
	.open		= farsight_open,
	.read           	= farsight_read,
	.write          	= farsight_write,
	.release		= farsight_close, 
	.unlocked_ioctl	= farsight_ioctl,
};

int register_char(void)		//注册设备文件
{
	int ret_1;
	cdev_init(cdev,&farsight_ops);					//初始化字符设备对象
	cdev->owner = THIS_MODULE; 					//设置字符设备所属模块
	ret_1 = alloc_chrdev_region(&devnum,0,1,"character_device"); 		//申请设备号
	if(ret_1<0)
	{
		goto out_err_0;
	}
	ret_1 = cdev_add(cdev, devnum, 1);					//添加字符设备
	if (ret_1 < 0) 
	{
		goto out_err_1;
	}	
	class = class_create(THIS_MODULE,"character_class");			//创建character类
	if (IS_ERR(class)) 
	{
		ret_1 = PTR_ERR(class);
		goto out_err_2;	
	}
	dev = device_create(class,NULL,devnum,NULL,"character_device");		//创建字符设备节点
	if (IS_ERR(dev)) 
	{
		ret_1 = PTR_ERR(dev);
		goto out_err_3;	
	}
	return 0;
out_err_3:
	device_del(dev);
	class_destroy(class);
out_err_2:
	cdev_del(cdev);
out_err_1:
	unregister_chrdev_region(devnum,1);
out_err_0:
	kfree(cdev);
	return ret_1;
} 

static int __init farsight_dev_init(void) 		//驱动模块入口
{
	cdev = kmalloc(sizeof(struct cdev), GFP_KERNEL);	//注册字符设备
	return register_char();
}

static void __exit farsight_dev_exit(void) 	//驱动模块出口
{
	device_del(dev);
	class_destroy(class);
	cdev_del(cdev);
	kfree(cdev);
	unregister_chrdev_region(devnum,1);
}

module_init(farsight_dev_init);		//模块初始化
module_exit(farsight_dev_exit);		//模块退出

MODULE_LICENSE("GPL");			//许可证
MODULE_AUTHOR("FARSIGHT");		//作者
MODULE_DESCRIPTION("LED Driver");		//描述信息
