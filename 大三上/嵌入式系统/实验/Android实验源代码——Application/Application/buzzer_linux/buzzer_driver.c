//------------------------------------蜂鸣器（位于MPU开发板上）设备驱动程序--------------------------
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
#include <linux/of_address.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define DEVICE_NAME "buzzer_ctl"
#define DRIVER_NAME "buzzer_ctl"

#define Buzzer_on   1
#define Buzzer_off  0

#define GPIO_DR 0x00  	  
#define GPIO_DDR 0x04		

unsigned int addr_base[1] = {0};  			//基地址缓冲区
void __iomem *pclk_gpio1_en = NULL;			//GPIO1使能时钟寄存器
void __iomem *gpio1_swporta_base = NULL;		//GPIO1虚拟映射地址

struct device_node *buzzer_node;

static long farsight_buzzer_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    printk(KERN_ERR "%s:\n", __func__);
    switch(cmd) 
    {
        case Buzzer_off:
			printk(KERN_ERR "buzzer off\n");
			writel((readl((gpio1_swporta_base + GPIO_DR)) & ~(0x1<<23)) , (gpio1_swporta_base + GPIO_DR)); 	//置数据寄存器=0
            			break;
        case Buzzer_on:
			printk(KERN_ERR "buzzer on\n");
			writel((readl((gpio1_swporta_base + GPIO_DR)) | 0x1<<23) , (gpio1_swporta_base + GPIO_DR));  		//置数据寄存器=1
            			break;
        default:
            			return -EINVAL;
    }
    return 0;
}

static int farsight_buzzer_open(struct inode *inode, struct file *file) 
{
	printk(KERN_ERR "thisd *** %s  \n",__func__);
        	return 0;
}

static int farsight_buzzer_close(struct inode *inode, struct file *file) 
{
	printk(KERN_ERR "thisd *** %s  \n",__func__);
    	return 0;
}

static struct file_operations farsight_buzzer_ops = {
    .owner          	= THIS_MODULE,
    .open           	= farsight_buzzer_open,
    .release        	= farsight_buzzer_close,
    .unlocked_ioctl   = farsight_buzzer_ioctl,
};

static struct miscdevice farsight_misc_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &farsight_buzzer_ops,
};

static int farsight_buzzer_probe(struct platform_device *pdev)
{
	int ret = 0;
	ret = misc_register(&farsight_misc_dev);							//注册杂项设备
	if(ret<0)
	    return ret;
	buzzer_node = pdev->dev.of_node;								//获取设备树节点信息
	ret = of_property_read_u32_array(buzzer_node, "gpio1_base", addr_base, 1);				//设备树获取基地址   
	if(ret<0)
	    return ret;
	gpio1_swporta_base = ioremap(addr_base[0],8);							//映射GPIO1基地址
	ret = of_property_read_u32_array(buzzer_node, "pclk_gpio1", addr_base, 1); 				//设备树获取基地址   
	if(ret<0)
	    return ret;
	pclk_gpio1_en = ioremap((addr_base[0]+0x104),8);						//映射使能GPIO1时钟寄存器基地址
	writel(((readl(pclk_gpio1_en) & ~(0x1<<4)) | 0x1<<20) , pclk_gpio1_en); 				//使能GPIO1时钟
	writel(readl((gpio1_swporta_base + GPIO_DDR)) | 0x1<<23, (gpio1_swporta_base + GPIO_DDR));		//设置蜂鸣器引脚为输出模式
	return 0;
};

static int farsight_buzzer_remove (struct platform_device *pdev)
{
	iounmap(gpio1_swporta_base);
	iounmap(pclk_gpio1_en);
    	misc_deregister(&farsight_misc_dev);
    	return 0;
}

static const struct of_device_id buzzer_of_match[] = {
        { .compatible = "farsight_buzzer" },
        {}
};

static struct platform_driver farsight_buzzer_driver = {
    .probe = farsight_buzzer_probe,
    .remove = farsight_buzzer_remove,
    .driver = {
        .name = DRIVER_NAME,
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(buzzer_of_match),
    },
};

static int __init farsight_buzzer_dev_init(void) 
{
    	return platform_driver_register(&farsight_buzzer_driver);
}

static void __exit farsight_buzzer_dev_exit(void) 
{
    	platform_driver_unregister(&farsight_buzzer_driver);
}

module_init(farsight_buzzer_dev_init);
module_exit(farsight_buzzer_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FARSIGHT");
MODULE_DESCRIPTION("FARSIGHT BUZZER Driver");

