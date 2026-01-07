#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        // 子进程执行路径
        printf("子进程: pid=%d, 父pid=%d\n", getpid(), getppid());
        return 0;
    } else {
        // 父进程执行路径
        printf("父进程: pid=%d, 子pid=%d\n", getpid(), pid);
        int status = 0;
        if (waitpid(pid, &status, 0) < 0) {
            perror("waitpid");
            return 1;
        }
        if (WIFEXITED(status)) {
            printf("父进程: 子进程正常退出, exit_code=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("父进程: 子进程被信号(%d)终止\n", WTERMSIG(status));
        }
    }
    return 0;
}

