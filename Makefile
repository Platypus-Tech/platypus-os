NAME=If you use this tell me how bad it sucks # release name
RELNUM=0.06 # release number
RC=1 # -rc, if there.


DEFAULT_HOST=i686
HOST?=DEFAULT_HOST
HOSTARCH!=scripts/target-triplet-to-arch.sh $(HOST)

CFLAGS?= -O2 -g -ffreestanding -Wall -Wextra
CPPFLAGS?= -D__is_kernel -Iinclude
LDFLAGS?=
LIBS?= -nostdlib -lk -lgcc

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
INTERRUPTS?=$(PREFIX)/kernel/interrupts
DRIVERDIR?=$(PREFIX)/kernel/devices 

ARCHDIR=kernel/arch/$(DEFAULT_HOST)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/main.o \

INTERRUPT_OBJS=\
$(INTERRUPTS)/nmi.o

DRIVER_OBJS=\
$(DRIVERDIR)/mouse/ps2mouse.o \
$(DRIVERDIR)/keyboard/ps2.o \
$(DRIVERDIR)/keyboard/keyboard.o \
$(DRIVERDIR)/rtc/rtc.o \

OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: platypusos.kernel

platypusos.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot platypusos.kernel

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -m32 -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -m32 -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f platypusos.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: platypusos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp platypusos.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)
