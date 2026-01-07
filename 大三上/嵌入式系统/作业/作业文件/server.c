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
    struct sockaddr_in myaddr, peeraddr;
    char buf[N] = {0};
    socklen_t len;
    ssize_t n;

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


    memset(&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(atoi(argv[2]));//"6000"--6000 htons(6000);
    myaddr.sin_addr.s_addr = inet_addr(argv[1]);
    
    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
        perror("bind");
        exit(-1);
    }

    memset(&peeraddr, 0, sizeof(peeraddr));
    len = sizeof(peeraddr);

    while (1)
    {
        memset(buf, 0, sizeof(buf));
        n = recvfrom(sockfd, buf, N, 0, (struct sockaddr *)&peeraddr, &len);
        printf("from %s:%d %s\n", inet_ntoa(peeraddr.sin_addr),
                ntohs(peeraddr.sin_port), buf);
        sendto(sockfd, buf, n, 0, (struct sockaddr *)&peeraddr, sizeof(peeraddr));
    }
    close(sockfd);

    return 0;
}
