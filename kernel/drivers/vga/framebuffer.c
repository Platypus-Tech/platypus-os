#include <init/multiboot.h>
#include <kernel/vga.h>
#include <stdint.h>

/* Framebuffer Info */
static uint32_t framebuffer_width;
static uint32_t framebuffer_height;
uint32_t *framebuffer;
int x = 0;
int y = 0;

void put_pixel(int pos_x, int pos_y, unsigned char color) {
  framebuffer[pos_y * framebuffer_width + pos_x] = color;
}

void init_framebuffer() {
  multiboot_info_t *mboot_fb_info;

  framebuffer = mboot_fb_info->framebuffer_addr;
  framebuffer_width = mboot_fb_info->framebuffer_width;
  framebuffer_height = mboot_fb_info->framebuffer_height;
}
