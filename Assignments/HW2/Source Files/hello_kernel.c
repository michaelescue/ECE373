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

static int __init hello_init(void){
    printk(KERN_INFO "Hello, kernel\n");
    return 0;
}
static void __exit hello_exit(void){
    printk(KERN_INFO "Goodbye, kernel\n");
}
module_init(hello_init);
module_exit(hello_exit);