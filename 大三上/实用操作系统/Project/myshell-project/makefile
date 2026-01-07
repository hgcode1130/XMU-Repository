# MyShell Makefile
# 编译配置文件

# 编译器和编译选项
CC = gcc
CFLAGS = -Wall

# 目标文件
TARGET = myshell

# 源文件
SOURCES = myshell.c utility.c
HEADERS = myshell.h

# 默认目标：编译 myshell
$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

# 清理编译产物
clean:
	rm -f $(TARGET) *.o

# 伪目标声明
.PHONY: clean

