/**
 * @file hw2notes.c	
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-04-22
 * 
 * @copyright Copyright (c) 2019
 * 
 * BEGIN:
 * 
 *** 	_init function order:
 * 	X	1.	Allocate char device node.
 * 	X	2.	printk message for allocated Major, Minor numbers.
 * 	X	3.	cdev_init char device with file operations.
 * 
 *** 		void cdev_init(struct cdev *cdev, struct file_operations *fops)
 * 	
 * 	X	4.	cdev_add module with printk error checking.
 * 	X		a.	error checking should free the allocated char space on error.
 * 
 *** 		int cdev_add(struct cdev *cdev, dev_t num, unsigned int count)
 * 
 * 	X	5.	return.
 * 
 ***	_exit function order:
 * 	X	1.	cdev_del the char device to remove the link.
 * 
 *** 		void cdev_del(struct cdev *cdev)
 * 
 * 	X	2.	free the allocated char space.
 * 
 ***	struct mydev_dev{
 ***			struct	cdev cdev;
 *** 			dev_t	mydev_node;
 *** 		}mydev
 * 
 * 	-	mydev_dev structure is used in allocation, printk Major/Minor, "cdev_add",
 * 		and "cdev_delete".
 * 
 *** 	struct file_operations mydev_fops = {
 *** 		.owner = THIS_MODULE,
 *** 		.open = example4_open,
 *** 	}
 * 
 * 	-	mydev_fops structure is used for the "cdev_init". 
 * 
 ***	wfile function order:
 * 		1.	copy from user buffer.
 * 			a. use "kmalloc" to allocate kernel buffer.
 * 
 ***	void *kmalloc(size_t size, gfp_t flags)
 * 
 * 			b. use "copy_from_user" to copy user buffer.
 * 
 ***		copy_from_user(void *to, const void __user *from, unsigned long n) 
 * 
 * 		2.	Perform functions.
 * 		3.	free kernel buffer memory allocated.
 * 			a. use "kfree" to release allocated memory.
 * 
 ***	void kfree(const void *);
 * 
 * 
 ***	rfile function order:
 * 		1.	copy from kernel buffer to user buffer.
 *  		b. use "copy_to_user" to copy user buffer.
 * 
 ***		copy_to_user(void __user *to, const void *from, unsigned long n)
 * 
 * 		2.	Perform functions. 
 */


#include <linux/cdev.h>
/**
 * @brief Represents char devices inside the kernel.
 * 
 * cdev initialized with cdev_init, added with cdev_add,
 * and cleaned up with cdev_del.
 * 
 */
struct cdev {
	struct kobject kobj;
	struct module *owner;
	const struct file_operations *ops;
	struct list_head list;
	dev_t dev;
	unsigned int count;
} __randomize_layout;

void cdev_init(struct cdev *cdev, struct file_operations *fops)

/** Adding a char device.
 * file_operations must be configured and ready to go before “cdev_add()”
 * */
int cdev_add(struct cdev *cdev, dev_t num, unsigned int count)

void cdev_del(struct cdev *cdev)

#include <linux/fs.h>
/**
 * @brief Provides function pointers into system call interface.
 * 
 */
struct file_operations {
	struct module *owner;
	loff_t (*llseek) (struct file *, loff_t, int);

	/** Read used in HW2	*/
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	/** Write used in HW2	*/
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);

	ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
	ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
	int (*iterate) (struct file *, struct dir_context *);
	int (*iterate_shared) (struct file *, struct dir_context *);
	__poll_t (*poll) (struct file *, struct poll_table_struct *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	unsigned long mmap_supported_flags;

	int (*open) (struct inode *, struct file *);
	int (*flush) (struct file *, fl_owner_t id);
	int (*release) (struct inode *, struct file *);
	int (*fsync) (struct file *, loff_t, loff_t, int datasync);
	int (*fasync) (int, struct file *, int);
	int (*lock) (struct file *, int, struct file_lock *);
	ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*setlease)(struct file *, long, struct file_lock **, void **);
	long (*fallocate)(struct file *file, int mode, loff_t offset,
			  loff_t len);
	void (*show_fdinfo)(struct seq_file *m, struct file *f);
#ifndef CONFIG_MMU
	unsigned (*mmap_capabilities)(struct file *);
#endif
	ssize_t (*copy_file_range)(struct file *, loff_t, struct file *,
			loff_t, size_t, unsigned int);
	loff_t (*remap_file_range)(struct file *file_in, loff_t pos_in,
				   struct file *file_out, loff_t pos_out,
				   loff_t len, unsigned int remap_flags);
	int (*fadvise)(struct file *, loff_t, loff_t, int);
} __randomize_layout;