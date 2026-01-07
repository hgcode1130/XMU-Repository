#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define N 64

int main(int argc, char *argv[])//./server ip port
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buf[N] = {0};

    if (argc < 3)
    {
        printf("usage:%s ip port\n", argv[0]);
        return 0;
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(-1);
    }


    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2]));//"6000"--6000 htons(6000);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    while (1)
    {
        printf(">");
        fgets(buf, N, stdin);
        sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr *) &servaddr, sizeof(servaddr));

        memset(buf, 0, sizeof(buf));
        recvfrom(sockfd, buf, N, 0, NULL, NULL);
        printf("%s\n", buf);
    }
    close(sockfd);

    return 0;
}
