#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

static void child_loop(const char *name) {
    // 持续输出自身在执行, 直到被父进程终止
    while (1) {
        printf("%s正在执行….. (pid=%d)\n", name, getpid());
        fflush(stdout);
        sleep(1);
    }
}

int main(void) {
    // 行缓冲, 方便看到交错输出
    setvbuf(stdout, NULL, _IOLBF, 0);

    pid_t c1 = fork();
    if (c1 < 0) { perror("fork c1"); exit(1); }
    if (c1 == 0) { child_loop("子进程1"); return 0; }

    pid_t c2 = fork();
    if (c2 < 0) {
        perror("fork c2");
        kill(c1, SIGTERM);
        waitpid(c1, NULL, 0);
        exit(1);
    }
    if (c2 == 0) { child_loop("子进程2"); return 0; }

    // 父进程并发输出一段时间
    for (int i = 0; i < 5; ++i) {
        printf("父进程正在执行….. (pid=%d)\n", getpid());
        fflush(stdout);
        sleep(1);
    }

    // 一段时间后, 父进程终止两个子进程
    kill(c1, SIGTERM);
    kill(c2, SIGTERM);

    int status = 0;
    pid_t w = waitpid(c1, &status, 0);
    if (w == c1) {
        if (WIFSIGNALED(status)) {
            printf("子进程1被父进程杀死\n");
        } else {
            printf("子进程1已退出\n");
        }
    }
    w = waitpid(c2, &status, 0);
    if (w == c2) {
        if (WIFSIGNALED(status)) {
            printf("子进程2被父进程杀死\n");
        } else {
            printf("子进程2已退出\n");
        }
    }

    printf("父进程结束\n");
    return 0;
}

