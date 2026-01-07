/*
 * myshell.c - MyShell 主程序
 * 
 * 功能：实现一个简单的 shell 程序，支持内部命令、外部程序执行、
 *       I/O 重定向、后台执行和批处理模式
 * 作者：操作系统课程项目
 */

#include "myshell.h"

/* 全局变量：批处理文件指针 */
static FILE *batch_file = NULL;

/* ========== 主函数 ========== */

/**
 * main - 程序入口
 * 
 * 功能：初始化环境变量，处理批处理模式，进入主循环
 * 参数：argc - 参数数量，argv - 参数数组
 * 返回：0 表示正常退出
 */
int main(int argc, char *argv[]) {
    char shell_path[MAX_PATH];
    char *line;
    Command *cmd;
    int result;
    FILE *input = stdin;  /* 默认从标准输入读取 */
    
    /* 获取程序的完整路径并设置 shell 环境变量 */
    if (realpath(argv[0], shell_path) != NULL) {
        setenv("shell", shell_path, 1);
    } else {
        /* 如果 realpath 失败，使用 argv[0] */
        setenv("shell", argv[0], 1);
    }
    
    /* 检查是否为批处理模式 */
    if (argc > 1) {
        batch_file = fopen(argv[1], "r");
        if (batch_file == NULL) {
            fprintf(stderr, "myshell: 无法打开批处理文件 '%s': %s\n", 
                    argv[1], strerror(errno));
            return 1;
        }
        input = batch_file;
    }
    
    /* 主循环 */
    while (1) {
        /* 如果是交互模式，显示提示符 */
        if (input == stdin) {
            display_prompt();
        }
        
        /* 读取命令行 */
        line = read_command(input);
        if (line == NULL) {
            /* 文件结束或读取错误 */
            break;
        }
        
        /* 跳过空行和注释 */
        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }
        
        /* 解析命令 */
        cmd = parse_command(line);
        if (cmd == NULL) {
            continue;
        }
        
        /* 执行命令 */
        result = execute_command(cmd);
        
        /* 释放命令结构体 */
        free_command(cmd);
        
        /* 检查是否退出 */
        if (result == -999) {
            break;
        }
    }
    
    /* 关闭批处理文件 */
    if (batch_file != NULL) {
        fclose(batch_file);
    }
    
    return 0;
}

/* ========== 辅助函数实现 ========== */

/**
 * display_prompt - 显示命令提示符
 * 
 * 功能：显示包含当前工作目录的提示符
 */
void display_prompt() {
    char cwd[MAX_PATH];
    
    /* 获取当前工作目录 */
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s> ", cwd);
    } else {
        printf("myshell> ");
    }
    
    /* 刷新输出缓冲区 */
    fflush(stdout);
}

/**
 * read_command - 读取命令行
 * 
 * 功能：从指定输入流读取一行命令
 * 参数：input - 输入流（标准输入或批处理文件）
 * 返回：命令字符串指针，失败返回 NULL
 */
char* read_command(FILE *input) {
    static char buffer[MAX_LINE];
    char *result;
    int len;
    
    /* 读取一行 */
    result = fgets(buffer, MAX_LINE, input);
    if (result == NULL) {
        return NULL;
    }
    
    /* 去除末尾的换行符 */
    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    return buffer;
}

/**
 * parse_command - 解析命令行
 * 
 * 功能：将命令行字符串解析为 Command 结构体
 *       识别参数、重定向符号（<、>、>>）和后台执行符号（&）
 * 参数：line - 命令行字符串
 * 返回：Command 结构体指针，失败返回 NULL
 */
Command* parse_command(char *line) {
    static Command cmd;
    static char line_copy[MAX_LINE];
    char *token;

    /* 初始化 Command 结构体 */
    cmd.argc = 0;
    cmd.input_file = NULL;
    cmd.output_file = NULL;
    cmd.append_mode = 0;
    cmd.background = 0;
    
    /* 复制命令行，因为 strtok 会修改原字符串 */
    strncpy(line_copy, line, MAX_LINE - 1);
    line_copy[MAX_LINE - 1] = '\0';
    
    /* 使用 strtok 分割命令行 */
    token = strtok(line_copy, " \t");
    
    while (token != NULL && cmd.argc < MAX_ARGS - 1) {
        /* 检查是否为重定向符号 */
        if (strcmp(token, "<") == 0) {
            /* 输入重定向 */
            token = strtok(NULL, " \t");
            if (token != NULL) {
                cmd.input_file = token;
            }
        } else if (strcmp(token, ">") == 0) {
            /* 输出重定向（覆盖模式） */
            token = strtok(NULL, " \t");
            if (token != NULL) {
                cmd.output_file = token;
                cmd.append_mode = 0;
            }
        } else if (strcmp(token, ">>") == 0) {
            /* 输出重定向（追加模式） */
            token = strtok(NULL, " \t");
            if (token != NULL) {
                cmd.output_file = token;
                cmd.append_mode = 1;
            }
        } else if (strcmp(token, "&") == 0) {
            /* 后台执行 */
            cmd.background = 1;
        } else {
            /* 普通参数 */
            cmd.args[cmd.argc++] = token;
        }
        
        token = strtok(NULL, " \t");
    }
    
    /* 参数数组以 NULL 结尾（execvp 需要） */
    cmd.args[cmd.argc] = NULL;
    
    /* 如果没有参数，返回 NULL */
    if (cmd.argc == 0) {
        return NULL;
    }
    
    return &cmd;
}

