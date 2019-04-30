
#include <cdev.h>

struct cdev{
    struct kobject kobj;
    struct module *owner;
    const struct file_operations *ops;
    struct list_head list;
    dev_t dev;
    unsigned in count;    
}
