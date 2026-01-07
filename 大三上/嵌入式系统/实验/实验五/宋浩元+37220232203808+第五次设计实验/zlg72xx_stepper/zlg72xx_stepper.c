#define _DEFAULT_SOURCE

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define SET_VAL   _IO('Z', 0)
#define GET_KEY   _IO('Z', 1)

#define STEPPER_ON   0
#define STEPPER_OFF  1

#define KEY_DEVICE      "/dev/zlg72xx"
#define STEPPER_DEVICE  "/dev/stepper"

static int fd_key = -1;
static int fd_stepper = -1;
static unsigned int key1 = 0;
static unsigned int key2 = 0;
static unsigned int times = 900;

static const int step_clockwise[8][4] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

static const int step_anticlockwise[8][4] = {
    {1, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 1, 1},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 1, 0, 0},
    {1, 1, 0, 0},
    {1, 0, 0, 0}
};

static void apply_step(const int pattern[4])
{
    for (int phase = 0; phase < 4; ++phase) {
        int cmd = pattern[phase] ? STEPPER_ON : STEPPER_OFF;
        ioctl(fd_stepper, cmd, phase);
    }
}

static void run_sequence(const int sequence[8][4])
{
    for (int step = 0; step < 8; ++step) {
        apply_step(sequence[step]);
        usleep(times);
    }
}

static void reset_coils(void)
{
    static const int off_pattern[4] = {0, 0, 0, 0};
    apply_step(off_pattern);
}

static char translate_key(int keycode)
{
    switch (keycode) {
        case 28: return '1';
        case 27: return '2';
        case 26: return '3';
        case 25: return 'A';
        case 20: return '4';
        case 19: return '5';
        case 18: return '6';
        case 17: return 'B';
        case 12: return '7';
        case 11: return '8';
        case 10: return '9';
        case 9:  return 'C';
        case 4:  return '*';
        case 3:  return '0';
        case 2:  return '#';
        case 1:  return 'D';
        default: return 0x00;
    }
}

static void *stepper_clockwise(void *data)
{
    (void)data;
    while (1) {
        if (key1 == 1) {
            run_sequence(step_clockwise);
        }
    }
    return NULL;
}

static void *stepper_anticlockwise(void *data)
{
    (void)data;
    while (1) {
        if (key2 == 1) {
            run_sequence(step_anticlockwise);
        }
    }
    return NULL;
}

int main(void)
{
    int key = 0;
    char value = 0;
    pthread_t th_stepper_clockwise;
    pthread_t th_stepper_anticlockwise;

    fd_key = open(KEY_DEVICE, O_RDWR);
    if (fd_key < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_stepper = open(STEPPER_DEVICE, O_RDWR);
    if (fd_stepper < 0) {
        perror("Can't open file farsight_stepper,Check your path");
        close(fd_key);
        exit(EXIT_FAILURE);
    }

    reset_coils();

    pthread_create(&th_stepper_clockwise, NULL, stepper_clockwise, NULL);
    pthread_create(&th_stepper_anticlockwise, NULL, stepper_anticlockwise, NULL);

    while (1) {
        ioctl(fd_key, GET_KEY, &key);
        value = translate_key(key);

        if (value != 0x00) {
            printf("put is '%c'\n", value);
        }

        if (value == '1') {
            if (key1 == 0) {
                key1 = 1;
                key2 = 0;
            } else {
                key1 = 0;
                key2 = 0;
            }
        }

        if (value == '2') {
            if (key2 == 0) {
                key1 = 0;
                key2 = 1;
            } else {
                key1 = 0;
                key2 = 0;
            }
        }
    }

    pthread_join(th_stepper_clockwise, NULL);
    pthread_join(th_stepper_anticlockwise, NULL);

    close(fd_stepper);
    close(fd_key);
    return 0;
}
