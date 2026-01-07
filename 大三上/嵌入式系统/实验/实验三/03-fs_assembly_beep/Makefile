NAME    = fs_assembly_beep

# 交叉编译工具链路径保持不变
CROSS   = /usr/bin/aarch64-linux-gnu-
CC      = $(CROSS)gcc
LD      = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy
OBJDUMP = $(CROSS)objdump
CFLAGS  = -O0 -g -c

all:
    # 编译 $(NAME).s (即 fs_assembly_beep.s) 生成 .o 文件
	$(CC) $(CFLAGS) -o $(NAME).o $(NAME).s
    # 链接 .o 文件生成 .elf 文件
	$(LD) $(NAME).o -Tmap.lds -o $(NAME).elf
    # 从 .elf 文件中提取二进制 .bin 文件
	$(OBJCOPY) -O binary -S $(NAME).elf $(NAME).bin
    # 生成反汇编文件 .dis
	$(OBJDUMP) -D $(NAME).elf > $(NAME).dis

clean:
	rm -rf *.o *.bin *.elf *.dis

.PHONY: all clean