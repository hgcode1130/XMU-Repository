/*
 * myshell.h - MyShell 头文件
 * 
 * 功能：定义 myshell 程序的所有常量、数据结构和函数原型
 * 作者：操作系统课程项目
 */

#ifndef MYSHELL_H
#define MYSHELL_H

/* ========== 系统头文件 ========== */
#include <stdio.h>      /* 标准输入输出 */
#include <stdlib.h>     /* 标准库函数 */
#include <string.h>     /* 字符串处理 */
#include <unistd.h>     /* UNIX 标准函数 */
#include <sys/types.h>  /* 系统数据类型 */
#include <sys/wait.h>   /* 进程等待 */
#include <fcntl.h>      /* 文件控制 */
#include <dirent.h>     /* 目录操作 */
#include <errno.h>      /* 错误处理 */

/* ========== 常量定义 ========== */
#define MAX_LINE 1024   /* 最大命令行长度 */
#define MAX_ARGS 64     /* 最大参数数量 */
#define MAX_PATH 1024   /* 最大路径长度 */

/* ========== 数据结构定义 ========== */

/**
 * Command 结构体 - 表示一个解析后的命令
 * 
 * 字段说明：
 *   args[]       - 参数数组，args[0] 是命令名，以 NULL 结尾
 *   argc         - 参数数量（包括命令名）
 *   input_file   - 输入重定向文件名（< 符号），NULL 表示无重定向
 *   output_file  - 输出重定向文件名（> 或 >> 符号），NULL 表示无重定向
 *   append_mode  - 输出追加模式标志：1 表示追加(>>)，0 表示覆盖(>)
 *   background   - 后台执行标志：1 表示后台执行(&)，0 表示前台执行
 */
typedef struct {
    char *args[MAX_ARGS];   /* 参数数组 */
    int argc;               /* 参数数量 */
    char *input_file;       /* 输入重定向文件 */
    char *output_file;      /* 输出重定向文件 */
    int append_mode;        /* 追加模式标志 */
    int background;         /* 后台执行标志 */
} Command;

/* ========== 函数原型声明（myshell.c 中实现） ========== */

/**
 * display_prompt - 显示命令提示符
 * 
 * 功能：显示包含当前工作目录的提示符
 * 参数：无
 * 返回：无
 */
void display_prompt();

/**
 * read_command - 读取命令行
 * 
 * 功能：从指定输入流读取一行命令
 * 参数：input - 输入流（标准输入或批处理文件）
 * 返回：命令字符串指针，失败返回 NULL
 */
char* read_command(FILE *input);

/**
 * parse_command - 解析命令行
 * 
 * 功能：将命令行字符串解析为 Command 结构体
 *       识别参数、重定向符号（<、>、>>）和后台执行符号（&）
 * 参数：line - 命令行字符串
 * 返回：Command 结构体指针，失败返回 NULL
 */
Command* parse_command(char *line);

/**
 * execute_command - 执行命令
 * 
 * 功能：判断命令类型（内部命令或外部程序）并执行
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败，-999 表示退出 shell
 */
int execute_command(Command *cmd);

/**
 * free_command - 释放命令结构体
 * 
 * 功能：释放 Command 结构体占用的内存
 * 参数：cmd - Command 结构体指针
 * 返回：无
 */
void free_command(Command *cmd);

/**
 * cmd_cd - 改变当前目录命令
 * 
 * 功能：改变当前工作目录，更新 PWD 环境变量
 *       无参数时显示当前目录
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int cmd_cd(Command *cmd);

/**
 * cmd_clr - 清屏命令
 * 
 * 功能：清除屏幕内容
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功
 */
int cmd_clr(Command *cmd);

/**
 * cmd_quit - 退出命令
 * 
 * 功能：退出 shell 程序
 * 参数：cmd - Command 结构体指针
 * 返回：-999 表示退出信号
 */
int cmd_quit(Command *cmd);

/**
 * cmd_pause - 暂停命令
 * 
 * 功能：暂停 shell 操作直到用户按下回车键
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功
 */
int cmd_pause(Command *cmd);

/* ========== 函数原型声明（utility.c 中实现） ========== */

/**
 * cmd_dir - 列出目录内容命令
 * 
 * 功能：列出指定目录的内容，无参数时列出当前目录
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int cmd_dir(Command *cmd);

/**
 * cmd_environ - 列出环境变量命令
 * 
 * 功能：列出所有环境变量
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功
 */
int cmd_environ(Command *cmd);

/**
 * cmd_echo - 输出文本命令
 * 
 * 功能：在屏幕上显示文本并换行
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功
 */
int cmd_echo(Command *cmd);

/**
 * cmd_help - 显示帮助命令
 * 
 * 功能：显示用户手册，使用 more 命令分页
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int cmd_help(Command *cmd);

/**
 * execute_external - 执行外部程序
 * 
 * 功能：使用 fork/exec 执行外部程序，支持后台执行
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int execute_external(Command *cmd);

/**
 * setup_redirection - 设置 I/O 重定向
 * 
 * 功能：根据 Command 结构体设置输入输出重定向
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int setup_redirection(Command *cmd);

#endif /* MYSHELL_H */

