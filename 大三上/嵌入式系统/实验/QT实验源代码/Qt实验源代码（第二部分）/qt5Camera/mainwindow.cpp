#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    photoview = new photoView();
    // 初始化OpenCV摄像头
    cap = cv::VideoCapture(0);
    if (!cap.isOpened()) {
    // 摄像头无法打开
       return;
    }
    ui->Preview->installEventFilter(this);
    // 设置定时器更新界面
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    timer->start(10); // 更新频率（毫秒）

    loadImage();
    //connect(ui->Preview,&QLabel::linkActivated,this,&MainWindow::openPhotoView);
    connect(photoview,&photoView::open,this,&MainWindow::openMainWindow);
}

void MainWindow::loadImage()
{
    QString basePictrueDir = "/home/linux/Pictures"; // 设置图片的基础目录路径
    QDir dir(basePictrueDir); // 创建一个指向基础目录的QDir对象
    if(!dir.exists()){ // 检查目录是否存在
        qDebug()<<"Directory dose not exist"; // 如果目录不存在，输出错误信息
        return; // 返回，不执行后续代码
    }
    QStringList files = dir.entryList(QStringList() << "*.png" << "*.jpg" << "*.jpeg", QDir::Files); // 获取目录下所有.png、.jpg和.jpeg格式的文件列表
    if(files.isEmpty()){ // 检查文件列表是否为空
        qDebug()<<"No images found in directory"; // 如果没有找到图片，输出错误信息
        return; // 返回，不执行后续代码
    }
    QString firstFile = files.last(); // 获取文件列表中的最后一个文件，即最新的图片
    QString filePath = QString("%1/%2").arg(basePictrueDir).arg(firstFile); // 构建完整的文件路径
    cv::Mat cvImage = cv::imread(filePath.toStdString()); // 使用OpenCV读取图片文件
    if(cvImage.empty()){ // 检查图片是否成功加载
        qDebug()<<"Failed to load image"; // 如果加载失败，输出错误信息
        return; // 返回，不执行后续代码
    }
    cv::Mat rgbImage(cvImage.rows, cvImage.cols,cvImage.type(), cv::Scalar(0,0,0)); // 创建一个与cvImage大小相同的全黑色图像
    for(int y = 0;y < cvImage.rows;++y){ // 遍历图像的每一行
        for(int x= 0;x < cvImage.cols ; ++x){ // 遍历图像的每一列
            cv::Vec3b &bgr = cvImage.at<cv::Vec3b>(y,x); // 获取BGR格式的像素值
            rgbImage.at<cv::Vec3b>(y,x) = cv ::Vec3b(bgr[2],bgr[1],bgr[0]); // 将BGR值转换为RGB格式
        }
    }
    QImage image(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step, QImage::Format_RGB888); // 使用OpenCV图像数据创建QImage对象
    image.save(filePath); // 将转换后的QImage保存回文件
    QPixmap p = QPixmap::fromImage(image); // 将QImage转换为QPixmap
    ui->Preview->setScaledContents(true); // 设置预览框的内容缩放模式
    ui->Preview->setPixmap(p); // 将转换后的QPixmap设置到预览框中显示
}


void MainWindow::recvImage()
{
    // 检查传入的图像帧是否为空
    if (frame.empty()) {
        return; // 如果为空，直接返回，不执行后续操作
    }
    // 水平翻转图像帧
    flip(frame, frame, 1);
    // 创建一个与frame大小相同的全黑色图像
    cv::Mat rgbImage(frame.rows, frame.cols, frame.type(), cv::Scalar(0,0,0));
    // 遍历图像的每一行和每一列
    for(int y = 0; y < frame.rows; ++y){
        for(int x = 0; x < frame.cols; ++x){
            // 获取BGR格式的像素值
            cv::Vec3b &bgr = frame.at<cv::Vec3b>(y, x);
            // 将BGR值转换为RGB格式
            rgbImage.at<cv::Vec3b>(y, x) = cv::Vec3b(bgr[2], bgr[1], bgr[0]);
        }
    }
    // 使用OpenCV图像数据创建QImage对象
    QImage image(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step, QImage::Format_RGB888);
    // 将QImage转换为QPixmap
    QPixmap p = QPixmap::fromImage(image);
    // 设置视频预览区域的缩放模式为内容缩放
    ui->Video->setScaledContents(true);
    // 将转换后的QPixmap设置到视频预览区域中显示
    ui->Video->setPixmap(p);
}


bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->ui->Preview){
        if(event->type() == QEvent::MouseButtonPress){
            QMouseEvent *mouseevent = static_cast<QMouseEvent*>(event);
            if(mouseevent->button() == Qt::LeftButton){
                openPhotoView();
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}

MainWindow::~MainWindow()
{
    delete ui;
    timer->stop();
    cap.release();
}

void MainWindow::updateFrame()
{
       cv::Mat frame;
       if (cap.read(frame)) {
           this->frame = frame.clone();
           ui->Video->clear();
           recvImage();
       }
}

void MainWindow::on_getPhoto_clicked()
{
    QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-hh hh_mm_ss");
    QString dirName = "/home/linux/Pictures";
    if(!QFile::exists(dirName)){
        QDir dir;
        if(!dir.mkdir(dirName)){
            return;
        }
    }
    QString filePath = QString("%1/%2.png").arg(dirName).arg(timeStr);
    if (frame.empty()) {
        return;
    }

    cv::Mat rgbImage(frame.rows, frame.cols,frame.type(), cv::Scalar(0,0,0));;
    for(int y = 0;y < frame.rows;++y){
        for(int x= 0;x < frame.cols ; ++x){
            cv::Vec3b &bgr = frame.at<cv::Vec3b>(y,x);
            rgbImage.at<cv::Vec3b>(y,x) = cv ::Vec3b(bgr[2],bgr[1],bgr[0]);
        }
    }
    QImage image(rgbImage.data, rgbImage.cols, rgbImage.rows, rgbImage.step, QImage::Format_RGB888);
    image.save(filePath);
    QPixmap p = QPixmap::fromImage(image);
    ui->Preview->setScaledContents(true);
    ui->Preview->setPixmap(p);
}

void MainWindow::on_exit_clicked()
{
    timer->stop();
    cap.release();
    this->close();
    QApplication::quit;
}

void MainWindow::openPhotoView()
{
    if(!photoview->getCheckUpdate()){
        photoview->loadImages("/home/linux/Pictures");
        photoview->updateImage();
    }
    photoview->showFullScreen();
    //photoview->currentIndex = photoview->updateCount;
    this->hide();
}

void MainWindow::openMainWindow()
{
    this->showFullScreen();
    photoview->hide();
}
