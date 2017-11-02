#ifndef __exfs_HPP__
#define __exfs_HPP__

#include <cassert>
#include <cstring>
#include <cstdint>

static uint32_t const exfs_MAGIC = 0x13131313;

struct exfs_super_block
{
	uint32_t	asb_magic;
	uint32_t	asb_block_size;
	uint32_t	asb_root_inode;
	uint32_t	asb_inode_blocks;
};

static inline uint32_t & ASB_MAGIC(struct exfs_super_block *asb)
{ return asb->asb_magic; }

static inline uint32_t & ASB_BLOCK_SIZE(struct exfs_super_block *asb)
{ return asb->asb_block_size; }

static inline uint32_t & ASB_ROOT_INODE(struct exfs_super_block *asb)
{ return asb->asb_root_inode; }

static inline uint32_t & ASB_INODE_BLOCKS(struct exfs_super_block *asb)
{ return asb->asb_inode_blocks; }


struct exfs_inode
{
	uint32_t	ai_first;
	uint32_t	ai_blocks;
	uint32_t	ai_size;
	uint32_t	ai_gid;
	uint32_t	ai_uid;
	uint32_t	ai_mode;
	uint64_t	ai_ctime;
};

static inline uint32_t & AI_FIRST_BLOCK(struct exfs_inode *ai)
{ return ai->ai_first; }

static inline uint32_t & AI_BLOCKS(struct exfs_inode *ai)
{ return ai->ai_blocks; }

static inline uint32_t & AI_SIZE(struct exfs_inode *ai)
{ return ai->ai_size; }

static inline uint32_t & AI_GID(struct exfs_inode *ai)
{ return ai->ai_gid; }

static inline uint32_t & AI_UID(struct exfs_inode *ai)
{ return ai->ai_uid; }

static inline uint32_t & AI_MODE(struct exfs_inode *ai)
{ return ai->ai_mode; }

static inline uint64_t & AI_CTIME(struct exfs_inode *ai)
{ return ai->ai_ctime; }


struct exfs_dir_entry
{
	uint32_t	ade_size;
	uint32_t	ade_inode;
	union
	{
		uint32_t	dummy;
		char		ade_name;
	};
};

static inline uint32_t & ADE_SIZE(struct exfs_dir_entry *ade)
{ return ade->ade_size; }

static inline uint32_t & ADE_INODE(struct exfs_dir_entry *ade)
{ return ade->ade_inode; }

static inline char const * ADE_NAME(struct exfs_dir_entry const *ade)
{ return &ade->ade_name; }

static inline char * ADE_NAME(struct exfs_dir_entry *ade)
{
	return const_cast<char *>(
		ADE_NAME(const_cast<struct exfs_dir_entry const *>(ade)));
}

#endif /*__exfs_HPP__*/
