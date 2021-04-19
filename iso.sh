#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub
 
cp sysroot/boot/platypusos.kernel isodir/boot/platypusos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "platypusos" {
	multiboot /boot/platypusos.kernel
}
EOF
grub-mkrescue -o platypusos.iso isodir
