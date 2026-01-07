#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 目标: 观察 fork 后父/子进程中同名(同地址)变量的行为
// 结论: 虚拟地址可能一致, 但属于不同进程的独立地址空间(写时复制), 不是临界资源。

int x = 0; // 全局变量(便于观察地址和值)

int main(void) {
    printf("初始: pid=%d, x=%d, &x=%p\n", getpid(), x, (void*)&x);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        for (int i = 0; i < 1000000; ++i) x++; // 子进程递增
        printf("子进程: pid=%d, x=%d, &x=%p\n", getpid(), x, (void*)&x);
        return 0;
    } else {
        for (int i = 0; i < 1000000; ++i) x++; // 父进程递增
        printf("父进程: pid=%d, x=%d, &x=%p\n", getpid(), x, (void*)&x);
        int status = 0;
        waitpid(pid, &status, 0);
    }

    // 期望输出: 父/子各自的 x 都独立达到 1000000, 说明并未共享, 非临界资源。
    return 0;
}

