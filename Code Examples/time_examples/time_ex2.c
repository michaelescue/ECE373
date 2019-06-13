#include <linux/init.h>
#include <linux/module.h>
#include <linux/timekeeping.h>
#include <linux/delay.h>
#include <linux/jiffies.h>

MODULE_LICENSE("Dual BSD/GPL");

static int __init hello_init(void)
{
    cycles_t cyc_start, cyc_end, cyc;
    
    printk(KERN_INFO "EXAMPLE 2-------------------------\n");

        
    cyc_start = get_cycles();
    printk("cycles at start: %lld", cyc_start);
    cyc_end = cyc_start +  10000;
    cyc = get_cycles();
    while (cyc < cyc_end) {
        cyc = get_cycles();        
    }
    printk("DONE!");
    printk("cycles at end: %lld", cyc);

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "Goodbye, kernel\n");
}

module_init(hello_init);
module_exit(hello_exit);
