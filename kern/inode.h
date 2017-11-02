#ifndef __INODE_H__
#define __INODE_H__

#include <linux/fs.h>

struct exfs_inode
{
	struct inode	ai_inode;
	uint32_t	ai_block;
};

static inline struct exfs_inode *exfs_INODE(struct inode *inode)
{
	return (struct exfs_inode *)inode;
}

struct inode *exfs_inode_get(struct super_block *sb, uint32_t no);
struct inode *exfs_inode_alloc(struct super_block *sb);
void exfs_inode_free(struct inode *inode);

int exfs_inode_cache_create(void);
void exfs_inode_cache_destroy(void);

#endif /*__INODE_H__*/
