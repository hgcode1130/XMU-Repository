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

    // 使用相同的键值获取消息队列ID
    // 注意：这里也用 IPC_CREAT 是为了健壮性，万一接收者先启动，也能创建队列
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Receiver process ready. Waiting for messages...\n");

    while(1) {
        // 接收消息，如果队列为空则阻塞等待
        if (msgrcv(msgid, &msg, MAXMSG, 0, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }

        printf("Message received: \"%s\"\n", msg.some_text);

        // 如果收到 "end"，则退出循环
        if (strncmp(msg.some_text, "end", 3) == 0) {
            break;
        }
    }

    // 接收到 "end" 后，由接收方负责删除消息队列
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        perror("msgctl(IPC_RMID) failed");
        exit(EXIT_FAILURE);
    }

    printf("Receiver process received 'end', removed queue, and will exit.\n");
    exit(EXIT_SUCCESS);
}