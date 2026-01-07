#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QTransform>
#include <QScreen>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

class Painter : public QWidget
{
    Q_OBJECT
public:
    Painter(QWidget *parent = nullptr) : QWidget(parent), rat(0), ifpaint(0), count(0) {
        pixmap.load(":/icon/icon/FAN_close.png");
        pixmap = pixmap.scaled(pixwidth, pixheight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    }
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void setPart0();
    void setPart1();
    void setPart2();

private:
    QPixmap pixmap;
    int rat;
    int ifpaint;
    int count;
    int pixwidth = 400;
    int pixheight = 400;
};



#endif // PAINTER_H
