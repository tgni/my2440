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

dirs :=$(BUSYB0X_DIR)

all:config
	$(foreach N,$(dirs),make -C $(N) &&) :
	make -C $(BUSYB0X_DIR) install

config:
	cp $(BUSYB0X_DIR)/my2440_config $(BUSYB0X_DIR)/.config

clean:
	$(foreach N,$(dirs),make -C $(N) clean;)

distclean: 
	@$(foreach N,$(dirs),make -C $(N) distclean;)

.PHONY:all output clean distclean help
