#include "numkey.h"  // 包含 numKey 类的声明

// 构造函数实现，用于初始化 numKey 类
numKey::numKey(QWidget *parent) : QWidget(parent)
{
    // 创建并初始化每个数字按钮
    for (int i = 9; i >= 0; i--) {
        buttons[i] = new QPushButton(QString::number(i), this);  // 创建按钮，显示数字 i
        // 设置按钮样式
        buttons[i]->setStyleSheet("QPushButton {"
                                  "background-color: #444444;"  // 背景色
                                  "border: none;"  // 无边框
                                  "color: white;"  // 文字颜色
                                  "padding: 10px;"  // 填充
                                  "border-radius: 5px;"  // 边角圆滑
                                  "outline: none;"  // 无轮廓
                                  "}"
                                  "QPushButton:hover {"
                                  "background-color: #555555;"  // 鼠标悬停时的背景色
                                  "outline: none;"  // 无轮廓
                                  "}"
                                  "QPushButton:pressed {"
                                  "background-color: #666666;"  // 鼠标按下时的背景色
                                  "outline: none;"  // 无轮廓
                                  "}");
        buttons[i]->setFixedHeight(80);
        // 设置按钮字体
        QFont buttonsfont("Noto Sans CJK SC Regular",20);
        buttons[i]->setFont(buttonsfont);
    }
}

// getButton 方法实现，用于获取指定索引的按钮
QPushButton* numKey::getButton(int index) {
    if (index >= 0 && index < 10) {  // 检查索引有效性
        return buttons[index];  // 返回对应的按钮
    }
    return nullptr;  // 索引无效时返回空指针
}
