#include <linux/init.h>
#include <linux/module.h>
#include <linux/timekeeping.h>
#include <linux/delay.h>
#include <linux/jiffies.h>

MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
    struct timespec tm1, tm2;

    printk(KERN_INFO "EXAMPLE 4-------------------------\n");
     
    tm1 = current_kernel_time();
    printk("get time of day tv_sec: %ld", tm1.tv_sec);    
    printk("get time of day tv_nsec: %ld", tm1.tv_nsec);
        
    mdelay(3000);

    tm2 = current_kernel_time();
    printk("get time of day tv_sec: %ld", tm2.tv_sec);    
    printk("get time of day tv_nsec: %ld", tm2.tv_nsec);

    printk("difference in secs: %ld", tm2.tv_sec - tm1.tv_sec);

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, kernel\n");
}

module_init(hello_init);
module_exit(hello_exit);
