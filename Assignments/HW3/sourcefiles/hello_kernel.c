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

#define FIRSTMINOR 1
#define DEV_COUNT 1
#define MYDEV_SYSCALL_VAL 40
#define BUF_SIZE 256

static int x = 0;


/** Function prototypes */
ssize_t rfile(struct file *file, char __user *buf, size_t len, loff_t *offset);


ssize_t wfile(struct file *file, const char __user *buf, size_t len, loff_t *offset);


int fopen(struct inode *inode, struct file *file);


int frelease(struct inode *inode, struct file *indoe);


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
    .open = fopen,
    .release = frelease,
};

int fopen(struct inode *inode, struct file *file){
    printk(KERN_INFO "Goodbye, kernel file open-HW2\n");
    return 0;
}

int frelease(struct inode *inode, struct file *file){
    printk(KERN_INFO "Goodbye, kernel file closed-HW2\n");
    return 0;
}


ssize_t rfile(struct file *file, char __user *buf, size_t len, loff_t *offset){
    
	/*
	*	_copy_to_user(void __user *to, const void *from, unsigned long n)
	*/
	
    if(copy_to_user(buf, &my_device.syscall_val, len)){
	    printk(KERN_ERR "copy_to_user Error.\n");
        return -EFAULT;
    }

    printk(KERN_INFO "my_device pointer to *buf.");  


    return 0;
}

ssize_t wfile(struct file *file, const char __user *buf, size_t len, loff_t *offset){
    char * kbuffer;

    if((kbuffer = kmalloc(len, GFP_KERNEL))){
        printk(KERN_ERR "kmalloc Error.\n");
        return -ENOMEM;
    }

	/*
	*	copy_from_user(void *to, const void __user *from, unsigned long n)
	*/
	
    if(copy_from_user(kbuffer, buf, len)){
	    printk(KERN_ERR "copy_to_user Error.\n");
        return -EFAULT;
    }

    //operations using kbuffer

    kfree(kbuffer);    

    return 0;
}

/** Module initialization   */
static int __init hello_init(void){
    printk(KERN_INFO "Hello, kernel-HW2\n");

/** Dynamically allocate the device file pointer.    */
    if ((x = alloc_chrdev_region(&my_device.device_node, FIRSTMINOR,
        DEV_COUNT, "hello_kernel"))) {
		printk(KERN_ERR "Device allocation error.\n\t");
		return -1;
	}

        printk(KERN_INFO "Hello, kernel has mad it past allocation-HW2 = %d\n", x);


/** Print to kernel the my_device major and minor numbers of my_device. */
    printk(KERN_INFO "Major number: %d, Minor number: %d\n",
        MAJOR(my_device.device_node), MINOR(my_device.device_node));

/** Initialize char device: Void function  */
    cdev_init(&my_device.my_cdev, &mydev_fops);

    printk(KERN_INFO "Hello, kernel has mad it past initialization-HW2 = %d\n", x);


/** Add chard device to kernel fs   */
    if((x = cdev_add(&my_device.my_cdev, my_device.device_node, DEV_COUNT))){
        printk(KERN_ERR "Char device add Error.\n\t");
        
    /** clean up chrdev allocation */
        unregister_chrdev_region(my_device.device_node, DEV_COUNT);
		return -1;
    }
            
    printk(KERN_INFO "Hello, kernel has been added-HW2 = %d\n", x);

    my_device.syscall_val = MYDEV_SYSCALL_VAL;

    printk(KERN_INFO "Hello, kernel syscall_val = %d-HW2\n", my_device.syscall_val);


    return 0;
}

/** Moduel exit */
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

