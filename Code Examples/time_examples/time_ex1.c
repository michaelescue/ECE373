#include <linux/init.h>
#include <linux/module.h>
#include <linux/timekeeping.h>
#include <linux/delay.h>
#include <linux/jiffies.h>

MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello, kernel\n");
    
    printk("HZ: %d", HZ);
    printk("jiffies: %ld", jiffies);
    printk("msecs to jiffies %ld", msecs_to_jiffies(1000));
    printk("nsecs to jiffies %ld", nsecs_to_jiffies(1000000000));
    printk("jiffies to msecs (100) %d", jiffies_to_msecs(msecs_to_jiffies(100)));
    printk("jiffies to msecs (4) %d", jiffies_to_msecs(msecs_to_jiffies(4)));
    printk("jiffies to msecs (1) %d", jiffies_to_msecs(msecs_to_jiffies(1)));

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, kernel\n");
}

module_init(hello_init);
module_exit(hello_exit);
