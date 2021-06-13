NAME = PlatypusOS
VERSION = 0.08-dev
BUILD_SCRIPT = ./build.sh

all: exec_script

exec_script: 
	$(BUILD_SCRIPT)

run:
	qemu-system-x86_64 PlatypusOS.iso

clean:
	@echo "Cleaning"
	rm *.bin
	rm *.iso
	rm -rf isodir
	rm -rf build
	@echo "Done"