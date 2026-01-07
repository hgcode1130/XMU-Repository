#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    //通信对象
    QTcpServer *tcpServer;
private slots:
    void sendMessage();
};
#endif // WIDGET_H
