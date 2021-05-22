#!/bin/sh

# Change the PATH to the path where you have installed the i686-elf-gcc compiler
# Do not forget to add the :$PATH at the end!

export PATH="$HOME/cross/bin:$PATH"

i686-elf-as ./kernel/arch/i386/boot.S -o boot.o

i686-elf-gcc -I./kernel/include/ -c ./kernel/drivers/vga/vga.c -o vga.o

i686-elf-gcc -I./kernel/drivers/vga/ -I./kernel/include/ -c ./init/init.c -o init.o

i686-elf-gcc -T linker.ld -o PlatypusOS.bin -ffreestanding -O2 -nostdlib boot.o vga.o init.o
