# Building the OS (with toolchain)
To build the OS, you need `i686-elf-gcc` toolchain and many other packages. You can build the toolchain by running:
```
cd ./toolchain/
sh ./build_toolchain.sh
```

After the toolchain is built, you can build the OS by running: `make`

# Building the OS (without toolchain)
If you already have the `i686-elf-gcc` toolchain, there's no need to build it again. Open the `scripts/Makefile.build` file and change the `CC` variable to the path where you have installed the toolchain and run `make`.
