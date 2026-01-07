ifeq ($(KERNELRELEASE),)
 
KERNELDIR ?= /home/linux/workdir/fs3399/system/kernel

all: modules 

modules:
	$(MAKE) -C $(KERNELDIR) M=$$PWD modules

app:
	aarch64-linux-gnu-gcc dcmotor.c -o dcmotor

clean:
	rm -rf *.o *.ko .*.cmd modules.order Module.symvers .tmp_versions *.a *.mod* dcmotor
		
else
	obj-m := dcmotor_driver.o

endif

