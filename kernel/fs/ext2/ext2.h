#ifndef _FS_EXT2_H
#define _FS_EXT2_H

#include <stdint.h>

#define EXT2_SIGNATURE 0xef53

/* File System States */
#define EXT2_STATE_IS_CLEAN 1
#define EXT2_STATE_HAS_ERRORS 2

/* Error Handling */
#define EXT2_IGNORE_ERROR 1
#define EXT2_REMOUNT_FS_AS_RO 2
#define EXT2_KERNEL_PANIC 3

/* Creator OS IDs */
#define EXT2_CREATOR_LINUX 0
#define EXT2_CREATOR_GNU_HURD 1
#define EXT2_CREATOR_MASIX 2
#define EXT2_CREATOR_FREEBSD 3
#define EXT2_CREATOR_OTHER 4

/* Inode type */
#define EXT2_INODE_TYPE_FIFO 0x1000
#define EXT2_INODE_TYPE_CHAR_DEV 0x2000
#define EXT2_INODE_TYPE_DIR 0x3000
#define EXT2_INODE_TYPE_BLOCK_DEV 0x6000
#define EXT2_INODE_TYPE_FILE 0x8000
#define EXT2_INODE_TYPE_SYMLINK 0xA000
#define EXT2_INODE_TYPE_UNIX_SOCKET 0xC000

/* Inode Permissions */
#define EXT2_INODE_PERMISSION_OTHER_EXEC 0x001
#define EXT2_INODE_PERMISSION_OTHER_WRITE 0x002
#define EXT2_INODE_PERMISSION_OTHER_READ 0x004
#define EXT2_INODE_PERMISSION_GROUP_EXEC 0x008
#define EXT2_INODE_PERMISSION_GROUP_WRITE 0x010
#define EXT2_INODE_PERMISSION_GROUP_READ 0x020
#define EXT2_INODE_PERMISSION_USER_EXEC 0x040
#define EXT2_INODE_PERMISSION_USER_WRITE 0x080
#define EXT2_INODE_PERMISSION_USER_READ 0x100
#define EXT2_INODE_PERMISSION_STICKY_BIT 0x200
#define EXT2_INODE_PERMISSION_SET_GROUP_ID 0x400
#define EXT2_INODE_PERMISSION_SET_USER_ID 0x800

/* Inode Flags */
#define EXT2_INODE_FLAG_SECURE_DELETION 0x00000001
#define EXT2_INODE_FLAG_KEEP_COPY_OF_DATA 0x00000002
#define EXT2_INODE_FLAG_FILE_COMPRESSION 0x00000004
#define EXT2_INODE_FLAG_SYNC_UPDATES 0x00000008
#define EXT2_INODE_FLAG_IMMUTABLE 0x00000010
#define EXT2_INODE_FLAG_APPEND_ONLY 0x00000020
#define EXT2_INODE_FLAG_FILE_NOT_IN_DUMP 0x00000040
#define EXT2_INODE_FLAG_NO_UPDATE_ACCESS_TIME 0x00000080
#define EXT2_INODE_FLAG_HASH_INDEXED_DIR 0x00010000
#define EXT2_INODE_FLAG_AFS_DIR 0x00020000
#define EXT2_INODE_FLAG_JOURNAL_FILE_DATA 0x00040000

typedef struct {
  uint32_t total_inodes;
  uint32_t total_blocks;
  uint32_t blocks_reserved_for_superuser;
  uint32_t unallocated_blocks;
  uint32_t unallocated_inodes;
  uint32_t superblock_blocknum;
  uint32_t block_size;
  uint32_t fragment_size;
  uint32_t blocks_in_block_group;
  uint32_t fragments_in_block_group;
  uint32_t inodes_in_block_group;
  uint32_t last_mount_time;
  uint32_t last_write_time;
  uint16_t mounts_since_last_check;
  uint16_t mounts_allowed;
  uint16_t ext2_signature;
  uint16_t fs_state;
  uint16_t op_on_err;
  uint32_t minor_version;
  uint32_t last_fs_check;
  uint32_t interval_forced_checks;
  uint32_t os_id;
  uint32_t major_version;
  uint16_t uid_can_use_reserved_blocks;
  uint16_t gid_can_use_reserved_blocks;
} ext2_superblock_t;

typedef struct {
  uint32_t block_addr_of_block_usage_bitmap;
  uint32_t block_addr_of_inode_usage_bitmap;
  uint32_t start_block_addr_of_inode_table;
  uint32_t unallocated_blocks_in_group;
  uint32_t unallocated_inodes_in_group;
  uint32_t directories_in_group;
  char unused[8];
} ext2_block_group_desc_t;

typedef struct {
  uint16_t type_and_permissions;
  uint16_t uid;
  uint32_t size;
  uint32_t last_access_time;
  uint32_t creation_time;
  uint32_t last_modif_time;
  uint32_t deletion_time;
  uint32_t gid;
  uint32_t total_hardlinks;
  uint32_t total_disk_sectors;
  uint32_t flags;
  uint32_t os_specific_val_1;
  uint32_t direct_block_pointer_1;
  uint32_t direct_block_pointer_2;
  uint32_t direct_block_pointer_3;
  uint32_t direct_block_pointer_4;
  uint32_t direct_block_pointer_5;
  uint32_t direct_block_pointer_6;
  uint32_t direct_block_pointer_7;
  uint32_t direct_block_pointer_8;
  uint32_t direct_block_pointer_9;
  uint32_t direct_block_pointer_10;
  uint32_t direct_block_pointer_11;
  uint32_t singly_indirect_block_ptr;
  uint32_t doubly_indirect_block_ptr;
  uint32_t triply_indirect_block_ptr;
  uint32_t generation_num;
  uint32_t reserved_1;
  uint32_t reserved_2;
  uint32_t block_addr_of_fragment;
  uint32_t os_specific_val_2;
} ext2_inode_t;

typedef struct {
  uint32_t inode;
  uint32_t total_size;
  uint32_t name_length;
  uint32_t name_chars;
} ext2_dir_t;

#endif //_FS_EXT2_H
