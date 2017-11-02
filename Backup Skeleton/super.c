
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

static unsigned long const exfs_MAGIC_NUMBER = 0x13131313;

static void exfs_put_super(struct super_block *sb)
{
	pr_debug("exfs super block destroyed\n");
}

static struct super_operations const exfs_super_ops = {
	.put_super = exfs_put_super,
};

static int exfs_fill_sb(struct super_block *sb, void *data, int silent)
{
	struct inode *root = NULL;

	sb->s_magic = exfs_MAGIC_NUMBER;
	sb->s_op = &exfs_super_ops;

	root = new_inode(sb);
	if (!root)
	{
		pr_err("inode allocation failed\n");
		return -ENOMEM;
	}

	root->i_ino = 0;
	root->i_sb = sb;
	root->i_atime = root->i_mtime = root->i_ctime = CURRENT_TIME;
	inode_init_owner(root, NULL, S_IFDIR);

	sb->s_root = d_make_root(root);
	if (!sb->s_root)
	{
		pr_err("root creation failed\n");
		return -ENOMEM;
	}

	return 0;
}

static struct dentry *exfs_mount(struct file_system_type *type, int flags,
									char const *dev, void *data)
{
	struct dentry *const entry = mount_bdev(type, flags, dev,
											data, exfs_fill_sb);
	if (IS_ERR(entry))
		pr_err("exfs mounting failed\n");
	else
		pr_debug("exfs mounted\n");
	return entry;
}

static struct file_system_type exfs_type = {
	.owner = THIS_MODULE,
	.name = "exfs",
	.mount = exfs_mount,
	.kill_sb = kill_block_super,
	.fs_flags = FS_REQUIRES_DEV
};

static int __init exfs_init(void)
{
	int const ret = register_filesystem(&exfs_type);
	if (ret == 0)
		pr_debug("exfs module loaded\n");
	else
		pr_err("cannot register filesystem\n");
	return ret;
}

static void __exit exfs_fini(void)
{
	int const ret = unregister_filesystem(&exfs_type);
	if (ret != 0)
		pr_err("cannot unregister filesystem\n");
	pr_debug("exfs module unloaded\n");
}

module_init(exfs_init);
module_exit(exfs_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nandu");
