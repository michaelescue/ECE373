/*
 * PJ Waskiewicz
 * 6/28/2011
 * ECE 373
 *
 * Example 4: Hook up the char driver!
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEVCNT 5
#define DEVNAME "example4"

/* function prototypes - forward declaration */
static int example4_open(struct inode *inode, struct file *file);

static struct mydev_dev {
	struct cdev cdev;
	dev_t mydev_node;
	/* more stuff will go in here later... */
} mydev;

/* File operations for our device */
static struct file_operations mydev_fops = {
	.owner = THIS_MODULE,
	.open = example4_open,
};

static int example4_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "pop goes the example!\n");

	return 0;
}

int __init example4_init(void)
{
	printk(KERN_INFO "example4 module loading...\n");

	if (alloc_chrdev_region(&mydev.mydev_node, 0, DEVCNT, DEVNAME)) {
		printk(KERN_ERR "alloc_chrdev_region() failed!\n");
		return -1;
	}

	printk(KERN_INFO "Allocated %d devices at major: %d\n", DEVCNT,
	       MAJOR(mydev.mydev_node));

	/* Initialize the character device and add it to the kernel */
	cdev_init(&mydev.cdev, &mydev_fops);
	mydev.cdev.owner = THIS_MODULE;

	if (cdev_add(&mydev.cdev, mydev.mydev_node, DEVCNT)) {
		printk(KERN_ERR "cdev_add() failed!\n");
		/* clean up chrdev allocation */
		unregister_chrdev_region(mydev.mydev_node, DEVCNT);

		return -1;
	}

	return 0;
}

void __exit example4_exit(void)
{
	/* destroy the cdev */
	cdev_del(&mydev.cdev);

	/* clean up the devices */
	unregister_chrdev_region(mydev.mydev_node, DEVCNT);

	printk(KERN_INFO "example4 module unloaded!\n");
}

MODULE_AUTHOR("PJ Waskiewicz");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
module_init(example4_init);
module_exit(example4_exit);
