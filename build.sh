#!/bin/sh

sudo apt-get update
sudo apt-get install nasm mtools

export PATH="$PWD/toolchain/compiler/bin:$PATH"

if [ ! -d build ]; then
   mkdir build
fi

# Compile the libc
sh ./build_libc.sh

# Compile the OS
nasm -f elf32 ./kernel/arch/i386/boot.asm -o boot.o
i686-elf-gcc -I./kernel/include/ -c ./kernel/drivers/vga/vga.c -o vga.o
i686-elf-gcc -I./kernel/include/ -I./kernel/kernel/ -c ./kernel/drivers/sound/sound.c -o sound.o
i686-elf-gcc -I./kernel/include/ -c ./kernel/drivers/ports/ports.c -o ports.o
i686-elf-gcc -I./kernel/ -I./kernel/include/ -I./kernel/drivers/ -I./kernel/cpu/ -I./user/ -c ./kernel/drivers/keyboard/keyboard.c -o keyboard.o
i686-elf-gcc -I./kernel/ -I./kernel/drivers/ -I./kernel/include/ -I./kernel/kernel/ -I./user/ -c ./init/main.c -o main.o
nasm -f elf32 ./kernel/cpu/load_gdt.asm -o load_gdt.o
i686-elf-gcc -I./kernel/include/ -c ./kernel/cpu/gdt.c -o gdt.o
nasm -f elf32 ./kernel/cpu/load_idt.asm -o load_idt.o
i686-elf-gcc -I./kernel/include/ -c ./kernel/cpu/idt.c -o idt.o
nasm -f elf32 ./kernel/cpu/load_isr.asm -o load_isr.o
i686-elf-gcc -I./kernel/include/ -I./kernel/drivers/ -I./kernel/kernel/ -c ./kernel/cpu/isr.c -o isr.o
nasm -f elf32 ./kernel/cpu/load_irq.asm -o load_irq.o
i686-elf-gcc -I./kernel/include/ -c ./kernel/cpu/irq.c -o irq.o
i686-elf-gcc -I./kernel/ -I./kernel/include/ -c ./kernel/drivers/pit/pit.c -o pit.o
i686-elf-gcc -I./kernel/drivers/ -c ./kernel/kernel/panic.c -o panic.o
i686-elf-gcc -I./kernel/include/ -I./kernel/drivers/ -c ./kernel/kernel/memory.c -o memory.o
i686-elf-gcc -I./kernel/drivers/ -I./kernel/include/ -c ./kernel/kernel/nmi.c -o nmi.o
i686-elf-gcc -I./kernel/drivers/ -I./kernel/kernel/ -I./kernel/include/ -c ./kernel/system/vtconsole.c -o vtconsole.o
i686-elf-gcc -I./kernel/drivers/ -I./kernel/include/ -I./kernel/kernel/ -c ./kernel/system/log.c -o log.o
i686-elf-gcc -I./kernel/drivers/ -I./kernel/include/ -I./kernel/kernel/ -I./kernel/ -c ./user/terminal/terminal.c -o terminal.o
i686-elf-gcc -I./kernel/drivers/ -I./kernel/include/ -I./kernel/kernel/ -c ./kernel/kernel/printm/printm.c -o printm.o
i686-elf-gcc -I./kernel/include/ -I./kernel/ -c ./kernel/kernel/power/reboot.c -o reboot.o
i686-elf-gcc -I./kernel/include/ -I./kernel/drivers/ -I./kernel/ -I./kernel/kernel/ -c ./kernel/fs/vfs/vfs.c -o vfs.o

cp *.o ./build/
rm *.o

i686-elf-gcc -T ./kernel/arch/i386/linker.ld -o kernel.bin -ffreestanding -O2 -nostdlib ./build/*.o ./lib/libc/libpdclib.a

# Now generate the ISO file
mkdir -p isodir/boot/grub
cp grub.cfg isodir/boot/grub/
cp kernel.bin isodir/boot/
grub-mkrescue -o PlatypusOS.iso isodir
