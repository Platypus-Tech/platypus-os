# Makefile for Platypus OS

VERSION = 0.11
EXTRAVERSION = -rc3

MAKEFILE_BUILD = ./scripts/Makefile.build

.PHONY: all

all:
	@./scripts/gen_config.sh
	@make -f $(MAKEFILE_BUILD) -j$(nproc)
	
clean:
	@make -f $(MAKEFILE_BUILD) clean
	
run:
	@./scripts/run.sh PlatypusOS.iso floppy.img
