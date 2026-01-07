# 1. 定义最终生成文件的名字
NAME    = 01-fs_led

# 2. 定义交叉编译器路径和工具
# CROSS   = ~/toolchain/6.4-aarch64/bin/aarch64-linux-
CROSS   = /usr/bin/aarch64-linux-gnu-
CC      = $(CROSS)gcc
LD      = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy
OBJDUMP = $(CROSS)objdump

# 3. 定义编译选项
# -O0 表示不进行优化，-g 表示加入调试信息，-c 表示只编译不链接

CFLAGS    = -O0 -g -c -Iinclude -Icommon/include -Isource/include

# 4. 定义所有需要编译和链接的目标文件 (.o 文件)
# 我们需要启动文件 start.o, 主函数 main.o, LED驱动 fs3399_led.o, 以及延时函数 fs3399_timer.o
OBJS = start.o main.o fs3399_led.o fs3399_timer.o

# 5. 告诉make去哪里寻找源文件
# VPATH 会在当前目录、start子目录、source子目录中寻找.c和.S文件
VPATH = start:source

# 默认目标，当直接运行 make 时执行
all: $(NAME).bin
	@echo "build done."

# 链接规则：将所有的.o文件链接成.elf文件
$(NAME).elf: $(OBJS)
	$(LD) $^ -Tmap.lds -o $@

# 生成.bin文件规则：从.elf文件中提取二进制内容
$(NAME).bin: $(NAME).elf
	$(OBJCOPY) -O binary -S $< $@

# 通用编译规则：如何从.c文件生成.o文件
%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

# 通用编译规则：如何从.S文件生成.o文件
%.o: %.S
	$(CC) $(CFLAGS) -o $@ $<

# 清理命令：删除所有生成的文件
clean:
	rm -rf *.o *.bin *.elf *.dis

# 伪目标声明
.PHONY: all clean