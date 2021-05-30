#include "memory.h"
#include <stdint.h>
#include <stddef.h>

/* This file contains memory management functions for the kernel and userspace.
 * The kmalloc() and kfree() should be used in the kernel.
 * The malloc() and free() should be used in the userspace.
 */

/* Most of the code is based on the C Programming Language 2nd Edition Book */

#define ALLOC 1024

extern __kernel_end;
unsigned int heap;

static blk_hdr base;
static blk_hdr *free_p = NULL;

void kmalloc(uint32_t size) {
    uint32_t ptr = __kernel_end + heap;
    heap += size;
    
    return (void*)ptr;
}

void kfree(void *addr) {
    // Do nothing
}

/* We need sbrk() for this 
void *malloc(unsigned int size) {
    blk_hdr *p, *prev_p;
    blk_hdr *mcore(unsigned);
    unsigned total_units;
    
    total_units = (size + sizeof(blk_hdr) -1) / sizeof(blk_hdr) + 1;
    
    if ((prev_p = free_p) == NULL) {
        base.s.ptr = free_p = prev_p = &base;
        base.s.size = 0;
    }
    
    for (p = prev_p->s.ptr; ; prev_p = p, p = p->s.ptr) {
        if (p->s.size >= total_units) {
            prev_p->s.ptr = p->s.ptr;
        }
        else {
            p->s.size -= total_units;
            p += p->s.size;;
            p->s.size = total_units;
        }
        
        free_p = prev_p;
        return (void*) (p+1);
    }
    
    if (p == free_p) {
        if ((p = mcore(total_units)) == NULL) {
            return NULL;
        }
    }
} */

/* sbrk required
static blk_hdr *mcore(unsigned units) {
    char *cp, *sbrk(int);
    blk_hdr *up;
    
    if (units < ALLOC) {
        units = ALLOC;
    }
    
    cp = sbrk(units * sizeof(blk_hdr));
    
    if (cp == (char*) -1) {
        return NULL);
    }
    
    up = (blk_hdr*) cp;
    up->s.size = units;
    free((void*) (up+1));
    
    return free_p;
}
*/
