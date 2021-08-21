ARCH = i386
CC = ./toolchain/compiler/bin/i686-elf-gcc
LD = $(CC)
NASM = nasm
ISO_FILE = PlatypusOS.iso
KERNEL_FILE = kernel.bin
INITRD_FILE = initrd.img
INCLUDE = -I./kernel/ -I./kernel/drivers/ -I./kernel/fs/ -I./kernel/include/ -I./user/

CFLAGS = -ffreestanding $(INCLUDE)
NASMFLAGS = -f elf32
LDFLAGS = -T./kernel/arch/i386/linker.ld -ffreestanding -O2 -nostdlib

C_SOURCES = $(shell find init/ kernel/ lib/ user/ -name '*.c')
ASM_SOURCES = $(shell find kernel/ -name '*.asm')
OBJ_FILES = $(C_SOURCES:.c=.o) $(ASM_SOURCES:.asm=.o)

$(ISO_FILE): $(KERNEL_FILE)
	#@gcc -o ./scripts/gen_initrd ./scripts/gen_initrd.c
	#@./scripts/gen_initrd initrd/file.txt file.txt initrd/file2.txt file2.txt
	@mkdir -p isodir/boot/grub/
	@cp grub.cfg isodir/boot/grub/
	@cp kernel.bin isodir/boot/
	@grub-mkrescue -o PlatypusOS.iso isodir

$(KERNEL_FILE): kernel/arch/$(ARCH)/boot.o $(OBJ_FILES)
	@echo "LD $^"
	@$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	@echo "CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

kernel/system/vtconsole.o: kernel/system/vtconsole.c
	@$(CC) -I$(INCLUDE) -c $< -o $@

%.o: %.asm
	@echo "NASM $<"
	@$(NASM) $(NASMFLAGS) $< -o $@

clean:
	@rm -rf isodir/ $(KERNEL_FILE) $(INITRD_FILE) $(ISO_FILE) $(OBJ_FILES)

run:
	# TODO: Remove -soundhw pcspk
	@qemu-system-x86_64 -serial stdio -soundhw pcspk $(ISO_FILE)
