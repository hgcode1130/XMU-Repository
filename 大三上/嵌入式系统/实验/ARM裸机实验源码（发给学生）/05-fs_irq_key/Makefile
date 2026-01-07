CROSS_COMPILE   := ~/toolchain/6.4-aarch64/bin/aarch64-linux-

CFLAGS += -g -O0 -fno-builtin -nostdinc -I./common/include -I./include

CC = 		$(CROSS_COMPILE)gcc
LD = 		$(CROSS_COMPILE)ld
OBJCOPY = 	$(CROSS_COMPILE)objcopy
OBJDUMP = 	$(CROSS_COMPILE)objdump

OUTPUT_DIR = ./output

NAME 	= $(OUTPUT_DIR)/fs_irq_key

OBJSss := $(wildcard ./start/*.S) $(wildcard ./common/src/*.S) \
		$(wildcard ./source/*.S) $(wildcard ./*.S) \
		$(wildcard ./start/*.c) $(wildcard ./common/src/*.c) \
		$(wildcard ./source/*.c) $(wildcard ./*.c)

OBJSs  := $(patsubst %.S,%.o,$(OBJSss))

OBJS   := $(patsubst %.c,%.o,$(OBJSs))
	
all:$(OBJS)
	@ echo "  LD   Linking  $(NAME).elf"
	@ $(LD) -Tmap.lds -o $(NAME).elf $^
	@ echo "  OBJCOPY Objcopying  $(NAME).bin"
	@ $(OBJCOPY) -O binary -S $(NAME).elf $(NAME).bin
	@ echo "  OBJDUMP Objdumping  $(NAME).dis"
	@ $(OBJDUMP) -D $(NAME).elf > $(NAME).dis
	
%.o : %.S
	@ echo "  AS   $@"
	@ $(CC) -o $@ $< -c $(CFLAGS)

%.o : %.c
	@ echo "  CC   $@"
	@ $(CC) -o $@ $< -c $(CFLAGS)

distclean clean:
	@ echo "  CLEAN  complete."
	@ rm  $(OBJS) $(NAME).* main.o -rf 

install:
	cp $(NAME).bin /mnt/hgfs/share
	
	
