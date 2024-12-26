#include "start.h"
#include "mymap.h"
#include <QApplication>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QChar>
#include <QLineEdit>
#include <QVector>
#include "mainwindow.h"

Start *start;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    start = new Start();
    return app.exec();
}
