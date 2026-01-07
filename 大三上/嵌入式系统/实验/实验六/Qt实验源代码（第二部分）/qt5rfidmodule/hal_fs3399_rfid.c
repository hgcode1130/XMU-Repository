
#include "hal_fs3399_rfid.h"  // 包含 RFID 设备操作的头文件

// 定义不同类型 RFID 设备的文件描述符
int fd_hf = 0;   // 高频（HF）
int fd_lf = 0;   // 低频（LF）
int fd_nfc = 0;  // 近场通信（NFC）
int fd_2_4G = 0; // 2.4G，暂未使用
int fd_915m = 0; // 915M，暂未使用
char* rfid_card = NULL;  // 初始化指针为 NULL
// 初始化 RFID 设备
int init_rfid(int rfid)
{
    // 尝试分配内存
    rfid_card = (char*)malloc(12);
    if (rfid_card == NULL) {
        perror("Failed to allocate memory for rfid_card");
        return -1;
    }
    switch (rfid) {
    case F13_56M:
        // 初始化高频设备
        fd_hf = open("/dev/rfid_module0", O_RDWR);  // 打开高频设备文件
        if (fd_hf < 0) {
            perror("open rfid_module0");  // 打开失败，输出错误信息
            return -1;
        }
        break;
    case F125K:
        // 初始化低频设备
        fd_lf = open("/dev/rfid_module1", O_RDWR);  // 打开低频设备文件
        if (fd_lf < 0) {
            perror("open rfid_module1");  // 打开失败，输出错误信息
            return -1;
        }
        break;
    case F915M:
        // 初始化 915M 设备
        fd_915m = open("/dev/rfid_module3", O_RDWR);  // 打开 NFC 设备文件
        if (fd_nfc < 0) {
            perror("open rfid_module3");  // 打开失败，输出错误信息
            return -1;
        }
        break;
    case FNFC:
        // 初始化 NFC 设备
        fd_nfc = open("/dev/rfid_module2", O_RDWR);  // 打开 NFC 设备文件
        if (fd_nfc < 0) {
            perror("open rfid_module2");  // 打开失败，输出错误信息
            return -1;
        }
        break;
    case F2_4G:
        // 初始化 NFC 设备
        fd_2_4G = open("/dev/rfid_module4", O_RDWR);  // 打开 NFC 设备文件
        if (fd_2_4G < 0) {
            perror("open rfid_module4");  // 打开失败，输出错误信息
            return -1;
        }
        break;
    }
    return 0;  // 初始化成功
}

// 读取 HF 设备的数据
char* read_hf()
{
    char card_data[32] = {0};  // 确保缓冲区大小与读取的数据匹配
    usleep(100);
    int nbyte = read(fd_hf, card_data, 4);  // 确保读取的数据长度与缓冲区大小匹配
    if (nbyte < 0) {
        perror("read rfid_hf");
        free(rfid_card);  // 如果读取失败，释放内存
        return NULL;
    }
    printf("\nrfid_card %s\n", rfid_card);
    sprintf(rfid_card, "%02x %02x %02x %02x", card_data[0], card_data[1], card_data[2], card_data[3]);
    printf("\nrfid_card %s\n", rfid_card);
    return rfid_card;
}

// 读取 LF 设备的数据
char* read_lf()
{
    char card_data[32] = {0};  // 确保缓冲区大小与读取的数据匹配
    int nbyte = read(fd_lf, card_data, 5);  // 确保读取的数据长度与缓冲区大小匹配
    if (nbyte < 0) {
        perror("read rfid_lf");
        free(rfid_card);  // 如果读取失败，释放内存
        return NULL;
    }
    sprintf(rfid_card, "%02x %02x %02x %02x %02x", card_data[0], card_data[1], card_data[2], card_data[3],card_data[4]);
    printf("\nrfid_card %s\n", rfid_card);
    return rfid_card;
}

//读取NFC的数据
char* read_nfc()
{
    char card_data[32] = {0};
    if (rfid_card == NULL)
    {
      perror("Failed to allocate memory for rfid_card");
      return NULL;
    }

    int nbyte = read(fd_nfc,card_data,4);
    if(nbyte < 0)
    {
      perror("read rfid_nfc");
      free(rfid_card);  // 如果读取失败，释放内存并返回
      return NULL;
    }

    sprintf(rfid_card,"%02x %02x %02x %02x",card_data[0],card_data[1],card_data[2],card_data[3]);
    return rfid_card;
}


// 关闭 RFID 设备
int close_rfid()
{
    if(fd_hf){
        close(fd_hf);  // 关闭 HF 设备
        fd_hf = 0;
        printf("fd_hf = %d\n",fd_hf);
        return fd_hf;
    }
    if(fd_lf){
        close(fd_lf);  // 关闭 LF 设备
        fd_lf = 0;
        printf("fd_lf = %d\n",fd_lf);
        return fd_lf;
    }
    if(fd_nfc){
        close(fd_nfc);  // 关闭 NFC 设备
        fd_nfc = 0;
        printf("fd_nfc = %d\n",fd_nfc);
        return fd_nfc;
    }
    if(fd_2_4G){
        close(fd_2_4G);  // 关闭 2_4G 设备
        fd_2_4G = 0;
        printf("fd_2_4G = %d\n",fd_2_4G);
        return fd_2_4G;
    }
    if(fd_915m){
        close(fd_915m);  // 关闭 915m 设备
        fd_915m = 0;
        printf("fd_915m = %d\n",fd_915m);
        return fd_915m;
    }
    return -1;
}

char* read_2_4G()
{
    char card_data[32] = {0};  // 缓冲区，用于存储读取的数据
    if (rfid_card == NULL) {
        perror("Failed to allocate memory for rfid_card");  // 内存分配失败，输出错误信息
        return NULL;
    }
    int nbyte = read(fd_2_4G, card_data, 4);  // 读取数据
    if(nbyte < 0) {
        perror("read rfid_hf");  // 读取失败，输出错误信息
        free(rfid_card);  // 释放内存
        return NULL;
    }
    sprintf(rfid_card, "%02x %02x %02x %02x", card_data[0], card_data[1], card_data[2], card_data[3]);  // 格式化读取结果
    return rfid_card;  // 返回格式化后的字符串
}

char* read_915m()
{
    char card_data[32] = {0};  // 缓冲区，用于存储读取的数据
    if (rfid_card == NULL) {
        perror("Failed to allocate memory for rfid_card");  // 内存分配失败，输出错误信息
        return NULL;
    }
    int nbyte = read(fd_915m, card_data, 4);  // 读取数据
    if(nbyte < 0) {
        perror("read rfid_hf");  // 读取失败，输出错误信息
        free(rfid_card);  // 释放内存
        return NULL;
    }
    sprintf(rfid_card, "%02x %02x %02x %02x", card_data[0], card_data[1], card_data[2], card_data[3]);  // 格式化读取结果
    return rfid_card;  // 返回格式化后的字符串
}
