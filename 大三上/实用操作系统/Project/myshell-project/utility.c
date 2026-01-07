/*
 * utility.c - MyShell 工具函数
 * 
 * 功能：实现工具类内部命令和外部程序执行功能
 * 作者：操作系统课程项目
 */

#include "myshell.h"

/* 外部环境变量数组 */
extern char **environ;

/* ========== 工具类内部命令实现 ========== */

/**
 * cmd_dir - 列出目录内容命令
 * 
 * 功能：列出指定目录的内容，无参数时列出当前目录
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int cmd_dir(Command *cmd) {
    char *path;
    DIR *dir;
    struct dirent *entry;
    
    /* 确定目录路径 */
    if (cmd->argc == 1) {
        path = ".";  /* 当前目录 */
    } else {
        path = cmd->args[1];
    }
    
    /* 打开目录 */
    dir = opendir(path);
    if (dir == NULL) {
        perror("dir");
        return -1;
    }
    
    /* 读取并打印目录项 */
    while ((entry = readdir(dir)) != NULL) {
        /* 跳过 . 和 .. */
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        /* 打印文件/目录名 */
        printf("%s\n", entry->d_name);
    }
    
    /* 关闭目录 */
    closedir(dir);
    
    return 0;
}

/**
 * cmd_environ - 列出环境变量命令
 * 
 * 功能：列出所有环境变量
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功
 */
int cmd_environ(Command *cmd) {
    int i;
    
    /* 遍历环境变量数组 */
    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    
    return 0;
}

/**
 * cmd_echo - 输出文本命令
 * 
 * 功能：在屏幕上显示文本并换行
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功
 */
int cmd_echo(Command *cmd) {
    int i;
    
    /* 从第二个参数开始打印（第一个是命令名 echo） */
    for (i = 1; i < cmd->argc; i++) {
        printf("%s", cmd->args[i]);
        
        /* 参数之间打印空格 */
        if (i < cmd->argc - 1) {
            printf(" ");
        }
    }
    
    /* 打印换行符 */
    printf("\n");
    
    return 0;
}

/**
 * cmd_help - 显示帮助命令
 * 
 * 功能：显示用户手册，使用 more 命令分页
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int cmd_help(Command *cmd) {
    FILE *readme_file;
    FILE *more_pipe;
    char buffer[MAX_LINE];
    
    /* 打开 readme 文件 */
    readme_file = fopen("readme", "r");
    if (readme_file == NULL) {
        /* readme 文件不存在，显示简短帮助信息 */
        printf("MyShell - 简单的命令行解释器\n\n");
        printf("内部命令：\n");
        printf("  cd [directory]  - 改变当前目录\n");
        printf("  clr             - 清屏\n");
        printf("  dir [directory] - 列出目录内容\n");
        printf("  environ         - 列出所有环境变量\n");
        printf("  echo <text>     - 显示文本\n");
        printf("  help            - 显示帮助信息\n");
        printf("  pause           - 暂停直到按回车\n");
        printf("  quit            - 退出 shell\n\n");
        printf("支持 I/O 重定向：<, >, >>\n");
        printf("支持后台执行：&\n");
        return 0;
    }
    
    /* 打开管道到 more 命令 */
    more_pipe = popen("more", "w");
    if (more_pipe == NULL) {
        /* more 命令不可用，直接输出到标准输出 */
        while (fgets(buffer, MAX_LINE, readme_file) != NULL) {
            printf("%s", buffer);
        }
        fclose(readme_file);
        return 0;
    }
    
    /* 逐行读取 readme 并写入 more 管道 */
    while (fgets(buffer, MAX_LINE, readme_file) != NULL) {
        fprintf(more_pipe, "%s", buffer);
    }
    
    /* 关闭文件和管道 */
    fclose(readme_file);
    pclose(more_pipe);
    
    return 0;
}

/* ========== 外部程序执行和 I/O 重定向 ========== */

/**
 * setup_redirection - 设置 I/O 重定向
 *
 * 功能：根据 Command 结构体设置输入输出重定向
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int setup_redirection(Command *cmd) {
    int fd_in, fd_out;
    int flags;

    /* 处理输入重定向 */
    if (cmd->input_file != NULL) {
        fd_in = open(cmd->input_file, O_RDONLY);
        if (fd_in < 0) {
            perror("输入重定向");
            return -1;
        }

        /* 重定向标准输入 */
        if (dup2(fd_in, STDIN_FILENO) < 0) {
            perror("dup2");
            close(fd_in);
            return -1;
        }

        close(fd_in);
    }

    /* 处理输出重定向 */
    if (cmd->output_file != NULL) {
        /* 确定打开标志 */
        flags = O_WRONLY | O_CREAT;

        if (cmd->append_mode) {
            /* 追加模式 */
            flags |= O_APPEND;
        } else {
            /* 覆盖模式 */
            flags |= O_TRUNC;
        }

        /* 打开输出文件 */
        fd_out = open(cmd->output_file, flags, 0644);
        if (fd_out < 0) {
            perror("输出重定向");
            return -1;
        }

        /* 重定向标准输出 */
        if (dup2(fd_out, STDOUT_FILENO) < 0) {
            perror("dup2");
            close(fd_out);
            return -1;
        }

        close(fd_out);
    }

    return 0;
}

/**
 * execute_external - 执行外部程序
 *
 * 功能：使用 fork/exec 执行外部程序，支持后台执行
 * 参数：cmd - Command 结构体指针
 * 返回：0 表示成功，-1 表示失败
 */
int execute_external(Command *cmd) {
    pid_t pid;
    int status;

    /* 创建子进程 */
    pid = fork();

    if (pid < 0) {
        /* fork 失败 */
        perror("fork");
        return -1;
    } else if (pid == 0) {
        /* 子进程 */

        /* 设置 I/O 重定向 */
        if (setup_redirection(cmd) < 0) {
            exit(1);
        }

        /* 执行外部程序 */
        execvp(cmd->args[0], cmd->args);

        /* 如果 execvp 返回，说明执行失败 */
        perror(cmd->args[0]);
        exit(1);
    } else {
        /* 父进程 */

        if (cmd->background) {
            /* 后台执行 */
            printf("[后台进程] PID: %d\n", pid);
        } else {
            /* 前台执行，等待子进程结束 */
            if (waitpid(pid, &status, 0) < 0) {
                perror("waitpid");
                return -1;
            }

            /* 检查子进程退出状态 */
            if (WIFEXITED(status)) {
                /* 正常退出 */
                int exit_status = WEXITSTATUS(status);
                if (exit_status != 0) {
                    /* 非零退出状态 */
                    return -1;
                }
            } else {
                /* 异常退出 */
                return -1;
            }
        }
    }

    return 0;
}

