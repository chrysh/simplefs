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
	.kill_sb = kill_block_super,
};

#define SIMPLEFS_MAGIC_NUMBER 0xdeadbeef

static void simplefs_put_super(struct super_block *sb)
{
    pr_debug("%s: simplefs super block destroyed\n", __FILE__);
}

static struct super_operations const simplefs_super_ops = {
    .put_super = simplefs_put_super,
};

int simplefs_fill_super(struct super_block *sb, void *data, int silent)
{
    struct inode *root = NULL;
    printk(KERN_INFO "Fill in superblock for simplefs\n");

    sb->s_magic = SIMPLEFS_MAGIC_NUMBER;
    sb->s_op = &simplefs_super_ops;

    root = new_inode(sb);
    if (!root)
    {
        pr_err("%s: %s failed\n", __FILE__, __FUNCTION__);
        return -ENOMEM;
    }

    root->i_ino = 0;
    root->i_sb = sb;
    //root->i_atime = root->i_mtime = root->i_ctime = 123456;
    inode_init_owner(root, NULL, S_IFDIR);

    sb->s_root = d_make_root(root);
    if (!sb->s_root)
    {
        pr_err("root creation failed\n");
        return -ENOMEM;
    }
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

