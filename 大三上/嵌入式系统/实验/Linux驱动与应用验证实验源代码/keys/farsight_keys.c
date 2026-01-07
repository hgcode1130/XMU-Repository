//------------------------------------2个按键设备驱动程序--------------------------
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

struct keys_gpio_info {
	int KEY_GPIO[2];
	int KEY_IRQ[2];
	int KEY_MODE[2];
	int value[2];
	int state;
	int tmp_data[2];
	wait_queue_head_t wq_head;
};

static struct keys_gpio_info *mykeys;  

static int farsight_keys_open(struct inode *inode, struct file *file) 
{
	return 0;
}

static int farsight_keys_close(struct inode *inode, struct file *file) 
{
	return 0;
}

static ssize_t farsight_keys_read(struct file *file, char __user * ubuf, size_t size, loff_t *loff_t)
{
	int ret;
	wait_event_interruptible(mykeys->wq_head, mykeys->tmp_data[0]!=0);
	ret = copy_to_user((void *)ubuf,mykeys->tmp_data,sizeof(mykeys->tmp_data)); 
	if(ret != 0)
	{
		printk("copy_to_user err\n");
		return ret;
	}
	mykeys->tmp_data[0] = 0;
	return 2;
}

static struct file_operations farsight_keys_ops = {
	.owner		= THIS_MODULE,
	.open		= farsight_keys_open,
	.release		= farsight_keys_close, 
	.read     		= farsight_keys_read,
};

static struct miscdevice farsight_keys_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "farsight_keys",
	.fops = &farsight_keys_ops,
};

static irqreturn_t key1_irq_callback(int irq, void *dev_id)		//按键KEY1
{
	mykeys->value[0] = gpio_get_value(mykeys->KEY_GPIO[0]);
	mykeys->tmp_data[0] = 0x01;
	mykeys->tmp_data[1] = mykeys->value[0];
	wake_up_interruptible(&mykeys->wq_head);                 
	return IRQ_HANDLED;
}

static irqreturn_t key2_irq_callback(int irq, void *dev_id)		//按键KEY2
{
	mykeys->value[1] = gpio_get_value(mykeys->KEY_GPIO[1]);
	mykeys->tmp_data[0] = 0x02;
	mykeys->tmp_data[1] = mykeys->value[1];
	wake_up_interruptible(&mykeys->wq_head);                 
    	return IRQ_HANDLED;
}

static int keys_gpio_probe(struct platform_device *pdev)
{
    	int ret;
    	enum of_gpio_flags flag;
    	struct device_node *keys_gpio_node = pdev->dev.of_node;
    	mykeys = devm_kzalloc(&pdev->dev,sizeof(struct keys_gpio_info *), GFP_KERNEL);
    	if (!mykeys) 
    	{
       	 	dev_err(&pdev->dev, "devm_kzalloc failed!\n");
        		return -ENOMEM;
    	}

/***************************************  KEY1属性  ******************************************************/
    	mykeys->KEY_GPIO[0] = of_get_named_gpio_flags(keys_gpio_node, "key1-gpio", 0, &flag);
    	if (!gpio_is_valid(mykeys->KEY_GPIO[0])) 
    	{
        		dev_err(&pdev->dev, "keys-gpio: %d is invalid\n", mykeys->KEY_GPIO[0]);
        		return -ENODEV;
    	}
    	mykeys->KEY_IRQ[0] = gpio_to_irq(mykeys->KEY_GPIO[0]);
    	mykeys->KEY_MODE[0] = flag;
    	if (gpio_request(mykeys->KEY_GPIO[0], "key1-gpio")) 
    	{
        		dev_err(&pdev->dev, "keys-gpio: %d request failed!\n", mykeys->KEY_GPIO[0]);
        		gpio_free(mykeys->KEY_GPIO[0]);
        		return -ENODEV;
    	}
    	ret = request_irq(mykeys->KEY_IRQ[0],key1_irq_callback,mykeys->KEY_MODE[0],"KEY1_IRQ",mykeys);
    	if(ret != 0)
    	{
		free_irq(mykeys->KEY_IRQ[0],mykeys);	
		dev_err(&pdev->dev, "Failed to request key1 IRQ: %d\n", ret);
    	}
    	gpio_direction_input(mykeys->KEY_GPIO[0]);

/***********************************  KEY2属性  **********************************************************/
	mykeys->KEY_GPIO[1] = of_get_named_gpio_flags(keys_gpio_node, "key2-gpio", 0, &flag);
    	if (!gpio_is_valid(mykeys->KEY_GPIO[1])) 
	{
        		dev_err(&pdev->dev, "keys-gpio: %d is invalid\n", mykeys->KEY_GPIO[1]);
        		return -ENODEV;
    	}
	mykeys->KEY_IRQ[1] = gpio_to_irq(mykeys->KEY_GPIO[1]);
	mykeys->KEY_MODE[1] = flag;
   	 if (gpio_request(mykeys->KEY_GPIO[1], "key2-gpio")) 
	{
        		dev_err(&pdev->dev, "keys-gpio: %d request failed!\n", mykeys->KEY_GPIO[1]);
        		gpio_free(mykeys->KEY_GPIO[1]);
        		return -ENODEV;
    	}
	ret = request_irq(mykeys->KEY_IRQ[1],key2_irq_callback,mykeys->KEY_MODE[1],"KEY2_IRQ",mykeys);
	if(ret != 0)
	{
		free_irq(mykeys->KEY_IRQ[1],mykeys);	
		dev_err(&pdev->dev, "Failed to request key2 IRQ: %d\n", ret);
	}
	gpio_direction_input(mykeys->KEY_GPIO[1]);

    	mykeys->state = 0;
	init_waitqueue_head(&mykeys->wq_head);	//初始化等待队列头
	ret = misc_register(&farsight_keys_dev);	//注册杂项驱动
	return 0;
}

static int keys_gpio_remove(struct platform_device *pdev)
{
    	gpio_free(mykeys->KEY_GPIO[0]);
	free_irq(mykeys->KEY_IRQ[0],mykeys);	
    	gpio_free(mykeys->KEY_GPIO[1]);
	free_irq(mykeys->KEY_IRQ[1],mykeys);	
	misc_deregister(&farsight_keys_dev);
	kfree(mykeys);
	return 0;
}

static struct of_device_id keys_match_table[] = {
        { .compatible = "farsight_keys",},
        {},
};

static struct platform_driver keys_gpio_driver = {
        .driver = {
                .name = "farsight_keys",
                .owner = THIS_MODULE,
                .of_match_table = of_match_ptr(keys_match_table),
        },
        .probe  = keys_gpio_probe,
        .remove = keys_gpio_remove,
};

static int keys_gpio_init(void)
{
        return platform_driver_register(&keys_gpio_driver);
}
module_init(keys_gpio_init);

static void keys_gpio_exit(void)
{
        platform_driver_unregister(&keys_gpio_driver);
}
module_exit(keys_gpio_exit);

MODULE_AUTHOR("FARSIGHT");
MODULE_DESCRIPTION("FARSIGHT KEYS DRIVER");
MODULE_LICENSE("GPL");

