//------------------------------------ADC设备驱动程序--------------------------
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/clk.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <linux/reset.h>
#include <linux/slab.h>
#include <linux/regulator/consumer.h>
#include <linux/iio/iio.h>
#include <asm/uaccess.h>

#define MQ3   _IO('A',0)	//酒精
#define MQ5   _IO('A',1)	//气体
#define FLAME _IO('A',2)	//火焰
#define LDR   _IO('A',3)	//光敏
#define RP    _IO('A',4)	//电位器

#define DEVICE_NAME	"adc_ctl"
#define DRIVER_NAME 	"adc_ctl"

#define SARADC_DATA 		0x00
#define SARADC_STAS 		0x04
#define SARADC_CTRL 		0x08
#define SARADC_DLY_PU_SOC 	0x0C

#define CTRL_IRQ_ENABLE		BIT(5)
#define CTRL_POWER_UP		BIT(3)
#define CTRL_IRQ_DISABLE		~BIT(5)
#define CTRL_POWER_DOWN	~BIT(3)

struct farsight_saradc_data {
	int num_bits;
	unsigned long clk_rate;
};

struct farsight_saradc {
	void __iomem *regs;
	struct clk	*pclk;
	struct clk	*clk;
	const struct farsight_saradc_data *data;
	struct cdev cdev;
	struct class* class;
	struct device* dev;
	dev_t devnum;
};

struct farsight_saradc *info = NULL;

static const struct farsight_saradc_data rk3399_saradc_data = {
	.num_bits = 10,
	.clk_rate = 1000000,
};

static int farsight_saradc_open(struct inode *inode, struct file *file) 
{
	return 0;
}

static int farsight_saradc_close(struct inode *inode, struct file *file) 
{
	return 0;
}

/**********************************/
/*    选择ADC通道                 */
/*    气体传感器使用SARADC通道0   */
/*    电位器使用SARADC通道2       */
/*    火焰传感器使用SARADC通道3   */
/*    光敏传感器使用SARADC通道3   */
/*    酒精传感器使用SARADC通道4   */                             
/**********************************/
static long farsight_saradc_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	unsigned int adc_data = 0;
	writel((readl(info->regs + SARADC_CTRL) & CTRL_IRQ_DISABLE & CTRL_POWER_DOWN), (info->regs + SARADC_CTRL));	//停止ADC转换 - 禁用中断
	writel(0x8, (info->regs + SARADC_DLY_PU_SOC));
	switch(cmd) 
	{
		case MQ5:
			writel(((readl(info->regs + SARADC_CTRL) & ~(0x7<<0)) | CTRL_POWER_UP), (info->regs + SARADC_CTRL));		//ADC采集通道选择0通道
            			break;
        		case RP:
			writel((((readl(info->regs + SARADC_CTRL) & ~(0x7<<0)) | 0x2) | CTRL_POWER_UP), (info->regs + SARADC_CTRL));		//ADC采集通道选择2通道
			break;
		case FLAME:
			writel((((readl(info->regs + SARADC_CTRL) & ~(0x7<<0)) | 0x3) | CTRL_POWER_UP), (info->regs + SARADC_CTRL));		//ADC采集通道选择3通道
			break;
        		case LDR:
			writel((((readl(info->regs + SARADC_CTRL) & ~(0x7<<0)) | 0x3) | CTRL_POWER_UP), (info->regs + SARADC_CTRL));		//ADC采集通道选择3通道
			break;
		case MQ3:
			writel((((readl(info->regs + SARADC_CTRL) & ~(0x7<<0)) | 0x4) | CTRL_POWER_UP), (info->regs + SARADC_CTRL));		//ADC采集通道选择4通道
            			break;
		default:
			return -EINVAL;
	}
	msleep(1);
	while((readl((info->regs + SARADC_STAS)) & 0x1) == 0x1);		//判断转换是否停止
	adc_data = readl((info->regs + SARADC_DATA));				//获取数据
	if(copy_to_user((unsigned int*)arg,&adc_data,sizeof(adc_data)))
		return -EFAULT;
	return 0;
}

static struct file_operations farsight_saradc_ops = {
	.owner		= THIS_MODULE,
	.open		= farsight_saradc_open,
	.release		= farsight_saradc_close, 
	.unlocked_ioctl	= farsight_saradc_ioctl,
};

static const struct of_device_id farsight_saradc_match[] = {
	{.compatible = "rockchip,rk3399-saradc",
	.data = &rk3399_saradc_data,},
	{},
};

MODULE_DEVICE_TABLE(of, farsight_saradc_match);

static int farsight_saradc_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct resource	*mem;
	const struct of_device_id *match;
	int ret;
	if(!(info = kmalloc(sizeof(struct farsight_saradc),GFP_KERNEL)))
		return -ENOMEM;

