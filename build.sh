#!/bin/sh

# Change the PATH to the path where you have installed the i686-elf-gcc compiler
# Do not forget to add the :$PATH at the end!

export PATH="./toolchain/compiler/bin:$PATH"

# Compile the OS
i686-elf-as ./kernel/arch/i386/boot.S -o boot.o
i686-elf-gcc -I./kernel/include/ -c ./kernel/drivers/vga/vga.c -o vga.o
i686-elf-gcc -I./kernel/drivers/ -I./kernel/include/ -I./kernel/cpu/ -c ./init/init.c -o init.o
nasm -f elf32 ./kernel/cpu/load_gdt.asm -o load_gdt.o
i686-elf-gcc -I./kernel/include/ -I./kernel/drivers/ -c ./kernel/cpu/gdt.c -o gdt.o

i686-elf-gcc -T ./kernel/arch/i386/linker.ld -o PlatypusOS.bin -ffreestanding -O2 -nostdlib boot.o vga.o gdt.o load_gdt.o init.o
