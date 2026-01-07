# 1. 定义最终生成文件的名字
NAME    = 11_fs_loop_key_beep

# 2. 定义交叉编译器路径和工具
CROSS   = /usr/bin/aarch64-linux-gnu-
CC      = $(CROSS)gcc
LD      = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy
OBJDUMP = $(CROSS)objdump

# 3. 定义编译选项，包含所有头文件路径
CFLAGS    = -O0 -g -c -Iinclude -Icommon/include -Isource/include

# 4. 定义所有需要编译和链接的目标文件 (.o 文件)
#    我们不再需要 fs3399_beep.o
OBJS = start.o main.o fs3399_timer.o

# 5. 告诉make去哪里寻找源文件
VPATH = .:start:source

# 默认目标
all: $(NAME).bin
	@echo "build done."

# 链接规则
$(NAME).elf: $(OBJS)
	$(LD) $^ -Tmap.lds -o $@

# 生成.bin文件规则
$(NAME).bin: $(NAME).elf
	$(OBJCOPY) -O binary -S $< $@

# 通用编译规则 (.c -> .o)
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

# 通用编译规则 (.S -> .o)
%.o: %.S
	$(CC) $(CFLAGS) -o $@ $<

# 清理命令
clean:
	rm -rf *.o *.bin *.elf *.dis output/*

# 伪目标声明
.PHONY: all clean