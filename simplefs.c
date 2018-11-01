#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init example_init(void) {
printk(KERN_INFO "Hello, World!\n");
return 0;
}
static void __exit example_exit(void) {
printk(KERN_INFO "Goodbye, World!\n");
}

module_init(example_init);
module_exit(example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Doe");
MODULE_DESCRIPTION("A simple Linux kernel module.");
MODULE_VERSION("0.01");

