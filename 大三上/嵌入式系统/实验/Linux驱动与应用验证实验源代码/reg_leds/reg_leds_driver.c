//------------------------------------3个LED灯的设备驱动程序--------------------------
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
#include <linux/of.h>
#include <linux/cdev.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define LED1_ON    _IO('L',11)
#define LED1_OFF   _IO('L',10)
#define LED2_ON    _IO('L',21)
#define LED2_OFF   _IO('L',20)
#define LED3_ON    _IO('L',31)
#define LED3_OFF   _IO('L',30)

#define DEVICE_NAME	"leds_ctl"
#define DRIVER_NAME 	"leds_ctl"

#define GPIO_DR 0x00	//数据寄存器
#define GPIO_DDR 0x04	//方向寄存器

struct cdev* cdev;
struct class* class;
struct device* dev;
dev_t devnum;

void __iomem *gpio0_swporta_base = NULL;  	//gpio0基地址
void __iomem *gpio4_swporta_base = NULL;  	//gpio4基地址
void __iomem *pclk_gpio0_en = NULL;  
void __iomem *pclk_gpio4_en = NULL;  

static int farsight_led_open(struct inode *inode, struct file *file) 		//打开设备文件
{
	return 0;
}

static int farsight_led_close(struct inode *inode, struct file *file) 		//关闭设备文件
{
	return 0;
}

//ioctl函数
//功能：控制3个LED开关
//参数1：文件指针,应用层文件描述符
//参数2：应用层下发控制指令
//参数3：用户空间传递的数据
static long farsight_led_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)	
{
	switch(cmd) 
	{
		case LED1_ON:
			writel((readl((gpio4_swporta_base + GPIO_DR)) | 0x1<<22) , (gpio4_swporta_base + GPIO_DR)); 			//DR置1，灯亮
            			break;
        		case LED1_OFF:
			writel((readl((gpio4_swporta_base + GPIO_DR)) & ~(0x1<<22)) , (gpio4_swporta_base + GPIO_DR)); 		//DR置0，灯灭
			break;
		case LED2_ON:
			writel((readl((gpio0_swporta_base + GPIO_DR)) | 0x1<<2) , (gpio0_swporta_base + GPIO_DR)); 
            			break;
        		case LED2_OFF:
			writel((readl((gpio0_swporta_base + GPIO_DR)) & ~(0x1<<2)) , (gpio0_swporta_base + GPIO_DR)); 
			break;
		case LED3_ON:
			writel((readl((gpio0_swporta_base + GPIO_DR)) | 0x1<<12) , (gpio0_swporta_base + GPIO_DR)); 
            			break;
        		case LED3_OFF:
			writel((readl((gpio0_swporta_base + GPIO_DR)) & ~(0x1<<12)) , (gpio0_swporta_base + GPIO_DR)); 
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static struct file_operations farsight_led_ops = {		//设备文件结构体
	.owner		= THIS_MODULE,
	.open		= farsight_led_open,
	.release		= farsight_led_close, 
	.unlocked_ioctl	= farsight_led_ioctl,
};

static int __init farsight_led_dev_init(void) 		//设备文件初始化
{
	int ret_1;
	gpio0_swporta_base = ioremap(0xFF720000,8);							//映射GPIO0的基地址	
	gpio4_swporta_base = ioremap(0xFF790000,8);							//映射GPIO4的基地址
	pclk_gpio0_en = ioremap((0xFF750000+0x104),4);						//映射GPIO0的时钟寄存器地址
	pclk_gpio4_en = ioremap((0xFF760000+0x37c),4);						//映射GPIO4的时钟寄存器地址
	writel(((readl(pclk_gpio0_en) & ~(0x1<<3)) | 0x1<<19) , pclk_gpio0_en); 				//使能GPIO0的时钟	
	writel(((readl(pclk_gpio4_en) & ~(0x1<<5)) | 0x1<<21) , pclk_gpio4_en); 				//使能GPIO4的时钟	
	writel(readl((gpio4_swporta_base + GPIO_DDR)) | 0x1<<22, gpio4_swporta_base + GPIO_DDR);		//设置GPIO4的DDR的相应位为输出模式（LED1）
	writel(readl((gpio0_swporta_base + GPIO_DDR)) | 0x1<<2, gpio0_swporta_base + GPIO_DDR);		//设置GPIO0的DDR的相应位为输出模式（LED2）
	writel(readl((gpio0_swporta_base + GPIO_DDR)) | 0x1<<12, gpio0_swporta_base + GPIO_DDR);		//设置GPIO0的DDR的相应位为输出模式（LED3）
	cdev = kmalloc(sizeof(struct cdev), GFP_KERNEL);
	cdev_init(cdev,&farsight_led_ops);					//初始化字符设备对象
	cdev->owner = THIS_MODULE; 					//设置字符设备所属模块
	ret_1 = alloc_chrdev_region(&devnum,0,1,"leds_reg_device"); 		//申请设备号
	if(ret_1<0)
	{
		goto out_err_0;
	}
	ret_1 = cdev_add(cdev, devnum, 1);					//添加字符设备
	if (ret_1 < 0) 
	{
		goto out_err_1;
	}	
	class = class_create(THIS_MODULE,"leds_reg_class");			//创建character类
	if (IS_ERR(class)) 
	{
		ret_1 = PTR_ERR(class);
		goto out_err_2;	
	}
	dev = device_create(class,NULL,devnum,NULL,"leds_reg_device");		//创建字符设备节点
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

static void __exit farsight_led_dev_exit(void) 		//设备文件退出
{
	iounmap(gpio0_swporta_base);
	iounmap(gpio4_swporta_base);
	iounmap(pclk_gpio0_en);
	iounmap(pclk_gpio4_en);
	device_del(dev);
	class_destroy(class);
	cdev_del(cdev);
	kfree(cdev);
	unregister_chrdev_region(devnum,1);
}

module_init(farsight_led_dev_init);
module_exit(farsight_led_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FARSIGHT");
MODULE_DESCRIPTION("LED reg Driver");

