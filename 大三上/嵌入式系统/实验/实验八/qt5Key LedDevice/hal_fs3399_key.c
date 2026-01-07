#include "hal_fs3399_key.h" 

int fd_key = 0; // 定义文件描述符，用于键盘设备

// 初始化键盘设备
void key_init()
{
    fd_key = open(KEYS_PATH, O_RDWR); // 以读写方式打开键盘设备文件
    if (fd_key < 0) // 如果打开失败
        perror("open farsight_keys failed"); // 输出错误信息
}

// 获取被按下的按键状态
int get_keys_clicked()
{
    int buf[2] = { 0 }; // 定义一个整数数组，用于存储读取的数据
    int err = 0; // 定义错误码
    err = read(fd_key, buf, sizeof(buf)); // 从键盘设备文件读取数据
    if (err > 0) // 如果读取成功
    {
        if (buf[0] == 1) // 如果第一个值是1
        {
            if (buf[1] == 0) // 如果第二个值是0
                return KEY1_ON; // 返回按键1被按下
            else
                return KEY1_OFF; // 返回按键1被释放
        }
        else if (buf[0] == 2) // 如果第一个值是2
        {
            if (buf[1] == 0) // 如果第二个值是0
                return KEY2_ON; // 返回按键2被按下
            else
                return KEY2_OFF; // 返回按键2被释放
        }
    }
    else
        return -1; // 如果读取失败，返回-1
}

// 关闭键盘设备
int key_close()
{
    return close(fd_key); // 关闭键盘设备文件描述符
}

int fd_led = 0; // 定义文件描述符，用于LED设备

// 初始化LED设备
int led_init()
{
    fd_led = 0; // 初始化文件描述符
    fd_led = open(LED_PATH, O_RDWR); // 以读写方式打开LED设备文件
    if (fd_led < 0) // 如果打开失败
    {
        perror("open led failed"); // 输出错误信息
        return -1; // 返回-1
    }
    ioctl(fd_led, LED1_OFF); // 关闭LED1
    ioctl(fd_led, LED2_OFF); // 关闭LED2
    ioctl(fd_led, LED3_OFF); // 关闭LED3
    return 0; // 返回0
}

// 打开指定编号的LED
int led_on(int nr)
{
    switch (nr) // 根据编号
    {
    case LED1: // 如果是LED1
        ioctl(fd_led, LED1_ON); // 打开LED1
        break;
    case LED2: // 如果是LED2
        ioctl(fd_led, LED2_ON); // 打开LED2
        break;
    case LED3: // 如果是LED3
        ioctl(fd_led, LED3_ON); // 打开LED3
        break;
    default: // 如果编号不正确
        break;
    }
    return 0; // 返回0
}

// 关闭指定编号的LED
int led_off(int nr)
{
    int fd_led = open(LED_PATH, O_RDWR); // 以读写方式打开LED设备文件
    if (fd_led < 0) // 如果打开失败
    {
        perror("open failed"); // 输出错误信息
        return -1; // 返回-1
    }
    switch (nr) // 根据编号
    {
    case LED1: // 如果是LED1
        ioctl(fd_led, LED1_OFF); // 关闭LED1
        break;
    case LED2: // 如果是LED2
        ioctl(fd_led, LED2_OFF); // 关闭LED2
        break;
    case LED3: // 如果是LED3
        ioctl(fd_led, LED3_OFF); // 关闭LED3
        break;
    default: // 如果编号不正确
        break;
    }
    return 0; // 返回0
}

// 关闭LED设备
int led_close()
{
    return close(fd_led); // 关闭LED设备文件描述符
}