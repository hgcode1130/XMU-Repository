#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define KEY_DEVICE_PATH "/dev/farsight_keys"
#define LED_DEVICE_PATH "/dev/leds_ctl"

#define LED1_ON  _IO('G', 1)
#define LED1_OFF _IO('G', 2)
#define LED2_ON  _IO('G', 3)
#define LED2_OFF _IO('G', 4)

static volatile sig_atomic_t keep_running = 1;
static int key_fd = -1;
static int led_fd = -1;

static const unsigned int led_on_cmd[2] = {LED1_ON, LED2_ON};
static const unsigned int led_off_cmd[2] = {LED1_OFF, LED2_OFF};

static void close_devices(void)
{
    if (key_fd >= 0) {
        close(key_fd);
        key_fd = -1;
    }

    if (led_fd >= 0) {
        close(led_fd);
        led_fd = -1;
    }
}

static void signal_handler(int signo)
{
    (void)signo;
    keep_running = 0;
}

static int set_led_state(int index, int state)
{
    unsigned int cmd = state ? led_on_cmd[index] : led_off_cmd[index];
    if (ioctl(led_fd, cmd) == -1) {
        perror("ioctl 控制 LED 失败");
        return -1;
    }
    return 0;
}

int main(void)
{
    int led_state[2] = {0, 0};

    if (signal(SIGINT, signal_handler) == SIG_ERR ||
        signal(SIGTERM, signal_handler) == SIG_ERR) {
        perror("注册信号处理失败");
        return EXIT_FAILURE;
    }

    key_fd = open(KEY_DEVICE_PATH, O_RDONLY);
    if (key_fd < 0) {
        perror("打开按键设备失败");
        return EXIT_FAILURE;
    }

    led_fd = open(LED_DEVICE_PATH, O_RDWR);
    if (led_fd < 0) {
        perror("打开 LED 设备失败");
        close_devices();
        return EXIT_FAILURE;
    }

    // 确保 LED 初始为熄灭状态，避免异常状态残留
    for (int i = 0; i < 2; ++i) {
        if (set_led_state(i, 0) != 0) {
            close_devices();
            return EXIT_FAILURE;
        }
    }

    printf("按键控制程序启动，按 KEY1/KEY2 可以切换 LED1/LED2 亮灭，Ctrl+C 退出。\n");

    while (keep_running) {
        int buf[2] = {0, 0};
        ssize_t ret = read(key_fd, buf, sizeof(buf));

        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("读取按键事件失败");
            break;
        }

        // buf[0] 表示按键编号，buf[1] 表示电平（0=按下，1=松开）
        if (ret == 0) {
            continue;
        }

        int key_id = buf[0];
        int level = buf[1];

        if (key_id < 1 || key_id > 2) {
            fprintf(stderr, "收到未知按键编号: %d\n", key_id);
            continue;
        }

        if (level != 0) {
            // 只在按下瞬间切换 LED，释放事件忽略
            continue;
        }

        int index = key_id - 1;
        led_state[index] = !led_state[index];

        if (set_led_state(index, led_state[index]) != 0) {
            break;
        }

        printf("KEY%d 按下，LED%d 已切换为%s。\n",
               key_id, key_id, led_state[index] ? "点亮" : "熄灭");
    }

    printf("程序退出，关闭设备。\n");
    close_devices();
    return EXIT_SUCCESS;
}

