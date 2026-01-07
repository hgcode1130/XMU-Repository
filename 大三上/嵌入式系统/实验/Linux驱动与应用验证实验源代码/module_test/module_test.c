//------------------------------------内核模块测试程序--------------------------
#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_init(void)
{
	printk("hello init\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk("hello exit\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_ALIAS("hqyj:module");
MODULE_AUTHOR("HQYJ <yanfa@hqyj.com>");
MODULE_DESCRIPTION("A sample Hello World module");

