#!/bin/sh

if [ -d "compiler/" ]; then
    echo "Found i686-elf-gcc Toolchain"
    exit 0;
else
    continue;
fi

sudo apt-get update
sudo apt install make gcc bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev tar xorriso mtools

export PREFIX="$PWD/compiler"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir ./compiler

mkdir ./src
cd ./src

wget https://ftp.gnu.org/gnu/binutils/binutils-2.36.1.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-11.1.0/gcc-11.1.0.tar.gz

tar -xf gcc-11.1.0.tar.gz
tar -xf binutils-2.36.1.tar.gz

mkdir binutils-build
cd binutils-build
../binutils-2.36.1/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install

cd ..

which -- $TARGET-as || echo $TARGET-as not found
 
mkdir gcc-build
cd gcc-build
../gcc-11.1.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

# Remove the sources
cd ..
cd ..
rm -rf src/
