ifeq ($(KERNELRELEASE),)
 
KERNELDIR ?= /home/linux/workdir/fs3399/system/kernel

all: modules 

modules:
	$(MAKE) -C $(KERNELDIR) M=$$PWD modules

app:
	aarch64-linux-gnu-gcc pwm_led.c -o pwm_led

clean:
	rm -rf *.o *.ko .*.cmd modules.order Module.symvers .tmp_versions *.a *.mod*  pwm_led
		
else
	obj-m := pwm_led_driver.o

endif

