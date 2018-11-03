#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#define DEBUG 1
#include <linux/dcache.h>
#include <linux/fs.h>

static struct dentry *simplefs_mount(struct file_system_type *fs_type,
                     int flags, const char *dev_name, void *data);

static struct file_system_type simplefs_type = {
    .owner = THIS_MODULE,
	.name = "simplefs",
	.mount = simplefs_mount,
//	.kill_sb = kill_litter_super,
};

int simplefs_fill_super(struct super_block *sb, void *data, int silent)
{
    printk(KERN_INFO "Fill in superblock for simplefs\n");
    return 0;
}

static struct dentry *simplefs_mount(struct file_system_type *fs_type,
                     int flags, const char *dev_name,
                     void *data)
{
    struct dentry *ret;

    ret = mount_bdev(fs_type, flags, dev_name, data, simplefs_fill_super);

    if (unlikely(IS_ERR(ret)))
        printk(KERN_ERR "Error mounting simplefs");
    else
        printk(KERN_INFO "simplefs is succesfully mounted on [%s]\n",
               dev_name);

    return ret;
}

static int __init example_init(void) {
    int err = 0;
    printk(KERN_INFO "Hello, World!\n");
    err = register_filesystem(&simplefs_type);
    if (err) {
        printk(KERN_ERR "simplefs: unable to register filesystem (err %i)\n", err);
    }
    return 0;
}

static void __exit example_exit(void) {
    printk(KERN_INFO "Goodbye, World!\n");
    unregister_filesystem(&simplefs_type);
}

module_init(example_init);
module_exit(example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Doe");
MODULE_DESCRIPTION("A simple Linux kernel module.");
MODULE_VERSION("0.01");

