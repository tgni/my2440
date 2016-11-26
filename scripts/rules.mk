#ifndef BOARD
#$(error "pls try export BOARD=xxx or make BOARD=xxx")
#endif

CROSS=arm-linux-
CC=$(CROSS)gcc
AR=$(CROSS)ar
RANLIB=$(CROSS)ranlib
SSTRIP=$(CROSS)sstrip
LD=$(CROSS)ld
NM=$(CROSS)nm
GCC=$(CROSS)gcc
CXX=$(CROSS)g++
RANLIB=$(CROSS)ranlib
STRIP=$(CROSS)strip
OBJCOPY=$(CROSS)objcopy
OBJDUMP=$(CROSS)objdump
SIZE=$(CROSS)size

export CROSS CC AR RANLIB SSTRIP LD NM GCC CXX RANLIB STRIP OBJCOPY OBJDUMP SIZE BOARD
