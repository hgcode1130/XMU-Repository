#include <errno.h>
#include <linux/input.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define BUZZER_ON   1
#define BUZZER_OFF  0

#define IR_DEVICE      "/dev/input/event0"
#define BUZZER_DEVICE  "/dev/buzzer_ctl"

typedef struct {
    unsigned short code;
    const char *description;
    int toggles_buzzer;
} IrKeyInfo;

static const IrKeyInfo kIrKeyTable[] = {
    {0x74, "开关", 0},
    {0x72, "音量减", 0},
    {0x73, "音量加", 0},
    {0x8d, "设置", 0},
    {0x8b, "菜单", 0},
    {0x67, "up", 0},
    {0x6c, "down", 0},
    {0x69, "left", 0},
    {0x6a, "right", 0},
    {0x1c, "ok", 0},
    {0x66, "主页", 0},
    {0x01, "返回", 0},
    {0x02, "1", 1},
    {0x03, "2", 0},
    {0x04, "3", 0},
    {0x05, "4", 0},
    {0x06, "5", 0},
    {0x07, "6", 0},
    {0x08, "7", 0},
    {0x09, "8", 0},
    {0x0a, "9", 0},
    {0x0b, "0", 0},
};

static struct input_event g_input_event;

static const IrKeyInfo *find_key_info(unsigned short code)
{
    for (size_t i = 0; i < sizeof(kIrKeyTable) / sizeof(kIrKeyTable[0]); ++i) {
        if (kIrKeyTable[i].code == code) {
            return &kIrKeyTable[i];
        }
    }
    return NULL;
}

static int set_buzzer_state(int fd, int state)
{
    if (ioctl(fd, state ? BUZZER_ON : BUZZER_OFF) < 0) {
        perror("ioctl buzzer_ctl driver");
        return -1;
    }
    return 0;
}

static void toggle_buzzer(int fd, int *buzzer_state)
{
    int new_state = (*buzzer_state == 0) ? 1 : 0;
    if (set_buzzer_state(fd, new_state) == 0) {
        *buzzer_state = new_state;
    }
}

int main(void)
{
    int fd_ir = open(IR_DEVICE, O_RDWR);
    if (fd_ir < 0) {
        perror("Open file error, Check your path");
        return EXIT_FAILURE;
    }

    int fd_buzzer = open(BUZZER_DEVICE, O_RDWR);
    if (fd_buzzer < 0) {
        perror("Can't open file farsight_buzzer,Check your path");
        close(fd_ir);
        return EXIT_FAILURE;
    }

    int buzzer_state = 0;
    set_buzzer_state(fd_buzzer, 0);

    printf("Push 1 than sound the buzzer, Push 1 again than mute the buzzer\n");

    while (1) {
        ssize_t bytes_read = read(fd_ir, &g_input_event, sizeof(g_input_event));
        if (bytes_read < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("读取红外事件失败");
            break;
        }

        if (bytes_read != sizeof(g_input_event) || g_input_event.value == 0) {
            continue;
        }

        const IrKeyInfo *info = find_key_info(g_input_event.code);
        if (!info) {
            continue;
        }

        printf("%s is set\n", info->description);
        if (info->toggles_buzzer) {
            toggle_buzzer(fd_buzzer, &buzzer_state);
        }
    }

    close(fd_buzzer);
    close(fd_ir);
    return EXIT_SUCCESS;
}

