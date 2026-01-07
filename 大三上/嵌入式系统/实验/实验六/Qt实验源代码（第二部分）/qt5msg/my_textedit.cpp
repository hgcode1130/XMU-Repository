#include "my_textedit.h"
#include <QDebug>
#include <QTouchEvent>
My_textEdit::My_textEdit(QWidget *parent) :
    QTextEdit(parent)
{

}

void My_textEdit::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    QString text = this->toPlainText();
    emit sendtext_show(text);
    setText(text); // 将输入的字符设置到密码框中
}
