//------------------------------------3个LED灯设备驱动程序（使用设备树文件）--------------------------
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

#define LED1_ON    _IO('G',1)
#define LED1_OFF   _IO('G',2)
#define LED2_ON    _IO('G',3)
#define LED2_OFF   _IO('G',4)
#define LED3_ON    _IO('G',5)
#define LED3_OFF   _IO('G',6)

#define DEVICE_NAME	"leds_ctl"
#define DRIVER_NAME 	"leds_ctl"

struct led_driver_t{
	struct cdev *cdev_leds;		//字符设备结构体，Linux管理字符设备
	struct class* class_leds;		//类结构体
	struct device* dev_leds;		//保存设备基本信息的结构体
	struct device_node *np;		//保存设备树节点信息结构体
	dev_t devnum;
};

static uint32_t LED_GPIO1 = 0;
static uint32_t LED_GPIO2 = 0;
static uint32_t LED_GPIO3 = 0;

static struct led_driver_t *led;

static int farsight_led_open(struct inode *inode, struct file *file) 
{
	return 0;
}

static int farsight_led_close(struct inode *inode, struct file *file) 
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
            		gpio_set_value(LED_GPIO1, 1);
            		printk(KERN_ERR " ### LED1 ON ###\n  ");
            		break;
        	case LED1_OFF:
            		gpio_set_value(LED_GPIO1, 0);
            		printk(KERN_ERR " ### LED1 OFF ###\n  ");
            		break;
	case LED2_ON:
            		gpio_set_value(LED_GPIO2, 1);
            		printk(KERN_ERR " ### LED2 ON ###\n  ");
            		break;
        	case LED2_OFF:
            		gpio_set_value(LED_GPIO2, 0);
            		printk(KERN_ERR " ### LED2 OFF ###\n  ");
            		break;
	case LED3_ON:
		gpio_set_value(LED_GPIO3, 1);
		printk(KERN_ERR " ### LED3 ON ###\n  ");
		break;
	case LED3_OFF:
		gpio_set_value(LED_GPIO3, 0);
		printk(KERN_ERR " ### LED3 OFF ###\n  ");
		break;
	default:
		return -EINVAL;
    }
    return 0;
}

static struct file_operations farsight_led_ops = {
	.owner		= THIS_MODULE,
	.open		= farsight_led_open,
	.release		= farsight_led_close, 
	.unlocked_ioctl	= farsight_led_ioctl,
};

int register_leds(struct platform_device *pdev)		//注册设备文件
{
	int ret_1;
	cdev_init(led->cdev_leds,&farsight_led_ops);					//初始化字符设备对象
	led->cdev_leds->owner = THIS_MODULE; 					//设置字符设备所属模块
	ret_1 = alloc_chrdev_region(&led->devnum,0,1,"leds_ctl"); 			//申请设备号
	if(ret_1<0){
		dev_err(&pdev->dev, "alloc_chrdev_region() failed ret: %d.\n", ret_1);
		goto out_err_0;
	}
	ret_1 = cdev_add(led->cdev_leds, led->devnum, 1);				//添加字符设备
	if (ret_1 < 0) {
		dev_err(&pdev->dev, "cdev_add() failed ret: %d.\n", ret_1);
		goto out_err_1;
	}	
	led->class_leds = class_create(THIS_MODULE,"leds_ctl");				//创建LED类
	if (IS_ERR(led->class_leds)) {
		ret_1 = PTR_ERR(led->class_leds);
		dev_err(&pdev->dev, "class_create() failed ret: %d.\n", ret_1);
		goto out_err_2;	
	}
	led->dev_leds = device_create(led->class_leds,NULL,led->devnum,NULL,"leds_ctl");	//创建字符设备节点
	if (IS_ERR(led->dev_leds)) {
		ret_1 = PTR_ERR(led->dev_leds);
		dev_err(&pdev->dev, "device_create() failed ret: %d.\n", ret_1);
		goto out_err_3;	
	}
	return 0;
out_err_3:
	device_del(led->dev_leds);
	class_destroy(led->class_leds);
out_err_2:
	cdev_del(led->cdev_leds);
out_err_1:
	unregister_chrdev_region(led->devnum,1);
out_err_0:
	kfree(led);
	return ret_1;
}
 
