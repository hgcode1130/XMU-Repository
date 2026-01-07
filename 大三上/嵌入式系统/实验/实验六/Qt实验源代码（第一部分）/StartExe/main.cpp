#include "startexe.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartExe w;
    w.show();
    return a.exec();
}
