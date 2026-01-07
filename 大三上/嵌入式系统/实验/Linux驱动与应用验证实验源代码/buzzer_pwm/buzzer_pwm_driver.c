//------------------------------------蜂鸣器（位于底板上）设备驱动程序--------------------------
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

#define DEVICE_NAME	"buzzer"
#define DRIVER_NAME 	"buzzer" 

#define IOCTL_MAGIC 	'B'
#define ROTATE_ON 	_IO(IOCTL_MAGIC, 1) 
#define ROTATE_OFF 	_IO(IOCTL_MAGIC, 0) 

struct buzzer{
	struct hrtimer buzzer_timer_high;	//高精度定时器纳秒级
	uint32_t BUZZER_GPIO;//GPIO
	struct platform_device *pdev;
	struct device_node *np;
	int val;
	int flag;
};

struct buzzer *buzzer;

static enum hrtimer_restart buzzer_timeout_high(struct hrtimer *timer)
{
	if(buzzer->val == 1 )
	{
		buzzer->val = 0;
		gpio_set_value(buzzer->BUZZER_GPIO,buzzer->val);
		hrtimer_forward_now(&buzzer->buzzer_timer_high,ktime_set(0,250000));
	}
	else if(buzzer->val == 0)
	{
		buzzer->val = 1;
		gpio_set_value(buzzer->BUZZER_GPIO,buzzer->val);
		hrtimer_forward_now(&buzzer->buzzer_timer_high,ktime_set(0,250000));
	}
	else
	{
	}
	return HRTIMER_RESTART;
}

static int rk3399_buzzer_open(struct inode *inode, struct file *file) 
{
	int ret;
	buzzer->BUZZER_GPIO = of_get_gpio(buzzer->np, 0);
	if (buzzer->BUZZER_GPIO == -EPROBE_DEFER)
        		return buzzer->BUZZER_GPIO;
    	if (buzzer->BUZZER_GPIO < 0) 
	{
    		dev_err(&(buzzer->pdev->dev), "error acquiring buzzer gpio: %d\n", buzzer->BUZZER_GPIO);
        		return buzzer->BUZZER_GPIO;
    	}
    	ret = devm_gpio_request_one(&(buzzer->pdev->dev), buzzer->BUZZER_GPIO, 0, "buzzer_gpio");
    	if(ret) 
	{
    		dev_err(&buzzer->pdev->dev, "error requesting buzzer gpio: %d\n", ret);
        		return ret;
    	}
	hrtimer_start(&buzzer->buzzer_timer_high, ktime_set(0,500000), HRTIMER_MODE_REL);
	return 0;
}


static int rk3399_buzzer_close(struct inode *inode, struct file *file) 
{
	gpio_free(buzzer->BUZZER_GPIO);
	hrtimer_cancel(&buzzer->buzzer_timer_high);
	return 0;
}

static long rk3399_buzzer_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	if (_IOC_TYPE(cmd) != IOCTL_MAGIC)		//判断魔数是否一致
		return -ENOTTY;
	if (_IOC_NR(cmd) > 1)			//判断基数是否超出范围
		return -ENOTTY;
	switch(cmd) 
	{
		case ROTATE_ON:
			buzzer->val = 1;
			gpio_set_value(buzzer->BUZZER_GPIO,buzzer->val);
			hrtimer_start(&buzzer->buzzer_timer_high, ktime_set(0,250000), HRTIMER_MODE_REL);
			hrtimer_forward_now(&buzzer->buzzer_timer_high,ktime_set(0,250000));
			break;
		case ROTATE_OFF:
			hrtimer_cancel(&buzzer->buzzer_timer_high);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}

static struct file_operations rk3399_buzzer_ops = {
	.owner		= THIS_MODULE,
	.open		= rk3399_buzzer_open,
	.release		= rk3399_buzzer_close, 
	.unlocked_ioctl	= rk3399_buzzer_ioctl,
};

static struct miscdevice rk3399_misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = DEVICE_NAME,
	.fops = &rk3399_buzzer_ops,
};

static int rk3399_buzzer_probe(struct platform_device *pdev)
{
	int ret;
	buzzer = kzalloc(sizeof(*buzzer),GFP_KERNEL);
	buzzer->np = pdev->dev.of_node;
	buzzer->pdev = pdev;
	hrtimer_init(&buzzer->buzzer_timer_high, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	buzzer->buzzer_timer_high.function = buzzer_timeout_high;
	ret = misc_register(&rk3399_misc_dev);
	return 0;
}

static int rk3399_buzzer_remove (struct platform_device *pdev)
{
	misc_deregister(&rk3399_misc_dev);
	hrtimer_cancel(&buzzer->buzzer_timer_high);
	return 0;
}

static int rk3399_buzzer_suspend (struct platform_device *pdev, pm_message_t state)
{
	return 0;
}

static int rk3399_buzzer_resume (struct platform_device *pdev)
{
	return 0;
}

static const struct of_device_id buzzer_of_match[] = {
        { .compatible = "fs_rk3399_buzzer" },
        {}
};

MODULE_DEVICE_TABLE(of, buzzer_of_match);

static struct platform_driver rk3399_buzzer_driver = {
	.probe = rk3399_buzzer_probe,
	.remove = rk3399_buzzer_remove,
	.suspend = rk3399_buzzer_suspend,
	.resume = rk3399_buzzer_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(buzzer_of_match),
	},
};

static int __init rk3399_buzzer_dev_init(void) 
{
	return platform_driver_register(&rk3399_buzzer_driver);
}

static void __exit rk3399_buzzer_dev_exit(void) 
{
	platform_driver_unregister(&rk3399_buzzer_driver);
}

module_init(rk3399_buzzer_dev_init);
module_exit(rk3399_buzzer_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Farsight");
MODULE_DESCRIPTION("fs rk3399 servo Driver");
