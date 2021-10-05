# Makefile for Platypus OS

VERSION = 0.10
EXTRAVERSION = -rc4

MAKEFILE_BUILD = ./scripts/Makefile.build
MAKEFILE_RUN = ./scripts/Makefile.run

.PHONY: all

all:
	make -f $(MAKEFILE_BUILD) -j$(nproc)
	
clean:
	make -f $(MAKEFILE_BUILD) clean
	
run:
	make -f $(MAKEFILE_RUN)
