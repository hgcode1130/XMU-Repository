#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>

class Circularprogressbar : public QWidget
{
    Q_OBJECT

public:
    Circularprogressbar(QWidget *parent = nullptr);
    //大圆
    void drawBiggestCircle(QPainter &painter, int radius);

    //小圆
    void drawLittleCircle(QPainter &painter, int radius);

    void drawColor(QPainter &painter, int radius);

    void paintEvent(QPaintEvent*) override;

    //重写按压事件
    void keyPressEvent(QKeyEvent *event) override;

    //重写释放事件
    void keyReleaseEvent(QKeyEvent *event) override;

    ~Circularprogressbar();

public slots:
    void decreaseColorProgress();

private:
    QTimer *myTimer;
    bool direction = false;
    int currentColorProgress = 0;
};
#endif // CIRCULARPROGRESSBAR_H
