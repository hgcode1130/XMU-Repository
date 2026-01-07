//------------------------------------光电开关设备驱动程序--------------------------
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

#define DEVICE_NAME	"rk3399_itr"
#define DRIVER_NAME 	"itr" 
#define ITR_ON 	0 
#define ITR_OFF 	1 

uint32_t ITR_GPIO = 0;
struct device_node *np_itr;
struct platform_device *pdev_itr;

static int rk3399_itr_open(struct inode *inode, struct file *file) 
{
	int ret;
	ITR_GPIO = of_get_gpio(np_itr, 0);
	if (ITR_GPIO == -EPROBE_DEFER)
	        return ITR_GPIO;
	if (ITR_GPIO < 0) 
	{
	        dev_err(&pdev_itr->dev, "error acquiring itr gpio: %d\n", ITR_GPIO);
	        return ITR_GPIO;
	}
	ret = devm_gpio_request_one(&pdev_itr->dev, ITR_GPIO, 0, "itr_gpio");
	if(ret) 
	{
	        dev_err(&pdev_itr->dev, "error requesting itr gpio: %d\n", ret);
	        return ret;
	}
	gpio_direction_input(ITR_GPIO);
	return 0;
}

static int rk3399_itr_close(struct inode *inode, struct file *file) 
{
	gpio_free(ITR_GPIO);
	return 0;
}

static ssize_t rk3399_itr_read(struct file *file, char __user * ubuf, size_t size, loff_t *loff_t)
{
	int state = 0;
	state = gpio_get_value(ITR_GPIO);
	if (copy_to_user(ubuf,&state,sizeof(state)))
		return -EFAULT;
	return 0;
}

static struct file_operations rk3399_itr_ops = {
	.owner		= THIS_MODULE,
	.open		= rk3399_itr_open,
	.release		= rk3399_itr_close, 
	.read     		= rk3399_itr_read,
};

static struct miscdevice rk3399_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &rk3399_itr_ops,
};

static int rk3399_itr_probe(struct platform_device *pdev)
{
	int ret;
	np_itr = pdev->dev.of_node;
	pdev_itr = pdev;
	ret = misc_register(&rk3399_misc_dev);
	return 0;
}

static int rk3399_itr_remove (struct platform_device *pdev)
{
	misc_deregister(&rk3399_misc_dev);
	return 0;
}

static int rk3399_itr_suspend (struct platform_device *pdev, pm_message_t state)
{
	return 0;
}

static int rk3399_itr_resume (struct platform_device *pdev)
{
	return 0;
}

static const struct of_device_id itr_of_match[] = {
        { .compatible = "fs_rk3399_itr" },
        {}
};

MODULE_DEVICE_TABLE(of, itr_of_match);

static struct platform_driver rk3399_itr_driver = {
	.probe = rk3399_itr_probe,
	.remove = rk3399_itr_remove,
	.suspend = rk3399_itr_suspend,
	.resume = rk3399_itr_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(itr_of_match),
	},
};

static int __init rk3399_itr_dev_init(void) 
{
	return platform_driver_register(&rk3399_itr_driver);
}

static void __exit rk3399_itr_dev_exit(void) 
{
	platform_driver_unregister(&rk3399_itr_driver);
}

module_init(rk3399_itr_dev_init);
module_exit(rk3399_itr_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Farsight");
MODULE_DESCRIPTION("fs rk3399 itr Driver");
