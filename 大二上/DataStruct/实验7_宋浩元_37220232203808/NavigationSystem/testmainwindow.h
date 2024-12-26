#ifndef TESTMAINWINDOW_H
#define TESTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class TestMainWindow;
}

class TestMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestMainWindow(QWidget *parent = nullptr);
    ~TestMainWindow();

private:
    Ui::TestMainWindow *ui;
};

#endif // TESTMAINWINDOW_H
