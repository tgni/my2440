# Makefile 
#
# Copyright (C) 2013 HDLink
#
#
TOPDIR:=$(shell pwd)
export TOPDIR 
include $(TOPDIR)/scripts/rules.mk
include $(TOPDIR)/scripts/path.mk

dirs :=$(BOOTS_DIR) $(APPS_DIR) $(KERNELS_DIR)

all:
	$(foreach N,$(dirs),make -C $(N) &&) :
	@cp $(TOPDIR)/output/* ~/tftpboot -rf

clean:
	$(foreach N,$(dirs),make -C $(N) clean &&) :
	rm $(OUTPUT_DIR)/* -rf

distclean: 
	$(foreach N,$(dirs),make -C $(N) distclean &&) :
	rm $(OUTPUT_DIR)/* -rf

boot:
	make -C $(BOOTS_DIR)

apps:
	make -C $(APPS_DIR)

kernel:
	make -C $(KERNELS_DIR)

apps_clean:
	make -C $(APPS_DIR) clean

kernel_clean:
	make -C $(KERNELS_DIR) clean

help:
	@echo ""
	@echo "Usage: "
	@echo "       make [ compile boot, kernel, apps ]"
	

.PHONY:all apps kernel apps_clean kernel_clean clean distclean help
