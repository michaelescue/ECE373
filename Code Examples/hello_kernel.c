/*
 * PJ Waskiewicz
 * 6/28/2011
 * ECE 373
 *
 * Hi kernel!
 */

#include <linux/module.h>
#include <linux/types.h>

static int __init hello_init(void)
{
	printk(KERN_INFO "hello kernel!\n");

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "goodbye kernel!\n");
}

MODULE_AUTHOR("PJ Waskiewicz");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
module_init(hello_init);
module_exit(hello_exit);
