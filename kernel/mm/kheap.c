#include <kernel/kheap.h>
#include <kernel/pmm.h>
#include <kernel/vmm.h>

uint32_t heap_max = HEAP_START;
header_t *heap_first = 0;

void alloc_chunk(uint32_t start, uint32_t len) {
  while (start + len > heap_max) {
    uint32_t page = alloc_page_pmm();
    map_vmm(heap_max, page, PAGE_PRESENT | PAGE_WRITE);
    heap_max += 0x1000;
  }
}

void free_chunk(header_t *chunk) {
  chunk->prev->next = 0;

  if (chunk->prev == 0) {
    heap_first = 0;
  }

  while ((heap_max - 0x1000) >= (uint32_t)chunk) {
    heap_max -= 0x1000;
    uint32_t page;
    get_mapping_vmm(heap_max, &page);
    free_page_pmm(page);
    unmap_vmm(heap_max);
  }
}

void split_chunk(header_t *chunk, uint32_t len) {
  if (chunk->length - len > sizeof(header_t)) {
    header_t *newchunk = (header_t *)((uint32_t)chunk + chunk->length);
    newchunk->prev = chunk;
    newchunk->next = 0;
    newchunk->allocated = 0;
    newchunk->length = chunk->length - len;

    chunk->next = newchunk;
    chunk->length = len;
  }
}

void glue_chunk(header_t *chunk) {
  if (chunk->next && chunk->next->allocated == 0) {
    chunk->length = chunk->length + chunk->next->length;
    chunk->next->next->prev = chunk;
    chunk->next = chunk->next->next;
  }

  if (chunk->prev && chunk->prev->allocated == 0) {
    chunk->prev->length = chunk->prev->length + chunk->length;
    chunk->prev->next = chunk->next;
    chunk->next->prev = chunk->prev;
    chunk = chunk->prev;
  }

  if (chunk->next == 0) {
    free_chunk(chunk);
  }
}

void *kmalloc(uint32_t l) {
  l += sizeof(header_t);

  header_t *cur_header = heap_first, *prev_header = 0;

  while (cur_header) {
    if (cur_header->allocated == 0 && cur_header->length >= l) {
      split_chunk(cur_header, l);
      cur_header->allocated = 1;
      return (void *)((uint32_t)cur_header + sizeof(header_t));
    }
    prev_header = cur_header;
    cur_header = cur_header->next;
  }

  uint32_t chunk_start;
  if (prev_header) {
    chunk_start = (uint32_t)prev_header + prev_header->length;
  } else {
    chunk_start = HEAP_START;
    heap_first = (header_t *)chunk_start;
  }

  alloc_chunk(chunk_start, l);
  cur_header = (header_t *)chunk_start;
  cur_header->prev = prev_header;
  cur_header->next = 0;
  cur_header->allocated = 1;
  cur_header->length = l;

  prev_header->next = cur_header;

  return (void *)(chunk_start + sizeof(header_t));
}

void kfree(void *p) {
  header_t *header = (header_t *)((uint32_t)p - sizeof(header_t));
  header->allocated = 0;
  glue_chunk(header);
}
