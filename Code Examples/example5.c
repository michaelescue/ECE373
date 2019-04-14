/*
 * PJ Waskiewicz
 * 6/28/2011
 * ECE 373
 *
 * Example 5: Give stuff to the driver, get stuff from the driver
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEVCNT 5
#define DEVNAME "example5"

static struct mydev_dev {
	struct cdev cdev;
	/* more stuff will go in here later... */
	int sys_int;
} mydev;

static dev_t mydev_node;

/* this shows up under /sys/modules/example5/parameters */
static int exam = 15;
module_param(exam, int, S_IRUSR | S_IWUSR);

/* this doesn't appear in /sys/modules */
static int exam_nosysfs = 15;
module_param(exam_nosysfs, int, 0);

static int example5_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "successfully opened!\n");

	mydev.sys_int = 23;

	return 0;
}

static ssize_t example5_read(struct file *file, char __user *buf,
                             size_t len, loff_t *offset)
{
	/* Get a local kernel buffer set aside */
	int ret;

	if (*offset >= sizeof(int))
		return 0;

	/* Make sure our user wasn't bad... */
	if (!buf) {
		ret = -EINVAL;
		goto out;
	}

	if (copy_to_user(buf, &mydev.sys_int, sizeof(int))) {
		ret = -EFAULT;
		goto out;
	}
	ret = sizeof(int);
	*offset += len;

	/* Good to go, so printk the thingy */
	printk(KERN_INFO "User got from us %d\n", mydev.sys_int);

out:
	return ret;
}

static ssize_t example5_write(struct file *file, const char __user *buf,
                              size_t len, loff_t *offset)
{
	/* Have local kernel memory ready */
	char *kern_buf;
	int ret;

	/* Make sure our user isn't bad... */
	if (!buf) {
		ret = -EINVAL;
		goto out;
	}

	/* Get some memory to copy into... */
	kern_buf = kmalloc(len, GFP_KERNEL);

	/* ...and make sure it's good to go */
	if (!kern_buf) {
		ret = -ENOMEM;
		goto out;
	}

	/* Copy from the user-provided buffer */
	if (copy_from_user(kern_buf, buf, len)) {
		/* uh-oh... */
		ret = -EFAULT;
		goto mem_out;
	}

	ret = len;

	/* print what userspace gave us */
	printk(KERN_INFO "Userspace wrote \"%s\" to us\n", kern_buf);

mem_out:
	kfree(kern_buf);
out:
	return ret;
}

/* File operations for our device */
static struct file_operations mydev_fops = {
	.owner = THIS_MODULE,
	.open = example5_open,
	.read = example5_read,
	.write = example5_write,
};

static int __init example5_init(void)
{
	printk(KERN_INFO "example5 module loading... exam=%d\n", exam);

	if (alloc_chrdev_region(&mydev_node, 0, DEVCNT, DEVNAME)) {
		printk(KERN_ERR "alloc_chrdev_region() failed!\n");
		return -1;
	}

	printk(KERN_INFO "Allocated %d devices at major: %d\n", DEVCNT,
	       MAJOR(mydev_node));

	/* Initialize the character device and add it to the kernel */
	cdev_init(&mydev.cdev, &mydev_fops);
	mydev.cdev.owner = THIS_MODULE;

	if (cdev_add(&mydev.cdev, mydev_node, DEVCNT)) {
		printk(KERN_ERR "cdev_add() failed!\n");
		/* clean up chrdev allocation */
		unregister_chrdev_region(mydev_node, DEVCNT);

		return -1;
	}

	return 0;
}

static void __exit example5_exit(void)
{
	/* destroy the cdev */
	cdev_del(&mydev.cdev);

	/* clean up the devices */
	unregister_chrdev_region(mydev_node, DEVCNT);

	printk(KERN_INFO "example5 module unloaded!\n");
}

MODULE_AUTHOR("PJ Waskiewicz");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");
module_init(example5_init);
module_exit(example5_exit);
