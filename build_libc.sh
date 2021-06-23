#!/bin/sh

cd ./lib/libc/

if [ ! -d build ]; then
   mkdir build
else
   exit 0;
fi

# Build ctype
cd ./ctype/
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c isalnum.c
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c isalpha.c
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c isblank.c
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c isdigit.c
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c islower.c
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c isupper.c

cp *.o ../build/
rm *.o
cd ..

# Build string
cd ./string/
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c memcpy.c
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c memsetw.c
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c strcmp.c
i686-elf-gcc -fno-builtin -I../../../kernel/include/ -c strlen.c

cp *.o ../build/
rm *.o
cd ..
