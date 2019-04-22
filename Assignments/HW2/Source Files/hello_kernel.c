/**
 * @file hello.c
 * @author Michael Escue
 * @brief A file for implementing hello module.
 * @version 0.1
 * @date 2019-04-14
 * 
 * @Code provided by Peter (PJ) Waskiewicz
 * 
 */

#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

#define FIRSTMINOR 0
#define DEV_COUNT 1


dev_t *my_device = NULL;
char my_dev_name[] = "HW2module";

static int __init hello_init(void){
    printk(KERN_INFO "Hello, kernel-HW2\n");

    /** Dynamically allocate the device file pointer.    */
    if (alloc_chrdev_region(my_device, FIRSTMINOR, DEV_COUNT, my_dev_name)) {
		printk(KERN_ERR "Device allocation failed.\n");
		return -1;
	}

    /** Print to kernel the my_device major and minor numbers of my_device. */
    printk(KERN_INFO "Major number: %d, Minor number: %d\n",
        MAJOR(my_device), MINOR(my_device));

    return 0;
}

static void __exit hello_exit(void){
    printk(KERN_INFO "Goodbye, kernel-HW2\n");
    
    /** Free allocated memory for device file.  */
    unregister_chrdev_region(my_device, DEV_COUNT);

}

void unregister_chrdev_region(dev_t first, unsigned int count);

int alloc_chrdev_region(dev_t *dev, unsigned int firstminor, unsigned int count, char *name);

module_init(hello_init);

module_exit(hello_exit);

