# Makefile for Platypus OS

VERSION = 0.10
EXTRAVERSION = 

MAKEFILE_BUILD = ./scripts/Makefile.build
MAKEFILE_RUN = ./scripts/Makefile.run

.PHONY: all

all:
	@./scripts/gen_config.sh
	@make -f $(MAKEFILE_BUILD) -j$(nproc)
	
clean:
	@make -f $(MAKEFILE_BUILD) clean
	
run:
	@make -f $(MAKEFILE_RUN)
