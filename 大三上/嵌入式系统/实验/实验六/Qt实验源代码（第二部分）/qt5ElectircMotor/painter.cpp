#include "painter.h"  // 包含 Painter 类的定义

// 处理绘制事件
void Painter::paintEvent(QPaintEvent *) {
    QPainter painter(this);  // 创建 QPainter 对象用于绘图
    QPainterPath path;  // 创建 QPainterPath 对象用于定义复杂形状
    path.addEllipse(0, 0, width(), height());  // 在路径中添加一个椭圆形，占据整个控件
    painter.setClipPath(path);  // 设置绘图区域，仅在椭圆形内绘图

    // 根据旋转方向更新旋转角度
    if (ifpaint == 1) {
        rat = (rat + count) % 360; // 正转
    } else if(ifpaint == -1) {
        rat = (rat - count) % 360; // 反转
    }

    painter.setRenderHint(QPainter::Antialiasing);  // 启用抗锯齿
    painter.translate(width() / 2, height() / 2);  // 将绘图原点移动到控件中心
    painter.rotate(rat);  // 旋转画布
    painter.drawPixmap(-pixmap.width() / 2, -pixmap.height() / 2, pixmap);  // 绘制图片
}

// 控件尺寸改变时调整控件大小以保持正方形
void Painter::resizeEvent(QResizeEvent *event){
    if (width() != height()) {
        int size = qMin(width(), height());  // 取宽和高的最小值
        setFixedSize(size, size);  // 设置固定大小
    }
}

// 控制图片停止旋转
void Painter::setPart0(){
    ifpaint = 0;  // 停止旋转标志
    count = 0;  // 旋转速度为 0
    pixmap.load(":/icon/icon/FAN_close.png");  // 加载停止时的图片
    pixmap = pixmap.scaled(pixwidth, pixheight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);  // 调整图片大小
}

// 控制图片正转
void Painter::setPart1(){
    ifpaint = 1;  // 正转标志
    count = 30;  // 设置旋转速度
    pixmap.load(":/icon/icon/FAN.png");  // 加载旋转的图片
    pixmap = pixmap.scaled(pixwidth, pixheight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);  // 调整图片大小
}

// 控制图片反转
void Painter::setPart2(){
    ifpaint = -1;  // 反转标志
    count = 30;  // 设置旋转速度
    pixmap.load(":/icon/icon/FAN.png");  // 重新加载同一张旋转的图片
    pixmap = pixmap.scaled(pixwidth, pixheight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);  // 调整图片大小
}
