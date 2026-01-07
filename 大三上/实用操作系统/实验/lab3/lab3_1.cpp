#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MAXMSG 512 

struct my_msg {
    long int my_msg_type;
    char some_text[MAXMSG];
};

int main() {
    int pid;
    int msgid;
    struct my_msg msg;
    char buffer[BUFSIZ];
    
    // 1. 创建消息队列，键值为1234，权限为0666
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }
    
    // 2. 创建子进程
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    
    // 3. 子进程代码块
    if (pid == 0) {
        printf("Child process starts sending messages.\n");
        while(1) {
            printf("Enter some text: ");
            fgets(buffer, BUFSIZ, stdin);
            
            buffer[strcspn(buffer, "\n")] = 0;

            msg.my_msg_type = 1;
            strcpy(msg.some_text, buffer);
            
            if (msgsnd(msgid, &msg, MAXMSG, 0) == -1) {
                perror("msgsnd failed");
                exit(EXIT_FAILURE);
            }
            
            if (strncmp(msg.some_text, "end", 3) == 0) {
                break;
            }
        }
        printf("Child process finished sending and will exit.\n");
        exit(EXIT_SUCCESS);
    }
    // 4. 父进程代码块
    else {
        printf("Parent process is waiting for the child process to finish...\n");
        wait(NULL);
        printf("Parent process detected child has finished. Now receiving messages.\n");

        // 子进程结束后，开始接收消息
        while(1) {
            if (msgrcv(msgid, &msg, MAXMSG, 0, 0) == -1) {
                perror("msgrcv failed");
                exit(EXIT_FAILURE);
            }
            
            printf("Parent received: \"%s\"\n", msg.some_text);
            
            // 如果消息为 "end"，则跳出循环
            if (strncmp(msg.some_text, "end", 3) == 0) {
                break;
            }
        }
        
        // 5. 撤销（删除）消息队列
        if (msgctl(msgid, IPC_RMID, 0) == -1) {
            perror("msgctl(IPC_RMID) failed");
            exit(EXIT_FAILURE);
        }
        
        printf("Message queue removed. Parent process will exit.\n");
        exit(EXIT_SUCCESS);
    }
}