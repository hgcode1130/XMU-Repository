#include "circularprogressbar.h"

Circularprogressbar::Circularprogressbar(QWidget *parent)
    : QWidget(parent)
{
    myTimer = new QTimer(this);
    connect(myTimer, &QTimer::timeout, this, &Circularprogressbar::decreaseColorProgress);
}

void Circularprogressbar::drawBiggestCircle(QPainter &painter, int radius) {
    painter.save();
    QPainterPath path;
    // 绘制外圈大圆
    path.addEllipse(-radius, -radius, 2 * radius, 2 * radius);
    painter.setBrush(QColor(54, 54, 54)); // 暗灰色
    painter.drawPath(path);
    painter.restore();
}

void Circularprogressbar::drawLittleCircle(QPainter &painter, int radius) {
    painter.save();
    QPainterPath path;
    // 绘制内圈小圆
    int reducedRadius = radius - 50; // 内圈圆半径减少
    path.addEllipse(-reducedRadius, -reducedRadius, 2 * reducedRadius, 2 * reducedRadius);
    QColor ringColor = palette().color(QPalette::Window); // 获取控件的背景颜色
    painter.setBrush(ringColor);
    painter.drawPath(path);
    painter.restore();
}

void Circularprogressbar::drawColor(QPainter &painter, int radius)
{
    QRect rect(-radius,-radius,2*radius,2*radius);
    QConicalGradient Conical(0, 0, 0);

    // 在0点处设置与0.05点相似的颜色
    Conical.setColorAt(0, QColor(128, 0, 255)); // 深紫色
    Conical.setColorAt(0.05, QColor(128, 0, 255)); // 深紫色

    // 其他颜色保持不变
    Conical.setColorAt(0.2, QColor(255, 0, 0));     // 红色
    Conical.setColorAt(0.4, QColor(255, 165, 0));   // 橙色
    Conical.setColorAt(0.6, QColor(0, 128, 0));     // 浅绿色
    Conical.setColorAt(0.8, QColor(0, 255, 255));   // 青色

    // 在接近1的位置复制0点的颜色以完成闭环
    Conical.setColorAt(0.95, QColor(0, 0, 255));    // 蓝色
    Conical.setColorAt(1.0, QColor(128, 0, 255));   // 深紫色


    painter.setBrush(Conical);
    painter.drawPie(rect, -180 * 16, -(currentColorProgress * 16));
}


void Circularprogressbar::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);//忽略event
    QPainter painter(this);
    int width = this->width();
    int height = this->height();
    painter.translate(width / 2, height / 2); // 将画布中心移动到窗口中心
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);

    int outerRadius = std::min(width, height) / 2; // 外圈半径
    int innerRadius = outerRadius - 50; // 内圈半径

    // 绘制外圈大圆
    drawBiggestCircle(painter, outerRadius);

    drawColor(painter, outerRadius);

    // 绘制内圈小圆
    drawLittleCircle(painter, innerRadius);
}

void Circularprogressbar::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        myTimer->start();
        direction = true;
        // 更新控件的颜色
        update();
    }
}

void Circularprogressbar::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space)
    {
        direction = false;
        // 更新控件的颜色
        update();
    }
}

void Circularprogressbar::decreaseColorProgress()
{
    if(direction){
        // 增加颜色进度
        currentColorProgress += 3.6;
        if(currentColorProgress > 360){
            currentColorProgress = 360;
        }
    }else{
        // 减少颜色进度
        currentColorProgress -= 1;
        if(currentColorProgress < 0){
            currentColorProgress = 0;
            myTimer->stop();
        }
    }
    // 更新控件的颜色
    update();
}

Circularprogressbar::~Circularprogressbar()
{
}

