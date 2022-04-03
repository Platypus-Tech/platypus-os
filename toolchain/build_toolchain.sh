#!/bin/sh

GCC_VERSION=11.2.0
BINUTILS_VERSION=2.38

if [ -d "compiler/" ]; then
    echo "Found i686-elf-gcc Toolchain"
    exit 0;
fi

sudo apt-get update
sudo apt install make nasm gcc bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev tar xorriso mtools

export PREFIX="$PWD/compiler"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir ./compiler

mkdir ./src
cd ./src

wget https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-11.1.0/gcc-$GCC_VERSION.tar.gz

tar -xf gcc-$GCC_VERSION.tar.gz
tar -xf binutils-$BINUTILS_VERSION.tar.gz

mkdir binutils-build
cd binutils-build
../binutils-$BINUTILS_VERSION/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j$(nproc)
make install

cd ..

which -- $TARGET-as || echo $TARGET-as not found
 
mkdir gcc-build
cd gcc-build
../gcc-$GCC_VERSION/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make -j$(nproc) all-gcc
make -j$(nproc) all-target-libgcc
make install-gcc
make install-target-libgcc

# Remove the sources
cd ..
cd ..
rm -rf src/
