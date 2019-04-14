/*
 * PJ Waskiewicz
 * 6/28/2011
 * ECE 373
 *
 * Example 2: Register a device node
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

#define DEVCNT 5
static dev_t mydev_node;

int __init example2_init(void)
{
	printk(KERN_INFO "example2 module loading...\n");

	mydev_node = 0xff00000; /* DON'T DO THIS!! */

	if (register_chrdev_region(mydev_node, DEVCNT, "example2")) {
		printk(KERN_ERR "Register chardev failed!\n");
		return -1;
	}

	return 0;
}

void __exit example2_exit(void)
{
	/* clean up the devices */
	unregister_chrdev_region(mydev_node, DEVCNT);

	printk(KERN_INFO "example2 module unloaded!\n");
}

MODULE_AUTHOR("PJ Waskiewicz");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
module_init(example2_init);
module_exit(example2_exit);
