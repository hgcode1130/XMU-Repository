ifeq ($(KERNELRELEASE),)
 
KERNELDIR ?= /home/linux/workdir/fs3399/system/kernel

all: modules 

modules:
	$(MAKE) -C $(KERNELDIR) M=$$PWD modules

app:
	aarch64-linux-gnu-gcc lm75.c -o lm75

clean:
	rm -rf *.o *.ko .*.cmd modules.order Module.symvers .tmp_versions *.a *.mod*  lm75
		
else
	obj-m := farsight_lm75.o

endif

