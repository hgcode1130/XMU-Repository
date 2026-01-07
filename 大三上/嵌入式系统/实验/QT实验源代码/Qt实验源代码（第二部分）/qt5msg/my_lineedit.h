#ifndef MY_LINEEDIT_H
#define MY_LINEEDIT_H
#include <QWidget>
#include <QLineEdit>


class My_lineEdit : public QLineEdit
{
    Q_OBJECT
public:
    My_lineEdit(QWidget* parent = nullptr);

protected:
    bool event(QEvent* event) override;
signals:
    void send_show(QString data);
};

#endif // MY_LINEEDIT_H

