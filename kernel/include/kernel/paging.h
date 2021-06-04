#ifndef _KERNEL_PAGING_H
#define _KERNEL_PAGING_H

#include <stdint.h>

typedef struct page_paging {
	uint32_t present_page   : 1;
	uint32_t rw_page        : 1;
	uint32_t user_page      : 1;
	uint32_t accessed_page  : 1;
	uint32_t dirty_page     : 1;
	uint32_t unused_page    : 7;
	uint32_t frame_addr     : 20;
} page_paging_t;

typedef struct table_page {
	page_paging_t pages[1024];
} table_page_t;

typedef struct dir_page {
	table_page_t *tables[1024];
	uint32_t physical_tables[1024];
	uint32_t physical_addr;
} dir_page_t;

void switch_page_dir(dir_page_t *new_page_dir);
page_paging_t *page_get(uint32_t addr, int is_created, dir_page_t *page_dir);
void handler_page_fault();
void init_paging();

#endif //_KERNEL_PAGING_H