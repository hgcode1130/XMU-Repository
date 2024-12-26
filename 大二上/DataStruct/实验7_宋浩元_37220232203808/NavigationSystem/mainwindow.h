#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scribblearea.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onTaskBoxContextMenuEvent();
    ScribbleArea * s;
    void clearAllData();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
