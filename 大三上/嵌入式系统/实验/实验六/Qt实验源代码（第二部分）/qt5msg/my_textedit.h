#ifndef MY_TEXTEDIT_H
#define MY_TEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QDebug>
class My_textEdit : public QTextEdit
{
    Q_OBJECT
public:
    My_textEdit(QWidget* parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void sendtext_show(QString data);
};

#endif // MY_TEXTEDIT_H
