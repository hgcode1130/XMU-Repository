#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// 全局变量存储子进程PID，以便父进程的信号处理函数可以访问
pid_t pid1, pid2;

// 子进程的信号处理函数
void child_handler(int sig) {
    if (getpid() == pid1) {
        printf("Child process 1 is killed by parent !\n");
    } else {
        printf("Child process 2 is killed by parent !\n");
    }
    exit(EXIT_SUCCESS);
}

// 父进程的信号处理函数
void parent_handler(int sig) {
    printf("\nParent caught Ctrl+C (SIGINT). Sending signals to children.\n");
    
    // 向两个子进程发送SIGUSR1信号
    kill(pid1, SIGUSR1);
    kill(pid2, SIGUSR1);
    
    // 等待两个子进程都终止
    wait(NULL);
    wait(NULL);
    
    printf("Parent process is killed!\n");
    exit(EXIT_SUCCESS);
}

int main() {
    // 设置父进程捕捉SIGINT信号
    signal(SIGINT, parent_handler);

    // 创建第一个子进程
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork 1 failed");
        exit(EXIT_FAILURE);
    }
    
    if (pid1 == 0) { // 第一个子进程的代码
        signal(SIGUSR1, child_handler); // 设置自己的信号处理函数
        printf("Child process 1 (PID: %d) is waiting...\n", getpid());
        while(1) {
            pause(); // 挂起等待信号
        }
    } else { // 父进程的代码
        // 创建第二个子进程
        pid2 = fork();
        if (pid2 < 0) {
            perror("fork 2 failed");
            // 需要先杀死已经创建的子进程1
            kill(pid1, SIGKILL);
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) { // 第二个子进程的代码
            signal(SIGUSR1, child_handler); // 设置自己的信号处理函数
            printf("Child process 2 (PID: %d) is waiting...\n", getpid());
            while(1) {
                pause(); // 挂起等待信号
            }
        } else { // 父进程的代码
            printf("Parent process (PID: %d) created two children (PID: %d, PID: %d).\n", getpid(), pid1, pid2);
            printf("Press Ctrl+C to terminate all processes.\n");
            // 父进程也挂起等待，直到SIGINT信号到来
            while(1) {
                pause();
            }
        }
    }
    return 0; // 正常情况下不会执行到这里
}