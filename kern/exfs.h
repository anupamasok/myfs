#ifndef __exfs_H__
#define __exfs_H__

#include <linux/types.h>

static uint32_t const exfs_MAGIC = 0x13131313;

struct exfs_disk_super_block
{
	__be32	dsb_magic;
	__be32	dsb_block_size;
	__be32	dsb_root_inode;
	__be32	dsb_inode_blocks;
};

struct exfs_disk_inode
{
	__be32	di_first;
	__be32	di_blocks;
	__be32	di_size;
	__be32	di_gid;
	__be32	di_uid;
	__be32	di_mode;
	__be64	di_ctime;
};

#endif /*__exfs_H__*/
