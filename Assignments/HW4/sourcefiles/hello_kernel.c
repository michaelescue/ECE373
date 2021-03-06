/**
 * @file hello_kernel.c
 * @author Michael Escue
 * @brief A file for implementing hello module.
 * @version 0.1
 * @date 2019-04-24
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
#include <linux/pci.h>

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

int frelease(struct inode *inode, struct file *file);

static int pci_blinkdriver_probe(struct pci_dev *pdev, const struct pci_device_id *ent);

static void pci_blinkdriver_remove(struct pci_dev *pdev);

/** Device structure: From example 4 by PJ Waskiewicz   */
static struct my_dev_struct {
	struct cdev my_cdev;
	dev_t device_node;
    unsigned int syscall_val;
    long led_initial_val;
} my_device;

/** PCI structs from Apr 24 lecture */
static const struct pci_device_id pci_blinkdrivertable[] = {
    { PCI_DEVICE(0x8086, 0x100e)},
    {},
};

static struct pci_driver pci_blinkdriver = {
    .name = "blinkdriver",
    .id_table = pci_blinkdrivertable,
    .probe = pci_blinkdriver_probe,     // called when pci subsystem gets capable device
    .remove = pci_blinkdriver_remove,
};

static struct mypci {
    struct pci_dev *pdev;
    void *hw_addr;
} mypci;

/** File operations structure: From example 4 by PJ Waskiewicz */
static struct file_operations mydev_fops = {
	.owner = THIS_MODULE,
    .write = wfile,
    .read = rfile,
    .open = fopen,
    .release = frelease,
};

int fopen(struct inode *inode, struct file *file){
    printk(KERN_INFO "Kernel:File Opened.\n");
    return 0;
}

int frelease(struct inode *inode, struct file *file){
    printk(KERN_INFO "Kernel:File Closed.\n");
    return 0;
}

/** PCI operations from Apr 24/29 lecture  */

static int pci_blinkdriver_probe(struct pci_dev *pdev, const struct pci_device_id *ent){

    resource_size_t mmio_start, mmio_len;
    unsigned long barmask;

    printk(KERN_INFO "Blink driver probe called.\n");

    // get bar mask.

    barmask = pci_select_bars(pdev, IORESOURCE_MEM);
    
    printk(KERN_INFO "barmask %lx", barmask);

    if(pci_request_selected_regions(pdev, barmask, "blinkdriver")) {

        printk(KERN_ERR "request selected region failed.\n");

        goto unregister_selected_regions;

    }

    mmio_start = pci_resource_start(pdev, 0);
    mmio_len = pci_resource_len(pdev, 0);

    printk(KERN_INFO "mmio start: %lx", (unsigned long) mmio_start);

    printk(KERN_INFO "mmio len: %lx", (unsigned long) mmio_len);

    if(!(mypci.hw_addr = ioremap(mmio_start, mmio_len))) {
        
        printk(KERN_ERR "ioremap failed\n");

        goto unregister_ioremap;
    }

    // working

    my_device.led_initial_val = readl(mypci.hw_addr + 0xE00);

    printk(KERN_INFO "initial val is %lx\n", my_device.led_initial_val);

    return 0;

    unregister_ioremap:
        iounmap(mypci.hw_addr);

    unregister_selected_regions:
        pci_release_selected_regions(pdev, pci_select_bars(pdev, IORESOURCE_MEM));
        return -1;
}

static void pci_blinkdriver_remove(struct pci_dev *pdev) {
    printk(KERN_INFO "Removing PCI driver.\n");
    iounmap(mypci.hw_addr);
    pci_release_selected_regions(pdev, pci_select_bars(pdev, IORESOURCE_MEM));
}

/** System call functions   */
ssize_t rfile(struct file *file, char __user *buf, size_t len, loff_t *offset){
    
    /* Read from device */
    my_device.syscall_val = readl(mypci.hw_addr + 0xE00);

	/*
	*	_copy_to_user(void __user *to, const void *from, unsigned long n)
	*/
	
    if(copy_to_user(buf, &my_device.syscall_val, len)){
	    printk(KERN_ERR "copy_to_user Error.\n");
        return -EFAULT;
    }

    return 0;
}

ssize_t wfile(struct file *file, const char __user *buf, size_t len, loff_t *offset){

    int *kbuffer;

    if((kbuffer = kmalloc(len, GFP_KERNEL)) == NULL){
        printk(KERN_ERR "kmalloc Error.\n");
        printk("kbuffer = %d\n", kbuffer[0]);
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

    my_device.syscall_val = *kbuffer;

    printk(KERN_INFO "Kernel: write syscall_val = %x\n", my_device.syscall_val);

    /* Writing to device    */
    writel(my_device.syscall_val, mypci.hw_addr + 0xE00);

    kfree(kbuffer);    

    return 0;
}

/** Module initialization   */
static int __init hello_init(void){
    printk(KERN_INFO "Hello, kernel driver initializing.\n");

/** Dynamically allocate the device file pointer.    */
    if ((x = alloc_chrdev_region(&my_device.device_node, FIRSTMINOR,
        DEV_COUNT, "hellokernel"))) {
		printk(KERN_ERR "Device allocation error.\n\t");
		return -1;
	}

        printk(KERN_INFO "Kernel: Driver dev_t successfully allocated. Return = %d\n", x);


/** Print to kernel the my_device major and minor numbers of my_device. */
    printk(KERN_INFO "Major number: %d, Minor number: %d\n",
        MAJOR(my_device.device_node), MINOR(my_device.device_node));

/** Initialize char device: Void function  */
    cdev_init(&my_device.my_cdev, &mydev_fops);

    printk(KERN_INFO "Kernel: cdev struct initialized. Return = %d\n", x);


/** Add chard device to kernel fs   */
    if((x = cdev_add(&my_device.my_cdev, my_device.device_node, DEV_COUNT))){
        printk(KERN_ERR "Char device add Error.\n\t");
        
    /** clean up chrdev allocation if add fails */
        unregister_chrdev_region(my_device.device_node, DEV_COUNT);
		return -1;
    }

/* register driver as pci   */

   if(pci_register_driver(&pci_blinkdriver)){
        printk(KERN_ERR "pci register failed.\n");
        goto unreg_pci_driver;
    }
            
    printk(KERN_INFO "Kernel: cdev added with dev_t node. Return = %d\n", x);

    my_device.syscall_val = MYDEV_SYSCALL_VAL;

    printk(KERN_INFO "Kernel: syscall_val = %d\n", my_device.syscall_val);

    return 0;

    unreg_pci_driver:
        pci_unregister_driver(&pci_blinkdriver);

        unregister_chrdev_region(my_device.device_node, DEV_COUNT);
        return -1;
}

/** Module exit */
static void __exit hello_exit(void){
    printk(KERN_INFO "Kernel: Goodby, driver deleted and unregistered.\n");
    
    /** Delete the initialized char device  */
    cdev_del(&my_device.my_cdev);

    /* remove PCI driver */
    pci_unregister_driver(&pci_blinkdriver);


    /** Free allocated memory for device file.  */
    unregister_chrdev_region(my_device.device_node, DEV_COUNT);

   // No return, void function;
}

module_init(hello_init);

module_exit(hello_exit);

