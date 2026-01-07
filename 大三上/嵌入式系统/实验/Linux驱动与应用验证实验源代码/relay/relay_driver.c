//------------------------------------继电器设备驱动程序--------------------------
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

#define DEVICE_NAME	"relay"
#define DRIVER_NAME 	"relay" 

#define RELAY_ON 	0 
#define RELAY_OFF 	1 

uint32_t RELAY_GPIO = 0;
struct device_node *np;
struct platform_device *pdev_open;
	
static int rk3399_relay_open(struct inode *inode, struct file *file) 
{
	int ret;
	RELAY_GPIO = of_get_gpio(np, 0);
	if (RELAY_GPIO == -EPROBE_DEFER)
                	return RELAY_GPIO;
        	if (RELAY_GPIO < 0) 
	{
                	dev_err(&pdev_open->dev, "error acquiring relay gpio: %d\n", RELAY_GPIO);
                	return RELAY_GPIO;
        	}
        	ret = devm_gpio_request_one(&pdev_open->dev, RELAY_GPIO, 0, "relay_gpio");
        	if(ret) 
	{
                	dev_err(&pdev_open->dev, "error requesting relay gpio: %d\n", ret);
                	return ret;
        	}
	gpio_direction_output(RELAY_GPIO, 0);
	return 0;
}

static int rk3399_relay_close(struct inode *inode, struct file *file) 
{
	gpio_free(RELAY_GPIO);
	return 0;
}

static long rk3399_relay_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	switch(cmd) 
	{
	        case RELAY_ON:
		gpio_set_value(RELAY_GPIO, 1);
		break;
	        case RELAY_OFF:
		gpio_set_value(RELAY_GPIO, 0);
		break;
	        default:
		return -EINVAL;
	}
	return 0;
}

static ssize_t rk3399_relay_write(struct file *filp, const char *buffer, size_t count, loff_t *ppos)
{
	char str[20];
	memset(str, 0, 20);
	if(copy_from_user(str, buffer, count))
	{
		printk("Error\n");
		return -EINVAL;
	}
	if(!strncmp(str, "1", 1))
		gpio_set_value(RELAY_GPIO, 1);
	else
		gpio_set_value(RELAY_GPIO, 0);
	return count;
}

static struct file_operations rk3399_relay_ops = {
	.owner			= THIS_MODULE,
	.open			= rk3399_relay_open,
	.release			= rk3399_relay_close, 
	.unlocked_ioctl		= rk3399_relay_ioctl,
	.write			= rk3399_relay_write,
};

static struct miscdevice rk3399_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &rk3399_relay_ops,
};

static int rk3399_relay_probe(struct platform_device *pdev)
{
	np = pdev->dev.of_node;
	pdev_open = pdev;
	misc_register(&rk3399_misc_dev);
	return 0;
}

static int rk3399_relay_remove (struct platform_device *pdev)
{
	misc_deregister(&rk3399_misc_dev);
	return 0;
}

static int rk3399_relay_suspend (struct platform_device *pdev, pm_message_t state)
{
	return 0;
}

static int rk3399_relay_resume (struct platform_device *pdev)
{
	return 0;
}

static const struct of_device_id relay_of_match[] = {
        { .compatible = "fs_rk3399_relay" },
        {}
};

MODULE_DEVICE_TABLE(of, relay_of_match);

static struct platform_driver rk3399_relay_driver = {
	.probe = rk3399_relay_probe,
	.remove = rk3399_relay_remove,
	.suspend = rk3399_relay_suspend,
	.resume = rk3399_relay_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(relay_of_match),
	},
};

static int __init rk3399_relay_dev_init(void) 
{
	return platform_driver_register(&rk3399_relay_driver);
}

static void __exit rk3399_relay_dev_exit(void) 
{
	platform_driver_unregister(&rk3399_relay_driver);
}

module_init(rk3399_relay_dev_init);
module_exit(rk3399_relay_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Farsight");
MODULE_DESCRIPTION("fs rk3399 relay Driver");