#include "photoview.h"
#include "ui_photoview.h"

photoView::photoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::photoView)
{
    ui->setupUi(this);
    animation = new QPropertyAnimation(ui->stackedWidget,"geometry");

    currentIndex = 0;
    ui->stackedWidget->installEventFilter(this);
    loadImages("/home/linux/Pictures");
    updateImage();
    qDebug()<<"photo init over";
}

void photoView::loadImages(const QString &folderPath)
{
    QDir dir(folderPath);
    QStringList filters;
    filters << "*.jpg" << "*.jpeg" << "*.png" << "*.bmp";
    QStringList fileList = dir.entryList(filters,QDir::Files);
    if(fileList.isEmpty()){
        qDebug()<<"fileList.isEmpty";
        checkUpdate = false;
        return;
    }
    for(const QString &file : fileList){
        QString fullPath = folderPath + QDir::separator() + file;
        qDebug()<<"fullPath"<<fullPath;
        imagePaths.append(fullPath);
    }
   checkUpdate = true;
}

// 更新图片显示
void photoView::updateImage()
{
    int i = ui->stackedWidget->count(); // 获取当前堆叠照片中的照片数量
    if(imagePaths.isEmpty()){ // 检查imagePaths是否为空
        qDebug()<<"imagePaths.isEmpty"; // 在控制台输出信息
        checkUpdate = false; // 将checkUpdate设置为false，表示没有更新发生
        return; // 返回，不执行后续代码
    }
    for(i;i>=0;i--){ // 从最后一个照片开始向前遍历
        QWidget *widget = ui->stackedWidget->widget(i); // 获取堆叠照片中的当前照片
        ui->stackedWidget->removeWidget(widget); // 从堆叠照片中移除当前照片
        widget->deleteLater(); // 将当前照片标记为删除
    }
    for(const QString &imagePath : imagePaths){ // 遍历imagePaths中的每个图片路径
        QLabel *label = new QLabel; // 创建一个新的QLabel对象
        label->setPixmap(QPixmap(imagePath)); // 将图片路径设置为标签的Pixmap
        label->setScaledContents(true); // 设置标签内容缩放，以适应标签大小
        ui->stackedWidget->addWidget(label); // 将标签添加到堆叠照片中
    }
    ui->stackedWidget->setCurrentIndex(currentIndex); // 设置堆叠照片的当前索引为currentIndex
    checkUpdate = true; // 将checkUpdate设置为true，表示更新已经完成
}


bool photoView::eventFilter(QObject *watched, QEvent *event)
{
    // 检查被监视的控件是否是堆叠照片
    if(watched == this->ui->stackedWidget){
        // 检查事件类型是否为鼠标移动
        if (event->type() == QEvent::MouseMove) {
            // 将事件强制转换为QMouseEvent
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            // 检查是否按下鼠标左键
            if (mouseEvent->buttons() & Qt::LeftButton) {
                // 计算鼠标位置的变化
                QPoint delta = mouseEvent->globalPos() - lastMousePos;
                // 检查水平移动距离是否大于垂直移动距离
                if (abs(delta.x()) > abs(delta.y())) {  // 如果水平方向的移动距离大于垂直方向
                    // 记录鼠标最后的位置
                    lastMousePos = mouseEvent->globalPos();
                    // 如果鼠标向右移动
                    if (delta.x() > 0) {
                        qDebug() << "鼠标向右移动了！"; // 在控制台输出信息
                        handleSwipeRight(); // 处理向右滑动
                    } else {
                        qDebug() << "鼠标向左移动了！"; // 在控制台输出信息
                        handleSwipeLeft(); // 处理向左滑动
                    }
                    return true; // 事件被处理，返回true
                }
            }
        } else if (event->type() == QEvent::MouseButtonPress) {
            // 将事件强制转换为QMouseEvent
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            // 检查是否按下鼠标左键
            if (mouseEvent->button() == Qt::LeftButton) {
                // 记录鼠标按下的位置
                lastMousePos = mouseEvent->globalPos();
            }
        }
    }
    // 如果事件未被处理，调用父类的eventFilter方法
    return QWidget::eventFilter(watched,event);
}

void photoView::handleSwipeLeft()
{
    // 向左滑动，切换到下一张图片
    int nextIndex = (currentIndex + 1) % imagePaths.size();
    animateImageSwitch(nextIndex);
}

void photoView::handleSwipeRight()
{
    // 向右滑动，切换到上一张图片
    int preIndex = (currentIndex - 1 + imagePaths.size()) % imagePaths.size();
    animateImageSwitch(preIndex);
}

bool photoView::getCheckUpdate()
{
    return checkUpdate;
}

void photoView::animateImageSwitch( int targetIndex)
{
    if (targetIndex == currentIndex) {
        return; // 如果目标索引与当前索引相同，不做任何处理
    }

    QLabel *currentLabel = qobject_cast<QLabel *>(ui->stackedWidget->currentWidget());
    QLabel *nextLabel = qobject_cast<QLabel *>(ui->stackedWidget->widget(targetIndex));

    if (!currentLabel || !nextLabel) {
        return; // 确保当前和目标标签都存在
    }

    // 初始化动画
    QPropertyAnimation *fadeOutAnimation = new QPropertyAnimation(currentLabel, "opacity");
    fadeOutAnimation->setDuration(100);
    fadeOutAnimation->setStartValue(1.0);
    fadeOutAnimation->setEndValue(0.0);

    QPropertyAnimation *fadeInAnimation = new QPropertyAnimation(nextLabel, "opacity");
    fadeInAnimation->setDuration(100);
    fadeInAnimation->setStartValue(0.0);
    fadeInAnimation->setEndValue(1.0);

    QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup();
    animationGroup->addAnimation(fadeOutAnimation);
    animationGroup->addAnimation(fadeInAnimation);

    // Transition to the new image
    connect(animationGroup, &QParallelAnimationGroup::finished, this, [this, targetIndex]() {
        currentIndex = targetIndex; // 更新当前索引
        updateImage(); // 更新 QStackedWidget 显示图片
    });

    animationGroup->start();
}

photoView::~photoView()
{
    delete ui;
}

void photoView::on_back_clicked()
{
    emit open();
}
