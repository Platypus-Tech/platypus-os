#include <kernel/paging.h>
#include <string.h>
#include <cpu/isr.h>
#include <cpu/irq.h>
#include <vga/vga.h>
#include "memory.h"
#include "panic.h"

/* Based on JamesM's kernel development tutorials */

uint32_t *frames;
uint32_t total_frames;

extern uint32_t __kernel_end;

#define INDEX_BIT(a) (a/(8*4))
#define OFFSET_BIT(a) (a%(8*4))

/* This function is for paging only */
uint32_t pmalloc(uint32_t size, int a, uint32_t *phys) {
	if (a == 1 && (__kernel_end & 0xFFFFF000)) {
		__kernel_end &= 0xFFFFF000;
		__kernel_end += 0x1000;
	}

	if (phys) {
		*phys = __kernel_end;
	}

	uint32_t t = __kernel_end;
	__kernel_end += size;
	return t;
}

uint32_t kmalloc_paging(uint32_t size) {
    return pmalloc(size, 0, 0);
}

uint32_t kmalloc_a(uint32_t size) {
    return pmalloc(size, 1, 0);
}

uint32_t kmalloc_p(uint32_t size, uint32_t *phys) {
    return pmalloc(size, 0, phys);
}

uint32_t kmalloc_ap(uint32_t size, uint32_t *phys) {
    return pmalloc(size, 1, phys);
}

static void frame_set(uint32_t addr) {
	uint32_t frame = addr / 0x1000;
	uint32_t index = INDEX_BIT(frame);
	uint32_t offset = OFFSET_BIT(frame);

	return (frames[index] |= (0x1 << offset));
}

static void frame_clear(uint32_t addr) {
	uint32_t frame = addr / 0x1000;
	uint32_t index = INDEX_BIT(frame);
	uint32_t offset = OFFSET_BIT(frame);

	return (frames[index] &= ~(0x1 << offset));
}

static uint32_t frame_test(uint32_t addr) {
	uint32_t frame = addr / 0x1000;
	uint32_t index = INDEX_BIT(frame);
	uint32_t offset = OFFSET_BIT(frame);

	return (frames[index] & (0x1 << offset));
}

static uint32_t find_first_frame() {
	uint32_t i, j;

	for (i = 0; i < INDEX_BIT(total_frames); i++) {
		if (frames[i] != 0xFFFFFFFF) {
			for (j = 0; j < 32; j++) {
				uint32_t t = 0x1 << j;

				if (!frames[i] & t) {
					return i*4*8+j;
				}
			}
		}
	}
}

void frame_allocate(page_paging_t *page, int kernel_page, int writeable) {

	if (page->frame_addr != 0) {
		return;
	}
	else {
		uint32_t index = find_first_frame();

        if (index == (uint32_t)-1) {
        	panic("Paging - No free frames found");
        }
         
        frame_set(index * 0x1000);
        page->present_page = 1;
        page->rw_page = (writeable) ? 1 : 0;
        page->user_page = (kernel_page) ? 0 : 1;
        page->frame_addr = index;
	}
}

void frame_free(page_paging_t *page) {
	uint32_t frame;

	if (!(frame = page->frame_addr)) {
		return;
	}
	else {
		frame_clear(frame);
		page->frame_addr = 0x0;
	}
}

void switch_page_dir(dir_page_t *page_dir) {
	int current_dir = page_dir;
    
	__asm__ volatile("mov %0, %%cr3":: "r"(&page_dir->physical_tables));
	
	uint32_t cr0;
	__asm__ volatile("mov %%cr0, %0": "=r"(cr0));

	cr0 |= 0x80000000;

	__asm__ volatile("mov %%cr0, %0": "=r"(cr0));
}

page_paging_t *page_get(uint32_t addr, int is_created, dir_page_t *page_dir) {
	addr /= 0x1000;

	uint32_t index_table = addr / 1024;

	if (page_dir->tables[index_table]) {
		return &page_dir->tables[index_table]->pages[addr % 1024];
	}
	else if (is_created) {
		uint32_t t;
		page_dir->tables[index_table] = (table_page_t*)kmalloc_ap(sizeof(table_page_t), &t);
		memset(page_dir->tables[index_table], 0, 0x1000);
		page_dir->physical_tables[index_table] = t | 0x7;

		return &page_dir->tables[index_table]->pages[addr % 1024];
	}
	else {
		return 0;
	}
}

void handler_page_fault(struct registers *regs) {
	uint32_t fault_addr;

	int is_present = !(regs->err_code & 0x1);
	int rw = regs->err_code & 0x2;
	int user_mode = regs->err_code & 0x4;
	int reserved = regs->err_code & 0x8;
	int id = regs->err_code & 0x10;

	writestr("Page Fault\n");

	writestr(is_present);
	writestr(rw);
	writestr(user_mode);
	writestr(reserved);

	writestr(" at address 0x%d\n", fault_addr);
	panic("Paging - Page Fault");
}

void init_paging() {
	uint32_t end_page = 0x1000000;

	total_frames = end_page / 0x1000;
	frames = (uint32_t*)kmalloc_paging(INDEX_BIT(total_frames));
	memset(frames, 0, INDEX_BIT(total_frames));

	uint32_t kernel_dir = (dir_page_t*)kmalloc_a(sizeof(dir_page_t));
	memset(kernel_dir, 0, sizeof(dir_page_t));
	uint32_t current_dir = kernel_dir;

	int i = 0;
    while (i < __kernel_end) {
    	frame_allocate(page_get(i, 1, kernel_dir), 0, 0);
    	i += 0x1000;
    }

    install_irq_handler(14, handler_page_fault);
    writestr("[ PAGING ] Installed Fault Handler\n");
    switch_page_dir(kernel_dir);
    writestr("[ PAGING ] Switched kernel_dir\n");
}
