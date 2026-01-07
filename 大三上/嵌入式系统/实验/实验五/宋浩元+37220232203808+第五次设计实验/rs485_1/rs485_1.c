#define _GNU_SOURCE
#define _DEFAULT_SOURCE

#include <errno.h>
#include <fcntl.h>
#include <iconv.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define ENDMINITERM 27

static int fd_485 = -1;

static void serial_init(void)
{
    struct termios options;

    tcgetattr(fd_485, &options);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag &= ~CRTSCTS;
    options.c_cflag |= CS8;
    options.c_cflag &= ~CSTOPB;
    options.c_iflag |= IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;

    if (cfsetispeed(&options, B115200) == -1) {
        printf("cfsetispeed is erro\n");
        exit(EXIT_FAILURE);
    }

    tcsetattr(fd_485, TCSANOW, &options);
}

static unsigned short getch(void)
{
    struct termios current;
    struct termios original;

    if (tcgetattr(STDIN_FILENO, &current) < 0) {
        return (unsigned short)-1;
    }

    original = current;
    cfmakeraw(&current);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &current) < 0) {
        return (unsigned short)-1;
    }

    int ch = getchar();

    if (tcsetattr(STDIN_FILENO, TCSANOW, &original) < 0) {
        return (unsigned short)-1;
    }

    return (unsigned short)ch;
}

static void write_stdout_char(unsigned short ch)
{
    unsigned char byte = (unsigned char)ch;
    write(STDOUT_FILENO, &byte, 1);
}

static void write_serial_char(unsigned short ch)
{
    unsigned char byte = (unsigned char)ch;
    write(fd_485, &byte, 1);
}

static void output_newline(void)
{
    write_stdout_char(0x0d);
    write_stdout_char(0x0a);
}

static void *receive(void *data)
{
    (void)data;

    printf("RS-485 Receive Begin!\n");
    output_newline();

    while (1) {
        unsigned char ch = 0;
        ssize_t nbytes = read(fd_485, &ch, 1);
        if (nbytes <= 0) {
            continue;
        }

        if (ch == '\n') {
            output_newline();
        } else {
            write_stdout_char(ch);
        }

        if (ch == ENDMINITERM) {
            break;
        }
    }

    printf("RS-485 Receive End!\n");
    output_newline();
    return NULL;
}

static void sleep_short(unsigned int usec)
{
    struct timespec req = {
        .tv_sec = usec / 1000000u,
        .tv_nsec = (long)((usec % 1000000u) * 1000u)
    };

    while (nanosleep(&req, &req) == -1 && errno == EINTR) {
        continue;
    }
}

int main(void)
{
    pthread_t th_receive;
    unsigned short ch;

    fd_485 = open("/dev/ttyS0", O_RDWR);
    if (fd_485 < 0) {
        perror("fail to open serial port");
        return EXIT_FAILURE;
    }

    serial_init();

    pthread_create(&th_receive, NULL, receive, NULL);

    printf("Please press the keys on the computer keyboard, then watch the monitor of another computer\n\n");
    printf("Press the Esc key to exit the program\n\n");
    printf("RS-485 Send Begin!\n");
    output_newline();

    while (1) {
        ch = getch();
        if (ch == (unsigned short)-1) {
            continue;
        }

        if (ch == '\r') {
            write_stdout_char('\n');
            write_serial_char('\n');
        } else {
            write_stdout_char(ch);
            write_serial_char(ch);
        }

        if (ch == ENDMINITERM) {
            break;
        }

        sleep_short(50);
    }

    pthread_join(th_receive, NULL);

    close(fd_485);
    fd_485 = -1;

    printf("RS-485 Send End!\n");
    output_newline();
    return EXIT_SUCCESS;
}
