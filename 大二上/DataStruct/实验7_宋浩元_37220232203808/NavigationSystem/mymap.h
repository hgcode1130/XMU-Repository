#ifndef MYMAP_H
#define MYMAP_H

#include <QWidget>

namespace Ui {
class MyMap;
}

class MyMap : public QWidget
{
    Q_OBJECT

public:
    explicit MyMap(QWidget *parent = nullptr);
    ~MyMap();

private:
    Ui::MyMap *ui;
};

#endif // MYMAP_H
