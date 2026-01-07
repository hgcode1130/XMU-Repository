#include "my_lineedit.h"
#include <QDebug>
#include <QTouchEvent>
My_lineEdit::My_lineEdit(QWidget *parent) :
    QLineEdit(parent)
{

}
bool My_lineEdit::event(QEvent* event)
{
    if (event->type() == QEvent::TouchBegin || event->type() == QEvent::MouseButtonPress) {
        bool isLeftButton = false;

        if (event->type() == QEvent::TouchBegin) {
            QTouchEvent* touchEvent = static_cast<QTouchEvent*>(event);
            if (!touchEvent->touchPoints().isEmpty()) {
                isLeftButton = true;
            }
        } else if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                isLeftButton = true;
            }
        }

        if (isLeftButton) {
            QString text = this->text();
            emit send_show(text);
            setText(text); // 将输入的字符设置到密码框中
        }
    }

    return QLineEdit::event(event);
}
