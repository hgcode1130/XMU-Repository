//------------------------------------呼吸灯（PWM）设备驱动程序--------------------------
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

#define LED1_PERIOD  _IO('L',0)
#define LED1_DUTY    _IO('L',1)
#define LED1_ON      _IO('L',2)
#define LED1_OFF     _IO('L',3)

#define DEVICE_NAME	"leds_pwm_ctl"
#define DRIVER_NAME 	"leds_pwm_ctl"

struct cdev* cdev;
struct class* class;
struct device* dev;

dev_t devnum;

#define PWM_CNT 0x00
#define PWM_PERIOD_HPR 0x04
#define PWM_DUTY_LPR 0x08
#define PWM_CTRL 0x0c

void __iomem *pclk_gpio4_en = NULL;
void __iomem *grf_gpio4c_iomux = NULL;
void __iomem *pwm1 = NULL;

static int farsight_led_open(struct inode *inode, struct file *file) 
{
	return 0;
}

static int farsight_led_close(struct inode *inode, struct file *file) 
{
	return 0;
}

static long farsight_led_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	unsigned int buf;
	switch(cmd) 
	{
		case LED1_PERIOD:
				if(copy_from_user((void *)&buf,(void *)arg,4))
					return -EFAULT;
				writel(buf,(pwm1+PWM_PERIOD_HPR)); 
            				break;
        		case LED1_DUTY:
				if(copy_from_user((void *)&buf,(char*)arg,4))
					return -EFAULT;
				writel(buf,(pwm1+PWM_DUTY_LPR)); 
				break;
        		case LED1_ON:
				printk("4\n");
				writel((readl(pwm1 + PWM_CTRL) | (0x1<<0)),(pwm1 + PWM_CTRL));
				break;
        		case LED1_OFF:
				writel((readl(pwm1 + PWM_CTRL) | (0x0<<0)),(pwm1 + PWM_CTRL));
				break;
		default:
				return -EINVAL;
	}
	return 0;
}

static struct file_operations farsight_pwm_ops = {
	.owner		= THIS_MODULE,
	.open		= farsight_led_open,
	.release		= farsight_led_close, 
	.unlocked_ioctl	= farsight_led_ioctl,
};

static int __init farsight_led_pwm_init(void) 
{
	int ret_1;
	pclk_gpio4_en = ioremap((0xFF760000+0x37c),4);
	grf_gpio4c_iomux = ioremap(0xFF77E028,4);
	pwm1 = ioremap(0xFF420010,4);
//--------------------------------PWM配置-----------------------------------------------	
	writel(((readl(pclk_gpio4_en) | 0x1<<26) & (~(0x1<<10))), pclk_gpio4_en);		//使能GPIO4时钟
	writel(((readl(grf_gpio4c_iomux) | 0x3<<28) | 0x1<<12),grf_gpio4c_iomux);		//设置GPIO4_C6为PWM
	writel((readl(pwm1 + PWM_CTRL) & (~(0x1<<0))),(pwm1 + PWM_CTRL));		//关闭PWM通道
	writel((readl(pwm1 + PWM_CTRL) | (0x0<<9)),(pwm1 + PWM_CTRL));		//选择时钟源
	writel((readl(pwm1 + PWM_CTRL) | (0x1<<12)),(pwm1 + PWM_CTRL));		//设置输入时钟的分频因子，2的1次方
	writel((readl(pwm1 + PWM_CTRL) | (0x1<<16)),(pwm1 + PWM_CTRL));		//设置缩放比例因子,时钟除以2的N次方,这里设置为2的1次方
	writel((readl(pwm1 + PWM_CTRL) | (0x1<<1)),(pwm1 + PWM_CTRL));		//设置连续模式，PWM产生连续波形
	writel((readl(pwm1 + PWM_CTRL) | (0x1<<3)),(pwm1 + PWM_CTRL));		//设置PWM的极性为positive
	writel((readl(pwm1 + PWM_CTRL) & (~(0x1<<5))),(pwm1 + PWM_CTRL));		//输出方式为左对齐
	writel((readl(pwm1 + PWM_CTRL) | (0x1<<0)),(pwm1 + PWM_CTRL));		//使能PWM通道
//-------------------------------创建字符设备-------------------------------------------
	cdev = kmalloc(sizeof(struct cdev), GFP_KERNEL);
	cdev_init(cdev,&farsight_pwm_ops);					//初始化字符设备对象
	cdev->owner = THIS_MODULE; 					//设置字符设备所属模块
	ret_1 = alloc_chrdev_region(&devnum,0,1,"led_pwm_device"); 		//申请设备号
	if(ret_1<0)
	{
		goto out_err_0;
	}
	ret_1 = cdev_add(cdev, devnum, 1);					//添加字符设备
	if (ret_1 < 0) 
	{
		goto out_err_1;
	}	
	class = class_create(THIS_MODULE,"leds_pwm_class");			//创建character类
	if (IS_ERR(class)) 
	{
		ret_1 = PTR_ERR(class);
		goto out_err_2;	
	}
	dev = device_create(class,NULL,devnum,NULL,"leds_pwm_device");		//创建字符设备节点
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

static void __exit farsight_led_pwm_exit(void) 
{
	iounmap(pclk_gpio4_en);
	iounmap(grf_gpio4c_iomux);
	iounmap(pwm1);
	device_del(dev);
	class_destroy(class);
	cdev_del(cdev);
	kfree(cdev);
	unregister_chrdev_region(devnum,1);
}

module_init(farsight_led_pwm_init);
module_exit(farsight_led_pwm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FARSIGHT");
MODULE_DESCRIPTION("LED pwm Driver");