/**
 * free_command - 释放命令结构体
 * 
 * 功能：释放 Command 结构体占用的内存
 * 参数：cmd - Command 结构体指针
 */
void free_command(Command *cmd) {
    /* 当前实现使用静态结构体，无需释放 */
    /* 如果将来改为动态分配，在此处添加 free 调用 */
}

/* ========== 内部命令实现（简单命令） ========== */

/**
 * cmd_cd - 改变当前目录命令
 * 
 * 功能：改变当前工作目录，更新 PWD 环境变量
 *       无参数时显示当前目录
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int cmd_cd(Command *cmd) {
    char cwd[MAX_PATH];
    
    if (cmd->argc == 1) {
        /* 无参数，显示当前目录 */
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("cd");
            return -1;
        }
    } else {
        /* 改变目录 */
        if (chdir(cmd->args[1]) != 0) {
            perror("cd");
            return -1;
        }
        
        /* 更新 PWD 环境变量 */
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            setenv("PWD", cwd, 1);
        }
    }
    
    return 0;
}

/**
 * cmd_clr - 清屏命令
 * 
 * 功能：清除屏幕内容
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功
 */
int cmd_clr(Command *cmd) {
    /* 使用 ANSI 转义序列清屏 */
    printf("\033[2J\033[H");
    fflush(stdout);
    return 0;
}

/**
 * cmd_quit - 退出命令
 * 
 * 功能：退出 shell 程序
 * 参数：cmd - Command 结构体指针
 * 返回：-999 表示退出信号
 */
int cmd_quit(Command *cmd) {
    return -999;
}

/**
 * cmd_pause - 暂停命令
 *
 * 功能：暂停 shell 操作直到用户按下回车键
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功
 */
int cmd_pause(Command *cmd) {
    printf("按回车键继续...\n");
    getchar();
    return 0;
}

/* ========== 命令执行调度（临时实现） ========== */

/**
 * execute_command - 执行命令
 *
 * 功能：判断命令类型（内部命令或外部程序）并执行
 *       支持内部命令的输出重定向（dir、echo）
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败，-999 表示退出 shell
 */
int execute_command(Command *cmd) {
    int saved_stdout = -1;
    int result = 0;
    int fd_out;
    int flags;

    /* 检查空命令 */
    if (cmd == NULL || cmd->argc == 0) {
        return 0;
    }

    /* 获取命令名 */
    char *command = cmd->args[0];

    /* 判断是否为内部命令 */
    if (strcmp(command, "cd") == 0) {
        return cmd_cd(cmd);
    } else if (strcmp(command, "clr") == 0) {
        return cmd_clr(cmd);
    } else if (strcmp(command, "quit") == 0) {
        return cmd_quit(cmd);
    } else if (strcmp(command, "pause") == 0) {
        return cmd_pause(cmd);
    } else if (strcmp(command, "dir") == 0 || strcmp(command, "echo") == 0) {
        /* dir 和 echo 支持输出重定向 */

        /* 如果有输出重定向，保存原 stdout */
        if (cmd->output_file != NULL) {
            saved_stdout = dup(STDOUT_FILENO);
            if (saved_stdout < 0) {
                perror("dup");
                return -1;
            }

            /* 打开输出文件 */
            flags = O_WRONLY | O_CREAT;
            if (cmd->append_mode) {
                flags |= O_APPEND;
            } else {
                flags |= O_TRUNC;
            }

            fd_out = open(cmd->output_file, flags, 0644);
            if (fd_out < 0) {
                perror("输出重定向");
                close(saved_stdout);
                return -1;
            }

            /* 重定向标准输出 */
            if (dup2(fd_out, STDOUT_FILENO) < 0) {
                perror("dup2");
                close(fd_out);
                close(saved_stdout);
                return -1;
            }

            close(fd_out);
        }

        /* 执行命令 */
        if (strcmp(command, "dir") == 0) {
            result = cmd_dir(cmd);
        } else {
            result = cmd_echo(cmd);
        }

        /* 恢复原 stdout */
        if (saved_stdout >= 0) {
            dup2(saved_stdout, STDOUT_FILENO);
            close(saved_stdout);
        }

        return result;
    } else if (strcmp(command, "environ") == 0) {
        return cmd_environ(cmd);
    } else if (strcmp(command, "help") == 0) {
        return cmd_help(cmd);
    } else {
        /* 外部程序，调用 execute_external */
        return execute_external(cmd);
    }

    return 0;
}