static int farsight_led_probe(struct platform_device *pdev)		//设备树匹配成功执行函数
{
	int ret;
	led = kmalloc(sizeof(struct led_driver_t), GFP_KERNEL);			//申请内存
	led->np = pdev->dev.of_node;					//获取设备树节点信息

	LED_GPIO1 = of_get_named_gpio(led->np,"led1", 0);			//获取LED1引脚的管脚号
	if (LED_GPIO1 == -EPROBE_DEFER)
                	return LED_GPIO1;
        	if (LED_GPIO1 < 0) {
                	dev_err(&pdev->dev, "error acquiring led gpio: %d\n", LED_GPIO1);
                	return LED_GPIO1;
        	}
	ret = gpio_request(LED_GPIO1,NULL);					//向内核注册该引脚，确保不被其他驱动占用
        	if(ret) {
                	dev_err(&pdev->dev, "error requesting led gpio: %d\n", ret);
                	return ret;
        	}
	gpio_direction_output(LED_GPIO1, 0);					//设置LED1引脚为输出模式，初始为低电平

	LED_GPIO2 = of_get_named_gpio(led->np,"led2", 0);			//获取LED2引脚的管脚号
    	if (LED_GPIO2 == -EPROBE_DEFER)
                	return LED_GPIO2;
        	if (LED_GPIO2 < 0) {
                	dev_err(&pdev->dev, "error acquiring led gpio: %d\n", LED_GPIO2);
                	return LED_GPIO2;
        	}
    	ret = gpio_request(LED_GPIO2,NULL);					//向内核注册该引脚，确保不被其他驱动占用
        	if(ret) {
                	dev_err(&pdev->dev, "error requesting led gpio: %d\n", ret);
                	return ret;
        	}
    	gpio_direction_output(LED_GPIO2, 0);					//设置LED2引脚为输出模式，初始为低电平

	LED_GPIO3 = of_get_named_gpio(led->np,"led3", 0);			//获取LED3引脚的管脚号
    	if (LED_GPIO1 == -EPROBE_DEFER)
                	return LED_GPIO3;
        	if (LED_GPIO1 < 0) {
                	dev_err(&pdev->dev, "error acquiring led gpio: %d\n", LED_GPIO3);
                	return LED_GPIO3;
        	}
    	ret = gpio_request(LED_GPIO3,NULL);				//向内核注册该引脚，确保不被其他驱动占用
        	if(ret) {
                	dev_err(&pdev->dev, "error requesting led gpio: %d\n", ret);
                	return ret;
        	}
    	gpio_direction_output(LED_GPIO3, 0);				//设置LED3引脚为输出模式，初始为低电平

	ret = register_leds(pdev);					//注册字符设备
	platform_set_drvdata(pdev,led);				//存储在probe()中的指针以防止丢失
	return 0;
}

static int farsight_led_remove (struct platform_device *pdev)	//移除设备文件
{
	gpio_free(LED_GPIO1);	
	gpio_free(LED_GPIO2);	
	gpio_free(LED_GPIO3);	
	device_del(led->dev_leds);
	class_destroy(led->class_leds);
	cdev_del(led->cdev_leds);
	unregister_chrdev_region(led->devnum,1);
	kfree(led);
	return 0;
}

static int farsight_led_suspend (struct platform_device *pdev, pm_message_t state)	//暂停设计文件
{
	return 0;
}

static int farsight_led_resume (struct platform_device *pdev)	//恢复设备文件
{
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id led_of_match[] = {		//匹配表，在of_device_id表中填充成员
        { .compatible = "farsight_led" },
        {}
};
MODULE_DEVICE_TABLE(of, led_of_match);			//将设备加入到外设队列，告诉程序员读者，这是个热插拔设备
#endif

//内核中的platform结构体对象，定义了操作对象的方法
static struct platform_driver farsight_led_driver = {
	.probe = farsight_led_probe,				//设备树和匹配表匹配成功后之后执行函数，在该函数中，一般初始化设备，申请驱动所需资源
	.remove = farsight_led_remove,			//从内核删除设备，释放资源
	.suspend = farsight_led_suspend,			//挂起
	.resume = farsight_led_resume,			//唤醒
	.driver = {					//设备驱动通用属性
		.name = DRIVER_NAME,			//设备驱动的名字
		.owner = THIS_MODULE,			//表示实现该驱动程序的模块
		.of_match_table = of_match_ptr(led_of_match),	//与设备树进行匹配，使用id_table
	},
};

//驱动模块入口
static int __init farsight_led_dev_init(void) 
{
	return platform_driver_register(&farsight_led_driver);	//将驱动注册到platform总线上
}

//驱动模块出口
static void __exit farsight_led_dev_exit(void) 
{
	platform_driver_unregister(&farsight_led_driver);		//将驱动从platform总线删除
}

module_init(farsight_led_dev_init);
module_exit(farsight_led_dev_exit);

MODULE_LICENSE("GPL");//许可证
MODULE_AUTHOR("FARSIGHT");//作者
MODULE_DESCRIPTION("LED Driver");//描述信息
