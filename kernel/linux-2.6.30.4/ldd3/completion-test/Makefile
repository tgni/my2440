
CROSS_COMPILE	=/home/tekkaman/working/crosstool-gcc410-k26222/gcc-4.1.0-glibc-2.3.2/arm-9tdmi-linux-gnu/bin/arm-9tdmi-linux-gnu-
CC	= $(CROSS_COMPILE)gcc


all : completion_testw.o  completion_testr.o
		$(CC)  -o completion_testw completion_testw.o 
		$(CC)  -o completion_testr completion_testr.o 


clean:
		rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions




