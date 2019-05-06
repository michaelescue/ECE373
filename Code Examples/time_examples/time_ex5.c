#include <linux/init.h>
#include <linux/module.h>
#include <linux/timekeeping.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/timer.h>

MODULE_LICENSE("Dual BSD/GPL");

static struct timer_list my_timer;

void my_callback(struct timer_list *list) {
    struct timespec tm; 
    printk("callback was called!!");
    tm = current_kernel_time();
    printk("current num secs (from callback): %ld", tm.tv_sec);
}

static int __init hello_init(void)
{
    struct timespec tm;

    printk(KERN_INFO "EXAMPLE 5-------------------------\n");
    
    tm = current_kernel_time();
    printk("current num secs (from init): %ld", tm.tv_sec);
    timer_setup(&my_timer, my_callback, 0);
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(4000));

    return 0;
}

static void __exit hello_exit(void)
{
    del_timer(&my_timer);
    printk(KERN_INFO "Goodbye, kernel\n");
}

module_init(hello_init);
module_exit(hello_exit);
