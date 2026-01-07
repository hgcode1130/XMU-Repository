#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <time.h>

#define SET_VAL _IO('Z', 0)
#define GET_KEY _IO('Z', 1)

#define STEPPER_ON  0
#define STEPPER_OFF 1

#define KEY_DEVICE     "/dev/zlg72xx"
#define STEPPER_DEVICE "/dev/stepper"

static volatile sig_atomic_t keep_running = 1;
static int fd_key = -1;
static int fd_stepper = -1;
static unsigned int times = 900;

/* 顺时针 8 步驱动序列，元素表示四相线圈的开关状态 */
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

/* 逆时针 8 步驱动序列 */
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

static void signal_handler(int signo)
{
    (void)signo;
    keep_running = 0;
}

static void apply_step(const int pattern[4])
{
    for (int phase = 0; phase < 4; ++phase) {
        int cmd = pattern[phase] ? STEPPER_ON : STEPPER_OFF;
        if (ioctl(fd_stepper, cmd, phase) == -1) {
            perror("设置步进电机相位失败");
            keep_running = 0;
            break;
        }
    }
}

static void reset_coils(void)
{
    static const int off_pattern[4] = {0, 0, 0, 0};
    apply_step(off_pattern);
}

static void sleep_delay(unsigned int usec)
{
    struct timespec req = {
        .tv_sec = usec / 1000000u,
        .tv_nsec = (long)((usec % 1000000u) * 1000u)
    };
    while (nanosleep(&req, &req) == -1 && errno == EINTR) {
        continue;
    }
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

static void close_devices(void)
{
    if (fd_stepper >= 0) {
        close(fd_stepper);
        fd_stepper = -1;
    }
    if (fd_key >= 0) {
        close(fd_key);
        fd_key = -1;
    }
}

int main(void)
{
    int direction = 0;      /* 0 表示停止，1 顺时针，-1 逆时针 */
    int step_index = 0;     /* 当前执行到的步序索引 */
    int keycode = 0;

    if (signal(SIGINT, signal_handler) == SIG_ERR ||
        signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("注册信号处理失败");
        return EXIT_FAILURE;
    }

    fd_key = open(KEY_DEVICE, O_RDWR);
    if (fd_key < 0) {
        perror("打开键盘设备失败");
        return EXIT_FAILURE;
    }

    fd_stepper = open(STEPPER_DEVICE, O_RDWR);
    if (fd_stepper < 0) {
        perror("打开步进电机设备失败");
        close_devices();
        return EXIT_FAILURE;
    }

    reset_coils();

    printf("Turn D8 and D9 and D10 and D11 to the left, others to the right\n\n");
    printf("Push 1 than Stepper motor rotates clockwise, Push 1 again than Stepper motor stop;\n");
    printf("Push 2 than Stepper motor rotates counterclockwise, Push 2 again than Stepper motor stop\n");

    while (keep_running) {
        if (ioctl(fd_key, GET_KEY, &keycode) == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("读取键盘失败");
            break;
        }

        char value = translate_key(keycode);
        if (value != 0x00) {
            printf("put is '%c'\n", value);
        }

        if (value == '1') {
            if (direction == 1) {
                direction = 0;
                reset_coils();
            } else {
                direction = 1;
                step_index = 0;
            }
        } else if (value == '2') {
            if (direction == -1) {
                direction = 0;
                reset_coils();
            } else {
                direction = -1;
                step_index = 0;
            }
        }

        if (direction == 1) {
            apply_step(step_clockwise[step_index]);
            step_index = (step_index + 1) % 8;
        } else if (direction == -1) {
            apply_step(step_anticlockwise[step_index]);
            step_index = (step_index + 1) % 8;
        } else {
            /* 停止状态确保线圈保持关闭 */
            reset_coils();
        }

        sleep_delay(times);
    }

    reset_coils();
    close_devices();
    return EXIT_SUCCESS;
}
