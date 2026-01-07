#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QCursor cursor(Qt::BlankCursor);
    a.setOverrideCursor(cursor);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    w.resize(screenWidth, screenHeight);

    w.showFullScreen();
    return a.exec();
}
