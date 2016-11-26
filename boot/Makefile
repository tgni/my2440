# Makefile 
#
# Copyright (C) 2014 HDLink
#
#
CURDIR:=$(shell pwd)
ifndef TOPDIR
export TOPDIR=$(CURDIR)/..
endif
include $(TOPDIR)/scripts/rules.mk
include $(TOPDIR)/scripts/path.mk

dirs :=$(BOOT_DIR)

all:config
	make -C $(BOOT_DIR) u-boot.bin
	cp $(BOOT_DIR)/u-boot.bin $(OUTPUT_DIR)

config:
	@make -C $(BOOT_DIR) my2440_config

clean:
	@$(foreach N,$(dirs),make -C $(N) clean;)

distclean: 
	@$(foreach N,$(dirs),make -C $(N) distclean;)

.PHONY:all output clean distclean help
