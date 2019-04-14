/*
 * PJ Waskiewicz
 * 6/28/2011
 * ECE 373
 *
 * Example 3: Dynamically allocate a device node
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

#define DEVCNT 5
static dev_t mydev_node;

int __init example3_init(void)
{
	printk(KERN_INFO "example3 module loading...\n");

	if (alloc_chrdev_region(&mydev_node, 0, DEVCNT, "example3")) {
		printk(KERN_ERR "alloc_chrdev_region() failed!\n");
		return -1;
	}

	printk(KERN_INFO "Allocated %d devices at major: %d\n", DEVCNT,
	       MAJOR(mydev_node));

	return 0;
}

void __exit example3_exit(void)
{
	/* clean up the devices */
	unregister_chrdev_region(mydev_node, DEVCNT);

	printk(KERN_INFO "example3 module unloaded!\n");
}

MODULE_AUTHOR("PJ Waskiewicz");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
module_init(example3_init);
module_exit(example3_exit);
