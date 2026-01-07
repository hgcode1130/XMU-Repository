NAME 		= fs_assembly_led
CROSS		= ~/toolchain/6.4-aarch64/bin/aarch64-linux-
CC		= $(CROSS)gcc
LD		= $(CROSS)ld
OBJCOPY		= $(CROSS)objcopy
OBGJDOMP 	= $(CROSS)objdump
CFLAGS		= -O0 -g -c 

all:
	$(CC) $(CFLAGS) -o $(NAME).o $(NAME).s
	$(LD) $(NAME).o -Tmap.lds -o $(NAME).elf
	$(OBJCOPY) -O binary -S $(NAME).elf $(NAME).bin
	$(OBGJDOMP) -D $(NAME).elf > $(NAME).dis
	
clean:
	rm -rf *.o *.bin *.elf *.dis
	
.PHONY: all clean
