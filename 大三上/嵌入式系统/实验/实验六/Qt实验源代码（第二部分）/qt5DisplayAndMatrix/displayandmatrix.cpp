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