/*-----------------------------字符设备创建------------------------------------*/	
	cdev_init(&info->cdev,&farsight_saradc_ops);				//初始化字符设备对象
	info->cdev.owner = THIS_MODULE; 					//设置字符设备所属模块
	ret = alloc_chrdev_region(&info->devnum,0,1,"saradcs_reg_device"); 	//申请设备号
	if(ret<0)
	{
		goto out_err_0;
	}
	ret = cdev_add(&info->cdev,info->devnum, 1);				//添加字符设备
	if (ret < 0) 
	{
		goto out_err_1;
	}	
	info->class = class_create(THIS_MODULE,"saradcs_reg_class");		//创建character类
	if (IS_ERR(info->class)) 
	{
		ret = PTR_ERR(info->class);
		goto out_err_2;	
	}
	info->dev = device_create(info->class,NULL,info->devnum,NULL,"adc_ctrl");	//创建字符设备节点
	if (IS_ERR(info->dev)) 
	{
		ret = PTR_ERR(info->dev);
		goto out_err_3;	
	}

/*-----------------------------配置时钟------------------------------------*/	
	if (!np)
		return -ENODEV;	
	match = of_match_device(farsight_saradc_match, &pdev->dev);	//获取设备ID，多设备下使用
	info->data = match->data;
	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);	//获取设备树寄存器地址
	info->regs = devm_ioremap_resource(&pdev->dev, mem);	//寄存器地址映射
	if (IS_ERR(info->regs))
		return PTR_ERR(info->regs);
	info->pclk = devm_clk_get(&pdev->dev, "apb_pclk");
	if (IS_ERR(info->pclk)) 
	{
		dev_err(&pdev->dev, "failed to get pclk\n");
		return PTR_ERR(info->pclk);
	}
	info->clk = devm_clk_get(&pdev->dev, "saradc");
	if (IS_ERR(info->clk)) 
	{
		dev_err(&pdev->dev, "failed to get adc clock\n");
		return PTR_ERR(info->clk);
	}
	ret = clk_set_rate(info->clk, info->data->clk_rate);
	if (ret < 0) 
	{
		dev_err(&pdev->dev, "failed to set adc clk rate, %d\n", ret);
		return ret;
	}
	ret = clk_prepare_enable(info->pclk);
	if (ret < 0) 
	{
		dev_err(&pdev->dev, "failed to enable pclk\n");
		goto err_pclk;
	}
	ret = clk_prepare_enable(info->clk);
	if (ret < 0) 
	{
		dev_err(&pdev->dev, "failed to enable converter clock\n");
		goto err_clk;
	}
	return 0;
err_clk:
	clk_disable_unprepare(info->clk);
err_pclk:
	clk_disable_unprepare(info->pclk);
out_err_3:
	device_del(info->dev);
	class_destroy(info->class);
out_err_2:
	cdev_del(&info->cdev);
out_err_1:
	unregister_chrdev_region(info->devnum,1);
out_err_0:
	kfree(info);
	return ret;
}

static int farsight_saradc_remove(struct platform_device *pdev)
{
	clk_disable_unprepare(info->clk);
	clk_disable_unprepare(info->pclk);
	device_del(info->dev);
	class_destroy(info->class);
	cdev_del(&info->cdev);
	kfree(info);
	unregister_chrdev_region(info->devnum,1);
	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int farsight_saradc_suspend(struct device *dev)
{
	clk_disable_unprepare(info->clk);
	clk_disable_unprepare(info->pclk);
	return 0;
}

static int farsight_saradc_resume(struct device *dev)
{
	int ret;
	ret = clk_prepare_enable(info->pclk);
	if (ret)
		return ret;
	ret = clk_prepare_enable(info->clk);
	if (ret)
		return ret;
	return ret;
}
#endif

static SIMPLE_DEV_PM_OPS(farsight_saradc_pm_ops, farsight_saradc_suspend, farsight_saradc_resume);

static struct platform_driver farsight_saradc_driver = {
	.probe		= farsight_saradc_probe,
	.remove		= farsight_saradc_remove,
	.driver		= {
		.name	= "farsight-saradc",
		.of_match_table = farsight_saradc_match,
		.pm	= &farsight_saradc_pm_ops,
	},
};

static int __init farsight_saradc_init(void) 
{
    	return platform_driver_register(&farsight_saradc_driver);
}

static void __exit farsight_saradc_exit(void) 
{
    	platform_driver_unregister(&farsight_saradc_driver);
}

module_init(farsight_saradc_init);
module_exit(farsight_saradc_exit);

MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
MODULE_DESCRIPTION("farsight SARADC driver");
MODULE_LICENSE("GPL v2");
