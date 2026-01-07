ifeq ($(KERNELRELEASE),)
 
KERNELDIR ?= /home/linux/workdir/fs3399/system/kernel

all: modules 

modules:
	$(MAKE) -C $(KERNELDIR) M=$$PWD modules
	
clean:
	rm -rf *.o *.ko .*.cmd modules.order Module.symvers .tmp_versions *.a *.mod*
		
else
	obj-m := module_test.o

endif

