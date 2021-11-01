#!/bin/sh

ISO_FILE="$1"
FLOPPY_FILE="$2"

qemu-system-x86_64 -fda $FLOPPY_FILE -serial stdio -m 256 -soundhw pcspk $ISO_FILE
