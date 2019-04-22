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

MODULE_LICENSE("Dual BSD/GPL");

#define FIRSTMINOR 0
#define DEV_COUNT 1

dev_t *my_device = NULL;
char my_dev_name[] = "HW2module";

/** Device structure: From example 4 by PJ Waskiewicz   */
 struct my_dev_struct {
	struct cdev cdev;
	dev_t device_node;
} *my_device;

/** File operations structure: From example 4 by PJ Waskiewicz */
static struct file_operations mydev_fops = {
	.owner = my_dev_name,
	.open = example4_open,
}

/** Initiate/create module   */
static int __init hello_init(void){
    printk(KERN_INFO "Hello, kernel-HW2\n");

    /** Dynamically allocate the device file pointer.    */
    if (alloc_chrdev_region(my_device.device_node, FIRSTMINOR, DEV_COUNT, my_dev_name)) {
		printk(KERN_ERR "Device allocation failed.\n");
		return -1;
	}

    /** Print to kernel the my_device major and minor numbers of my_device. */
    printk(KERN_INFO "Major number: %d, Minor number: %d\n",
        MAJOR(*my_device.device_node), MINOR(*my_device.device_node));

    return 0;
}

static void __exit hello_exit(void){
    printk(KERN_INFO "Goodbye, kernel-HW2\n");
    
    /** Free allocated memory for device file.  */
    unregister_chrdev_region(*my_device.device_node, DEV_COUNT);

   // No return, void function;
}


module_init(hello_init);

module_exit(hello_exit);

