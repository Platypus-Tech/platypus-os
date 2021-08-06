#ifndef _KERNEL_PAGING_H
#define _KERNEL_PAGING_H

#include <stdint.h>

#define INDEX_FROM_BIT(a) (a / (8 * 4))
#define OFFSET_FROM_BIT(a) (a % (8 * 4))

typedef struct page {
  uint32_t present : 1;
  uint32_t rw : 1;
  uint32_t user : 1;
  uint32_t accessed : 1;
  uint32_t dirty : 1;
  uint32_t unused : 7;
  uint32_t frame : 20;
} page_t;

typedef struct page_table {
  page_t pages[1024];
} page_table_t;

typedef struct page_directory {
  page_table_t *tables[1024];
  uint32_t tablesPhysical[1024];
  uint32_t physicalAddr;
} page_dir_t;

void switch_page_directory(page_dir_t *new);
page_t *get_page(uint32_t address, int make, page_dir_t *dir);
void init_paging();

#endif //_KERNEL_PAGING_H
