# Makefile 
#
# Copyright (C) 2014 HDLink
#
#
ifndef TOPDIR
export TOPDIR=$(PWD)/..
endif

include $(TOPDIR)/scripts/rules.mk
include $(TOPDIR)/scripts/path.mk

dirs=$(KERNEL_DIR)
MKIMG=$(TOPDIR)/scripts/mkimage

all:config	
	make -C $(KERNEL_DIR)
	@cp $(KERNEL_DIR)/arch/arm/boot/zImage $(OUTPUT_DIR)
	@$(MKIMG) -n 'tgni' -A arm -O linux -T kernel -C none -a 0x30008000 -e 0x30008040 -d $(OUTPUT_DIR)/zImage $(OUTPUT_DIR)/zImage.img

config:
	@#cd $(KERNEL_DIR) && make mrproper
	@cp $(KERNEL_DIR)/my2440_config $(KERNEL_DIR)/.config

clean:
	$(foreach N,$(dirs),make -C $(N) clean &&) :

distclean:
	$(foreach N,$(dirs),make -C $(N) distclean &&) :

.PHONY: all config output clean distclean

