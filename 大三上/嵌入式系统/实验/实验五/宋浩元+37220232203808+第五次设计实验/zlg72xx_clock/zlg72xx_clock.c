#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define SET_VAL _IO('Z', 0)

static const char kDigits[] = "0123456789";

static void increment_time(int *hour, int *minute, int *second)
{
    (*second)++;
    if (*second == 60) {
        *second = 0;
        (*minute)++;
        if (*minute == 60) {
            *minute = 0;
            (*hour)++;
            if (*hour == 24) {
                *hour = 0;
            }
        }
    }
}

static void build_display_buffer(int hour, int minute, int second, char buf[8])
{
    int hour_high = hour / 10;
    int hour_low = hour % 10;
    int minute_high = minute / 10;
    int minute_low = minute % 10;
    int second_high = second / 10;
    int second_low = second % 10;

    buf[0] = kDigits[hour_high];
    buf[1] = kDigits[hour_low];
    buf[2] = '-';
    buf[3] = kDigits[minute_high];
    buf[4] = kDigits[minute_low];
    buf[5] = '-';
    buf[6] = kDigits[second_high];
    buf[7] = kDigits[second_low];
}

int main(void)
{
    int hour = 23;
    int minute = 59;
    int second = 50;
    char buf[8] = {0};

    int fd = open("/dev/zlg72xx", O_RDWR);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    while (1) {
        increment_time(&hour, &minute, &second);
        build_display_buffer(hour, minute, second, buf);
        ioctl(fd, SET_VAL, buf);
        sleep(1);
    }

    close(fd);
    return EXIT_SUCCESS;
}
