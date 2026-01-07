#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAXMSG 512

struct my_msg {
    long int my_msg_type;
    char some_text[MAXMSG];
};

int main() {
    int msgid;
    struct my_msg msg;
    char buffer[BUFSIZ];

    // 创建或获取消息队列，键值为1234
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Sender process ready. Enter messages to send.\n");

    while(1) {
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        // 移除换行符
        buffer[strcspn(buffer, "\n")] = 0;

        msg.my_msg_type = 1; // 消息类型
        strcpy(msg.some_text, buffer);

        // 发送消息
        if (msgsnd(msgid, &msg, MAXMSG, 0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }

        // 如果发送 "end"，则退出
        if (strncmp(msg.some_text, "end", 3) == 0) {
            break;
        }
    }

    printf("Sender process has sent 'end' and will exit.\n");
    exit(EXIT_SUCCESS);
}