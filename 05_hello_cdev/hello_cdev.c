#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;

static ssize_t my_read(struct file *f, char __user *u, size_t l, loff_t *o) {
	printk("hello_cdev: Read called\n");
	return 0;
}

static struct file_operations fops = {
	.read = my_read
};

static int __init my_init(void) {
	major = register_chrdev(0, "hello_cdev", &fops);
	if(major < 0) {
		printk("hello_cdev - Error registering device\n");
		return major;
	}
	printk("hello_cdev - Registered device. (Major = %d)\n", major);
	return 0;
}

static void __exit my_exit(void) {
	unregister_chrdev(major, "hello_cdev");
	printk("hello_cdev - Goodbye Kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vilas Chitrakaran");
MODULE_DESCRIPTION("A sample driver for registering a character device");

