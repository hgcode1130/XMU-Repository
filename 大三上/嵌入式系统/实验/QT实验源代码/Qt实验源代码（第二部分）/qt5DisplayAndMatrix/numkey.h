#ifndef NUMKEY_H
#define NUMKEY_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
class numKey : public QWidget
{
    Q_OBJECT
public:
    explicit numKey(QWidget *parent = nullptr);
    QPushButton* getButton(int index);

signals:
private:
    QPushButton* buttons[10];

};




#endif // NUMKEY_H
