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
    QUdpSocket *receiver;
private slots:
    void processPendingDatagram();
};
#endif // WIDGET_H
