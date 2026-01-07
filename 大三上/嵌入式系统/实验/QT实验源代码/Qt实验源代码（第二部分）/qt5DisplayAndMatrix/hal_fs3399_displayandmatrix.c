#include "hal_fs3399_displayandmatrix.h"  // 包含硬件抽象层的头文件

int fd = 0;  // 文件描述符，用于设备文件的操作
char buf[10] = {0};  // 缓冲区，用于存储数据或命令

// 初始化设备
int dis_mat_init()
{
    fd = open("/dev/zlg72xx", O_RDWR);  // 打开设备文件，允许读写操作
    if (fd < 0) {
        perror("open");  // 如果打开失败，打印错误信息
    }
    return 0;  // 返回0表示函数结束
}

// 运行设备并获取按键值
int Run()
{
    int key = 0;  // 存储按键值
    char value;  // 存储转换后的字符
    ioctl(fd, SET_VAL, buf);  // 发送设置值的命令
    ioctl(fd, GET_KEY, &key);  // 获取按键值的命令

    // 根据按键值输出对应字符，并赋值给变量
    switch(key)
    {
        case 28 : printf("put is '1'\n"); value = '1'; break;
        case 27 : printf("put is '2'\n"); value = '2'; break;
        case 26 : printf("put is '3'\n"); value = '3'; break;
        case 25 : printf("put is 'A'\n"); value = 'A'; break;
        case 20 : printf("put is '4'\n"); value = '4'; break;
        case 19 : printf("put is '5'\n"); value = '5'; break;
        case 18 : printf("put is '6'\n"); value = '6'; break;
        case 17 : printf("put is 'B'\n"); value = 'B'; break;
        case 12 : printf("put is '7'\n"); value = '7'; break;
        case 11 : printf("put is '8'\n"); value = '8'; break;
        case 10 : printf("put is '9'\n"); value = '9'; break;
        case 9  : printf("put is 'C'\n"); value = 'C'; break;
        case 4  : printf("put is '*'\n"); value = '*'; break;
        case 3  : printf("put is '0'\n"); value = '0'; break;
        case 2  : printf("put is '#'\n"); value = '#'; break;
        case 1  : printf("put is 'D'\n"); value = 'D'; break;
        default: value = 0x00; break;
    }

    puts("==========================");
    // 将缓冲区内容向左移动，并将新的值添加到末尾
    for(int i = 0; i < 7; i++)
    {
        buf[i] = buf[i+1];
    }
    buf[7] = value;
    ioctl(fd, SET_VAL, buf);  // 更新设备的显示或矩阵状态
    return value;  // 返回处理后的值
}

// 更新缓冲区
void turn_new_buf(char value){
    for(int i = 0; i < 7; i++)
    {
        buf[i] = buf[i+1];  // 向左移动缓冲区内容
    }
    buf[7] = value;  // 将新值放在缓冲区末尾
    ioctl(fd, SET_VAL, buf);  // 发送更新命令
}

// 关闭设备
void close_dis()
{
    memset(buf, 0, sizeof(buf));  // 清空缓冲区
    close(fd);  // 关闭文件描述符
    system("killall -9 qt5DisplayAndMatrix");  // 强制关闭相关程序
}
