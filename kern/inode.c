#include <linux/buffer_head.h>
#include <linux/slab.h>

#include "exfs.h"
#include "inode.h"
#include "super.h"

static struct kmem_cache *exfs_inode_cache = NULL;

static void exfs_inode_fill(struct exfs_inode *ai,
			struct exfs_disk_inode const *di)
{
	ai->ai_block = be32_to_cpu(di->di_first);
	ai->ai_inode.i_mode = be32_to_cpu(di->di_mode);
	ai->ai_inode.i_size = be32_to_cpu(di->di_size);
	ai->ai_inode.i_blocks = be32_to_cpu(di->di_blocks);
	ai->ai_inode.i_ctime.tv_sec = (uint32_t)be64_to_cpu(di->di_ctime);
	ai->ai_inode.i_mtime.tv_sec = ai->ai_inode.i_atime.tv_sec =
				ai->ai_inode.i_ctime.tv_sec;
	ai->ai_inode.i_mtime.tv_nsec = ai->ai_inode.i_atime.tv_nsec =
				ai->ai_inode.i_ctime.tv_nsec = 0;
	i_uid_write(&ai->ai_inode, (uid_t)be32_to_cpu(di->di_uid));
	i_gid_write(&ai->ai_inode, (gid_t)be32_to_cpu(di->di_gid));
}

static inline sector_t exfs_inode_block(struct exfs_super_block const *asb,
			uint32_t inode_no)
{
	return (sector_t)(3 + inode_no / asb->asb_inodes_in_block);
}

static size_t exfs_inode_offset(struct exfs_super_block const *asb,
			uint32_t inode_no)
{
	return sizeof(struct exfs_disk_inode) *
				(inode_no % asb->asb_inodes_in_block);
}

struct inode *exfs_inode_get(struct super_block *sb, uint32_t no)
{
	struct exfs_super_block const *const asb = exfs_SB(sb);
	struct buffer_head *bh = NULL;
	struct exfs_disk_inode *di = NULL;
	struct exfs_inode *ai = NULL;
	struct inode *inode = NULL;
	uint32_t block = 0, offset = 0;

	inode = iget_locked(sb, no);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (!(inode->i_state & I_NEW))
		return inode;

	ai = exfs_INODE(inode);
	block = exfs_inode_block(asb, no);
	offset = exfs_inode_offset(asb, no);

	pr_debug("exfs reads inode %u from %u block with offset %u\n",
				(unsigned)no, (unsigned)block,
				(unsigned)offset);

	bh = sb_bread(sb, block);
	if (!bh)
	{
		pr_err("cannot read block %u\n", (unsigned)block);
		goto read_error;
	}

	di = (struct exfs_disk_inode *)(bh->b_data + offset);
	exfs_inode_fill(ai, di);
	brelse(bh);

	pr_debug("exfs inode %u info:\n"
				"\tsize   = %u\n"
				"\tblock  = %u\n"
				"\tblocks = %u\n"
				"\tuid    = %u\n"
				"\tgid    = %u\n"
				"\tmode   = %o\n",
				(unsigned)inode->i_ino,
				(unsigned)inode->i_size,
				(unsigned)ai->ai_block,
				(unsigned)inode->i_blocks,
				(unsigned)i_uid_read(inode),
				(unsigned)i_gid_read(inode),
				(unsigned)inode->i_mode);

	unlock_new_inode(inode);

	return inode;

read_error:
	pr_err("exfs cannot read inode %u\n", (unsigned)no);
	iget_failed(inode);

	return ERR_PTR(-EIO);
}

struct inode *exfs_inode_alloc(struct super_block *sb)
{
	struct exfs_inode *const i = (struct exfs_inode *)
				kmem_cache_alloc(exfs_inode_cache, GFP_KERNEL);

	if (!i)
		return NULL;

	i->ai_inode.i_sb = sb;
	return &i->ai_inode;
}

static void exfs_free_callback(struct rcu_head *head)
{
	struct inode *const inode = container_of(head, struct inode, i_rcu);
	pr_debug("freeing inode %u\n", (unsigned)inode->i_ino);
	kmem_cache_free(exfs_inode_cache, exfs_INODE(inode));
}

void exfs_inode_free(struct inode *inode)
{
	call_rcu(&inode->i_rcu, exfs_free_callback);
}

static void exfs_inode_init_once(void *i)
{
	struct exfs_inode *inode = (struct exfs_inode *)i;
	inode_init_once(&inode->ai_inode);
}

int exfs_inode_cache_create(void)
{
	exfs_inode_cache = kmem_cache_create("exfs_inode",
				sizeof(struct exfs_inode),
				0, (SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD),
				exfs_inode_init_once);

	if (exfs_inode_cache == NULL)
		return -ENOMEM;

	return 0;
}

void exfs_inode_cache_destroy(void)
{
	rcu_barrier();
	kmem_cache_destroy(exfs_inode_cache);
	exfs_inode_cache = NULL;
}
