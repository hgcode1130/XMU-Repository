//------------------------------------步进电机（位于底板上）设备驱动程序--------------------------
#include <linux/module.h>
#include <linux/device.h> 
#include <linux/cdev.h> 
#include <linux/fs.h> 
#include <linux/io.h> 
#include <linux/ioctl.h> 
#include <linux/platform_device.h> 
#include <linux/slab.h> 
#include <linux/of.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>

#define STEPMOTOR_MAX_DEV (1)
#define STEPPER_MAJOR 90
#define STEPPER_MINOR 0

#ifdef DEBUG
#define DEVICE_NAME "stepper"
#define LOGD(fmt, args...) \
	{printk(KERN_INFO "<<-Device:%s->> line %d at %s ", DEVICE_NAME, __LINE__, __func__); \
		printk(KERN_INFO fmt, ##args);}
#else
#define LOGD(fmt, args...) (void)(0);
#endif

#define LOGI(fmt, args...) {printk(KERN_INFO fmt, ##args);}
#define LOGE(fmt, args...) {printk(KERN_ERR fmt, ##args);}

#define STEPPER_ON 	0 
#define STEPPER_OFF 	1 
#if 0
#define IOCTL_MAGIC 	'S'
#define STEPPER_ON 	_IOW(IOCTL_MAGIC, 0, int) 
#define STEPPER_OFF 	_IOW(IOCTL_MAGIC, 1, int) 
#endif 

struct stepmotor_dev {
	struct device* dev;
	struct cdev cdev;
	dev_t devnum;
	struct class* stepmotorcls;
	struct device* stepmotordev;
	struct gpio_desc *gpiod[4];
	struct platform_device *pdev;
};

static void dev_on(struct file *filp, int nr)
{
	struct stepmotor_dev* stepmotor = (struct stepmotor_dev*)filp->private_data;
	gpiod_direction_output(stepmotor->gpiod[nr], 0);
}

static void dev_off(struct file *filp, int nr)
{
	struct stepmotor_dev* stepmotor = (struct stepmotor_dev*)filp->private_data;
	gpiod_direction_output(stepmotor->gpiod[nr],1);
}

int stepmotor_io_open(struct inode * inode, struct file * filp)
{
	int ret;
	struct cdev* i_cdev = inode->i_cdev;
	struct stepmotor_dev *stepmotor = container_of(i_cdev, struct stepmotor_dev, cdev);
	filp->private_data = stepmotor;
	stepmotor->gpiod[0] = devm_gpiod_get_index_optional(stepmotor->dev, "stepmotor_pin1", 0, GPIOD_OUT_HIGH);		//获取设备树中GPIO管脚
	if (IS_ERR(stepmotor->gpiod[0])) 
	{
		ret = PTR_ERR(stepmotor->gpiod[0]);
		dev_err(stepmotor->dev, "devm_gpiod_get_index_optional() failed ret: %d.\n", ret);
		device_del(stepmotor->stepmotordev);
	}
	stepmotor->gpiod[1] = devm_gpiod_get_index_optional(stepmotor->dev, "stepmotor_pin2", 0, GPIOD_OUT_HIGH);
	if (IS_ERR(stepmotor->gpiod[1])) 
	{
		ret = PTR_ERR(stepmotor->gpiod[1]);
		dev_err(stepmotor->dev, "devm_gpiod_get_index_optional() failed ret: %d.\n", ret);
		device_del(stepmotor->stepmotordev);
	}
	stepmotor->gpiod[2] = devm_gpiod_get_index_optional(stepmotor->dev, "stepmotor_pin3", 0, GPIOD_OUT_HIGH);
	if (IS_ERR(stepmotor->gpiod[2])) 
	{
		ret = PTR_ERR(stepmotor->gpiod[2]);
		dev_err(stepmotor->dev, "devm_gpiod_get_index_optional() failed ret: %d.\n", ret);
		device_del(stepmotor->stepmotordev);
	}
	stepmotor->gpiod[3] = devm_gpiod_get_index_optional(stepmotor->dev, "stepmotor_pin4", 0, GPIOD_OUT_HIGH);
	if (IS_ERR(stepmotor->gpiod[3])) 
	{
		ret = PTR_ERR(stepmotor->gpiod[3]);
		dev_err(stepmotor->dev, "devm_gpiod_get_index_optional() failed ret: %d.\n", ret);
		device_del(stepmotor->stepmotordev);
	}
	dev_info( stepmotor->dev, "stepmotor device open\n");
	return 0;
}

int stepmotor_io_close(struct inode * inodp, struct file * filp)
{
	struct stepmotor_dev* stepmotor = (struct stepmotor_dev*)filp->private_data;
	dev_info(stepmotor->dev, "stepmotor device close\n");
	devm_gpiod_put(stepmotor->dev,stepmotor->gpiod[0]);
	devm_gpiod_put(stepmotor->dev,stepmotor->gpiod[1]);
	devm_gpiod_put(stepmotor->dev,stepmotor->gpiod[2]);
	devm_gpiod_put(stepmotor->dev,stepmotor->gpiod[3]);
	return 0;
}

long stepmotor_ioctl(struct file * filp, unsigned int cmd, unsigned long arg)
{
	int nr = 0;
	nr = arg;
	LOGD("nr = %d\n", nr);
	switch(cmd) 
	{
		case STEPPER_ON:
			LOGD("dev_on<%d>\n", nr);
			dev_on(filp,nr);
			break;
		case STEPPER_OFF:
			LOGD("dev_off<%d>\n", nr);
			dev_off(filp,nr);
			break;
		default:
			LOGE("Please Check User's cmd\n");
	 		return -EINVAL;
	}
	return 0;
}

struct file_operations dev_ops = {
	.open = stepmotor_io_open,
	.release = stepmotor_io_close,
	.unlocked_ioctl = stepmotor_ioctl,
};

int stepmotor_io_drv_probe(struct platform_device *pdev)
{
	int ret;
	struct stepmotor_dev* stepmotor = kmalloc(sizeof(struct stepmotor_dev), GFP_KERNEL);
	dev_info(&pdev->dev, "call stepmotor_io_drv_probe\n");
	cdev_init(&stepmotor->cdev, &dev_ops);									//初始化字符设备对象
	stepmotor->cdev.owner = THIS_MODULE;
	stepmotor->devnum = MKDEV(STEPPER_MAJOR,STEPPER_MINOR);							//设置cdev字符设备对象所属的模块
	ret = register_chrdev_region(stepmotor->devnum,STEPMOTOR_MAX_DEV, "stepmotor");				//分配起始设备号
	if (ret < 0) 
	{
		dev_err(&pdev->dev, "alloc_chrdev_region() failed ret: %d.\n", ret);
		goto out_err_0;
	}
	ret = cdev_add(&stepmotor->cdev, stepmotor->devnum, 1);							//将cdev字符设备对象注册到字符设备列表中
	if (ret < 0) 
	{
		dev_err(&pdev->dev, "cdev_add() failed ret: %d.\n", ret);
		goto out_err_1;
	}	
	stepmotor->stepmotorcls = class_create(THIS_MODULE, "stepmotor");						//创建stepmotor class
	if (IS_ERR(stepmotor->stepmotorcls)) 
	{
		ret = PTR_ERR(stepmotor->stepmotorcls);
		dev_err(&pdev->dev, "class_create() failed ret: %d.\n", ret);
		goto out_err_2;	
	}
	stepmotor->stepmotordev = device_create(stepmotor->stepmotorcls, NULL, stepmotor->devnum, NULL, "stepper");		//创建/dev/stepmotor设备节点
	if (IS_ERR(stepmotor->stepmotordev)) 
	{
		ret = PTR_ERR(stepmotor->stepmotordev);
		dev_err(&pdev->dev, "device_create() failed ret: %d.\n", ret);
		goto out_err_3;	
	}
	stepmotor->dev = &pdev->dev;
	platform_set_drvdata(pdev, stepmotor);
	return 0;
out_err_3:
	class_destroy(stepmotor->stepmotorcls);
out_err_2:
	cdev_del(&stepmotor->cdev);
out_err_1:
	unregister_chrdev_region(stepmotor->devnum, STEPMOTOR_MAX_DEV);
out_err_0:
	kfree(stepmotor);
	return ret;
}

int stepmotor_io_drv_remove(struct platform_device *pdev)
{
	struct stepmotor_dev *stepmotor = platform_get_drvdata(pdev);
	dev_info(&pdev->dev, "call stepmotor_io_drv_remove\n");
	device_del(stepmotor->stepmotordev);
	class_destroy(stepmotor->stepmotorcls);
	cdev_del(&stepmotor->cdev);
	unregister_chrdev_region(stepmotor->devnum, STEPMOTOR_MAX_DEV);
	return 0;
}

static const struct of_device_id of_my_compatible_match[] = {
	{ .compatible = "d1-stepmotor", },
	{},
};

MODULE_DEVICE_TABLE(of, of_my_compatible_match);

struct platform_driver stepmotor_io_drv = {
	.driver = {
		.name = "d1-stepmotor",
		.of_match_table = of_my_compatible_match,
	},
	.probe = stepmotor_io_drv_probe, 		//当设备和驱动匹配成功后执行
	.remove = stepmotor_io_drv_remove, 		//当设备或驱动移除时执行
};

int stepmotor_io_drv_init(void)
{
	return platform_driver_register(&stepmotor_io_drv);
}

void stepmotor_io_drv_exit(void)
{
	platform_driver_unregister(&stepmotor_io_drv);
}

module_init(stepmotor_io_drv_init);
module_exit(stepmotor_io_drv_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Driver for stepmotor");
MODULE_AUTHOR("Farsight yanfa");


