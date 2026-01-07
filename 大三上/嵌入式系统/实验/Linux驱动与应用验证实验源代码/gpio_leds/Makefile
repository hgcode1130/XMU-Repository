ifeq ($(KERNELRELEASE),)
 
KERNELDIR ?= /home/linux/workdir/fs3399/system/kernel

all: modules 

modules:
	$(MAKE) -C $(KERNELDIR) M=$$PWD modules

app:
	aarch64-linux-gnu-gcc leds_test.c -o leds_test

clean:
	rm -rf *.o *.ko .*.cmd modules.order Module.symvers .tmp_versions *.a *.mod*  leds_test
		
else
	obj-m := gpio_leds.o

endif

