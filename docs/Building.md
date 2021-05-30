# Building the OS (with toolchain)
To build the OS, you need `i686-elf-gcc` toolchain and many other packages. You can build the toolchain by running:
```
cd ./toolchain/ 
sh ./build_compiler.sh
```

After the toolchain is built, you can build the OS by running: <br/>
`sh ./build.sh`

# Building the OS (without toolchain)
If you already have the `i686-elf-gcc` toolchain, there's no need to build it again. Open the `build.sh` file and change the PATH variable to the path 
where you have installed the toolchain. If you have installed it in - `/home/user/cross`, then change the PATH variable to `"$HOME/cross/bin:$PATH"`.
