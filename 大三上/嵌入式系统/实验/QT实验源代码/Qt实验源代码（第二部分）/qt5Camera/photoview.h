#ifndef PHOTOVIEW_H
#define PHOTOVIEW_H

#include <QWidget>
#include <QFile>
#include <QString>
#include <QPainter>
#include <QDir>
#include <QDebug>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QVector>
#include <QStringList>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStackedWidget>
#include <QLabel>

namespace Ui {
class photoView;
}

class photoView : public QWidget
{
    Q_OBJECT

public:
    explicit photoView(QWidget *parent = 0);
    void loadImages(const QString &folderPath);
    void updateImage();
    bool eventFilter(QObject*watched,QEvent*event) override;
    void handleSwipeLeft();
    void handleSwipeRight();
    bool getCheckUpdate();

    void animateImageSwitch(int targetIndex);
    ~photoView();


private slots:
    void on_back_clicked();

signals:
    void open();

private:
    Ui::photoView *ui;
    QVector<QString> imagePaths;
    QPoint lastMousePos;
    bool checkUpdate = false;
    int currentIndex = 0;
    QPropertyAnimation *animation;
};

#endif // PHOTOVIEW_H
