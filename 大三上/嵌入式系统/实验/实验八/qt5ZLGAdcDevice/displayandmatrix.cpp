#include "displayandmatrix.h"  // 包含相关头文件

// 基类 DisplayandMatrix 的构造函数
DisplayandMatrix::DisplayandMatrix()
{
    dis_mat_init();  // 调用初始化函数，用于设备的初始配置
}

// DisplayandMatri6818 类的实现
char DisplayandMatrix::getValue()
{
    char value = Run();  // 同样调用 Run 函数获取值
    return value;  // 返回值
}

void DisplayandMatrix::trunNewBuf(char value)
{
    turn_new_buf(value);  // 更新缓冲区
}

void DisplayandMatrix::close()
{
    close_dis();  // 关闭设备
}



void DisplayandMatrix::showValue(int value)
{
    // Ensure range 0-9999 (since we have 4 digits logic)
    // But adc is 0-1023 (4 digits)
    char data[8] = {0}; // Initialize all to 0
    
    // Logic: thousands, hundreds, tens, units
    int thousands = value / 1000;
    int hundreds = (value % 1000) / 100;
    int tens = (value % 100) / 10;
    int units = value % 10;
    
    // Map to positions (Right aligned: 7,6,5,4?)
    // Let's assume indices 4,5,6,7 correspond to the rightmost 4 digits
    // The HAL code case 3: value='0'. So we need to store chars '0'..'9'.
    
    data[4] = thousands + '0';
    data[5] = hundreds + '0';
    data[6] = tens + '0';
    data[7] = units + '0';
    
    // Fill others with '0' or space (0x00 turns off?)
    // Default switch in HAL says 0x00. Let's keep them 0.
    
    set_display_buffer(data);
}
