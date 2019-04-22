/**
 * @file hello_kernel.c
 * @author Michael Escue
 * @brief A file for implementing hello module.
 * @version 0.1
 * @date 2019-04-14
 * 
 * @Code sections based on example code provided by Peter (PJ) Waskiewicz
 * 
 */

/** Include Files for kernel interaction: 
 *  -   From example 4 by PJ Waskiewicz
 *  -   From Lecture 06 - Driver Intro - part 2 - cross compile hints
*/
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>


MODULE_LICENSE("Dual BSD/GPL");

#define FIRSTMINOR 0
#define DEV_COUNT 1
#define MYDEV_SYSCALL_VAL 40


/**
 * @brief 
 * 
 * @param __user 
 * @param len 
 * @return int 
 */
ssize_t rfile(struct file *file, char __user *buf, size_t len, loff_t *offset);

/**
 * @brief 
 * 
 * @param __user 
 * @param len 
 * @return int 
 */
ssize_t wfile(struct file *file, const char __user *buf, size_t len, loff_t *offset);


/** Device structure: From example 4 by PJ Waskiewicz   */
static struct my_dev_struct {
	struct cdev my_cdev;
	dev_t device_node;
    int syscall_val;
} my_device;

/** File operations structure: From example 4 by PJ Waskiewicz */
static struct file_operations mydev_fops = {
	.owner = THIS_MODULE,
    .write = wfile,
    .read = rfile,
};


ssize_t rfile(struct file *file, char __user *buf, size_t len, loff_t *offset){
    
    if(copy_to_user(buf, &my_device.syscall_val, sizeof(int))){
	    printk(KERN_ERR "copy_to_user Error.\n");
        return -EFAULT;
    }

    return 0;
}

ssize_t wfile(struct file *file, const char __user *buf, size_t len, loff_t *offset){
    char * kbuffer;

    if((kbuffer = kmalloc(len, GFP_KERNEL))){
        printk(KERN_ERR "kmalloc Error.\n");
        return -ENOMEM;
    }

    if(copy_from_user(kbuffer, buf, sizeof(int))){
	    printk(KERN_ERR "copy_to_user Error.\n");
        return -EFAULT;
    }

    //operations using kbuffer

    kfree(kbuffer);    

    return 0;
}

/**
 * @brief 
 * 
 * @return int hello_init exit status.
 */
static int __init hello_init(void){
    printk(KERN_INFO "Hello, kernel-HW2\n");

    /** Dynamically allocate the device file pointer.    */
    if (alloc_chrdev_region(&my_device.device_node, FIRSTMINOR,
        DEV_COUNT, "HW2mod")) {
		printk(KERN_ERR "Device allocation error.\n");
		return -1;
	}

    /** Print to kernel the my_device major and minor numbers of my_device. */
    printk(KERN_INFO "Major number: %d, Minor number: %d\n",
        MAJOR(my_device.device_node), MINOR(my_device.device_node));

    /** Initialize char device  */
    cdev_init(&my_device.my_cdev, &mydev_fops);

    /** Add chard device to kernel fs   */
    if(cdev_add(&my_device.my_cdev, my_device.device_node, DEV_COUNT)){
        printk(KERN_ERR "Char device add Error.\n");
		/* clean up chrdev allocation */
        unregister_chrdev_region(my_device.device_node, DEV_COUNT);

		return -1;
    }

    my_device.syscall_val = MYDEV_SYSCALL_VAL;

    return 0;
}

/**
 * @brief 
 * 
 */
static void __exit hello_exit(void){
    printk(KERN_INFO "Goodbye, kernel-HW2\n");
    
    /** Delete the initialized char device  */
    cdev_del(&my_device.my_cdev);

    /** Free allocated memory for device file.  */
    unregister_chrdev_region(my_device.device_node, DEV_COUNT);

   // No return, void function;
}


module_init(hello_init);

module_exit(hello_exit);

