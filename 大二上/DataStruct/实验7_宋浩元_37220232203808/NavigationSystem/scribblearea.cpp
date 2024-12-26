/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sigin.h"
#include "login.h"
#include "welcom.h"
#include "scribblearea.h"
#include "mysql.h"
#include "scribblearea.h"
#include "main.h"
#include "base.h"
#include "libpoint.h"
#include "mymap.h"
#include <QLabel>
#include <QMessageBox>
#include <QPalette>
#include <QMouseEvent>
#include <QPainter>
#include <QtDebug>
#include <QInputDialog>
#include <QVector>

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

void ScribbleArea::test(){
    qDebug() << "test";
    QRect tep = QRect(100,50,100,100);
    QImage k =  QImage() ;
    k = image.copy(100,100,100,100);
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    lastPoint = QPoint(lastMyPoint->x.toUInt(),lastMyPoint->y.toUInt());
    painter.drawImage(300,300,k);
    modified = true;

    update();
}


//! [0]
ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);

    setMouseTracking(true); // 启用鼠标悬浮事件
    startPoint = NULL;
    endPoint = NULL;
    showmap = true;
    QTimer::singleShot(2000, this, [this]() {
        databaseReady = true;
        qDebug() << "数据库加载完成，可以开始交互！";
    });
}

bool ScribbleArea::openImage(const QString &fileName)
//! [1] //! [2]
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    }
    return false;
}

void ScribbleArea::setPenColor(const QColor &newColor)
//! [5] //! [6]
{
    myPenColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void ScribbleArea::clearImage()
{

    if (showmap){
        openImage(":/map/Map.png");
        update();
    }else {
        image.fill(qRgba(255, 255, 255,255));
        modified = true;
    }

}
//! [10]

//! [11]
void ScribbleArea::mousePressEvent(QMouseEvent *event)
//! [11] //! [12]
{
    if (!databaseReady) {
        QMessageBox::information(this, "提示", "数据库正在加载，请稍候！");
        return;
    }
    qDebug() << "mousePressEvent";
    qDebug() << "x:" << event->x() << ",y:" << event->y();
    if (event->button() == Qt::LeftButton) {
        qDebug() << "event->button left";
        MySQL sql;
        sql.get_point_by_XY(&lastMyPoint,event->pos().x(),event->pos().y());
        //lastMyPoint = new Point(event->pos().x(),event->pos().y());
        //draw_line = true;
        //if (lastMyPoint == NULL){
           // lastMyPoint = new Point(event->pos().x(),event->pos().y());
        //}
       // drawPointAt(lastMyPoint->toQPoint());
    }else if (event->button() == Qt::RightButton){

    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if (!databaseReady) {
        QMessageBox::information(this, "提示", "数据库正在加载，请稍候！");
        return;
    }
    //setToolTip("this is a tip");
    static QPoint lt;
    static QPoint  rd;
    qDebug() << "mouseMoveEvent";
    // 显示建筑点信息的功能
    QPoint mousePos = event->pos();
    MySQL &sql = MySQL::getInstance();
    Point *hoveredPoint = nullptr;
    // 判断当前鼠标位置是否有建筑点
    sql.get_point_by_XY(&hoveredPoint, mousePos.x(), mousePos.y());
    if(hoveredPoint == nullptr) qDebug() << "hoveredPoint is null";
    if (hoveredPoint != nullptr) {
        if(hoveredPoint->build.toInt() == 1){
            // 如果是建筑点，显示建筑信息
            QString info = tr("建筑名称: %1\n建筑信息: %2")
                               .arg(hoveredPoint->name)
                               .arg(hoveredPoint->about);

            if (!infoLabel) {
                infoLabel = new QLabel(start->getMainWindow()); // 初始化 infoLabel
                infoLabel->setStyleSheet("background-color: white; color: black; border: 1px solid gray; padding: 5px;");
            }

            infoLabel->setText(info);
            infoLabel->adjustSize();

            // 在建筑点附近显示提示框
            int labelWidth = infoLabel->width();
            int labelHeight = infoLabel->height();
            int offsetX = 10; // 偏移量
            int offsetY = -labelHeight - 10; // 上方偏移量

            QPoint labelPos = mousePos + QPoint(offsetX, offsetY);
            if (labelPos.x() + labelWidth > this->width()) {
                labelPos.setX(this->width() - labelWidth - 5); // 防止超出右边界
            }
            if (labelPos.y() < 0) {
                labelPos.setY(0); // 防止超出上边界
            }

            infoLabel->move(labelPos);
            infoLabel->show();
        }
    } else {
        // 如果不是建筑点，则隐藏提示
        if (infoLabel) {
            infoLabel->hide();
        }
    }

    if ((event->buttons() & Qt::LeftButton) && start->isAdmin()){
        if (lastMyPoint == NULL){
            return;
        }
        if (lastRect == NULL){ // 第一次移动则为空，仅仅复制区域
            lastRect = new QImage();
            qDebug() << "new Image()";
            qDebug() << "image.copy: x:" << lt.x() << ",y:" << lt.y() << ",w:" << rd.x()- lt.x()  << ",h:" << rd.y()- lt.y();
            return;
        }
        if (draw_line){ // 不为空，则先覆盖区域，再复制图层，最后画线；
            QPainter painter(&image);
            painter.drawImage(lt,*lastRect);
            painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                                Qt::RoundJoin));

            lt = getltPoint(lastMyPoint->x.toInt(),lastMyPoint->y.toInt(),event->pos().x(),event->pos().y());
            rd = getrdPoint(lastMyPoint->x.toInt(),lastMyPoint->y.toInt(),event->pos().x(),event->pos().y());
            *lastRect = image.copy(lt.x(),lt.y(), rd.x()- lt.x() + 1 ,  rd.y()-lt.y() + 1);
            painter.drawLine(lastMyPoint->toQPoint(),event->pos());
            update();
            painter.end();
            return;
        }else if (lastMyPoint != NULL && get_long(lastMyPoint->toQPoint(),event->pos()) > 20 ){
           //移动小于某个范围不画线。
            draw_line = true;
        }
    }
    if (hoveredPoint) {
        delete hoveredPoint; // 确保释放内存
        hoveredPoint = nullptr; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!一个问题找了我1h我吐了。
    }
}
// 鼠标移动事件


void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (!databaseReady) {
        QMessageBox::information(this, "提示", "数据库正在加载，请稍候！");
        return;
    }
    qDebug() << "mouseRealseEvent";
    if (event->button() == Qt::LeftButton) {

        qDebug() << "event->button left";
        if (draw_line){//画线触发的释放按钮
            Point *tep = NULL;
            MySQL &sql = MySQL::getInstance();
            sql.get_point_by_XY(&tep,event->pos().x(),event->pos().y());
            if (tep == NULL){
                sql.inser_near(lastMyPoint->x.toInt(),lastMyPoint->y.toInt(),event->pos().x(),event->pos().y());
                sql.inser_near(event->pos().x(),event->pos().y(),lastMyPoint->x.toInt(),lastMyPoint->y.toInt());
                Point insert_val = Point(event->pos().x() , event->pos().y() );
                sql.inser_point( &insert_val);
                drawPointAt(event->pos());
            }else {
                sql.inser_near(lastMyPoint->x.toInt(),lastMyPoint->y.toInt(),tep->x.toInt(),tep->y.toInt());
                sql.inser_near(tep->x.toInt(),tep->y.toInt(),lastMyPoint->x.toInt(),lastMyPoint->y.toInt());
            }
            delete lastMyPoint;
            delete  lastRect;
            lastMyPoint = NULL;
            lastRect = NULL;
            draw_line = false;
        }

    }else if (event->button() == Qt::RightButton){
        MySQL &sql = MySQL::getInstance();
        sql.get_point_by_XY(&thisMyPoint,event->pos().x(),event->pos().y());
        if (thisMyPoint == NULL){
            thisMyPoint = new Point(event->pos().x(),event->pos().y());
        }else {
            setStrat = true;
        }
        add_right_click_menu();//只能在释放按键时添加菜单，否则会在弹起时触发点击事件。或者在响应方法内添加只响应左键也可。
    }
}

//! [12] //! [13]
void ScribbleArea::paintEvent(QPaintEvent *event)
//! [13] //! [14]
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
    update(); // 刷新整个窗口
}
//! [14]

//! [15]
void ScribbleArea::resizeEvent(QResizeEvent *event)
//! [15] //! [16]
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}
//! [16]

//! [17]
void ScribbleArea::drawLineTo(const QPoint &endPoint)
//! [17] //! [18]
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    lastPoint = QPoint(lastMyPoint->x.toUInt(),lastMyPoint->y.toUInt());
    painter.drawLine(lastPoint, endPoint);
    painter.drawPoint(endPoint);
    modified = true;
    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}
//! [18]
//!
void ScribbleArea::drawLineA2B(const QPoint &startPoint,const QPoint &endPoint)
//! [17] //! [18]
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    lastPoint = QPoint(lastMyPoint->x.toUInt(),lastMyPoint->y.toUInt());
    painter.drawLine(startPoint, endPoint);
    painter.drawPoint(endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));
}
void ScribbleArea::drawPointAt(const QPoint &pos){

    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, 5, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawPoint(pos);

   // painter.drawText(pos,"this is a point");
    modified = true;
    int rad = (myPenWidth / 2) + 2;
    update(QRect(pos.x() - rad, pos.y() - rad, rad * 2, rad * 2)); // 更新点的局部区域
}




//! [19]
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
//! [19] //! [20]
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGBA8888);
    newImage.fill(qRgba(255, 255, 255,0));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}
//! [20]

//! [21]
void ScribbleArea::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog printDialog(&printer, this);
//! [21] //! [22]
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_CONFIG(printdialog)
}
//! [22]


void ScribbleArea::add_right_click_menu(){
    QMenu *pMenu = new QMenu(this);
    pMenu->setStyleSheet( "QMenu {"
                            "background: #F00000;"
                            "border-width: 10px 20px 30px 40px;"
                            "} "
                            " QMenu::item {"//
                            "font-size: 10pt; "
                            "color: rgb(225,225,225); " /*字体颜色*/
                            // "border: 1px solid rgb(60,60,60);  "  /*item选框*/
                            " background-color:rgb(89,87,87);"
                            "padding:16px 16px; "/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/
                            " margin:2px 2px;"/*设置菜单项的外边距*/
                            " }"
                            " QMenu::item:selected { "
                            " background-color:rgb(235,110,36);"/*选中的样式*/
                            "}"
                            "QMenu::item:pressed {"/*菜单项按下效果*/
                            "border: 1px solid rgb(60,60,61); "
                            "background-color: rgb(220,80,6); "
                        "}");

    QAction *pDeleteTask = new QAction(tr("清空路径"), this);

    //1:新建任务 2:设置任务 3:删除任务 4:改名工具 5:设置工具 6:删除工具

    pDeleteTask ->setData(3);

    //把QAction对象添加到菜单上
    pMenu->addAction(pDeleteTask);

    //连接鼠标右键点击信号
    connect(pDeleteTask, SIGNAL(triggered()),this, SLOT(onTaskBoxContextMenuEvent()));

    QAction *pshowMap;
    if (!showmap){
       pshowMap = new QAction(tr("显示图片地图"), this);
    }else {
        pshowMap = new QAction(tr("显示纯色地图"), this);
    }
    pshowMap->setData(10);
    pMenu->addAction(pshowMap);
    connect(pshowMap, SIGNAL(triggered()),this, SLOT(onTaskBoxContextMenuEvent()));

    if (start->isAdmin()){
        QAction *pAddPoint = new QAction(tr("在此添加点"),this);
        if (thisMyPoint->build.toInt() == 1){  //建筑点专有菜单
            QAction *pToolAbout = new QAction(tr("建筑信息修改"), this);
            pToolAbout->setData(7);
            connect(pToolAbout, SIGNAL(triggered()), this,SLOT(onTaskBoxContextMenuEvent()));
            pMenu->addAction(pToolAbout);

            QAction *pToolRenName = new QAction(tr("建筑名称修改"), this);
            pMenu->addAction(pToolRenName);
            pToolRenName->setData(4);
            connect(pToolRenName, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
        }else{
            QAction *pT2build = new QAction(tr("添加或转换为建筑"), this);
            pT2build->setData(9);
            connect(pT2build, SIGNAL(triggered()), this,SLOT(onTaskBoxContextMenuEvent()));
            pMenu->addAction(pT2build);

        }
        if (thisMyPoint->build.toInt() == 1){

        }
        QAction *setLastPointAction = new QAction(tr("设置为lastMyPoint"), this);
        pMenu->addAction(setLastPointAction);
        setLastPointAction->setData(11); // 对应 case 11
        connect(setLastPointAction, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));

        QAction *connectToLastPointAction = new QAction(tr("连接到lastMyPoint"), this);
        pMenu->addAction(connectToLastPointAction);
        connectToLastPointAction->setData(12); // 对应 case 12
        connect(connectToLastPointAction, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));

        QAction *pToolEdot = new QAction(tr("删除该点"), this);
        QAction *pToolDelete = new QAction(tr("在地图画出所有点"), this);

        pToolEdot->setData(5);
        pToolDelete ->setData(6);
        pAddPoint->setData(8);

        pMenu->addAction(pAddPoint);
        pMenu->addAction(pToolEdot);
        pMenu->addAction(pToolDelete);

        connect(pAddPoint,SIGNAL(triggered()),this,SLOT(onTaskBoxContextMenuEvent()));
        connect(pToolEdot, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
        connect(pToolDelete, SIGNAL(triggered()),this, SLOT(onTaskBoxContextMenuEvent()));
    }

    //该板块是多点经过求解最短路
    QAction *addWaypoint = new QAction(tr("将该点加入待经过点"), this);
    addWaypoint->setData(13);
    pMenu->addAction(addWaypoint);
    connect(addWaypoint, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));

    QAction *clearWaypoints = new QAction(tr("清空待经过点"), this);
    clearWaypoints->setData(14);
    pMenu->addAction(clearWaypoints);
    connect(clearWaypoints, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));

    QAction *calculateShortestPath = new QAction(tr("求最短路径"), this);
    calculateShortestPath->setData(15);
    pMenu->addAction(calculateShortestPath);
    connect(calculateShortestPath, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));

    if (thisMyPoint->build.toInt() == 1){  //建筑点专有菜单
        QAction *pNewTask = new QAction(tr("设为起点"), this);
        QAction *pEditTask = new QAction(tr("设为终点"), this);
        pNewTask->setData(1);
        pEditTask->setData(2);
        pMenu->addAction(pNewTask);
        pMenu->addAction(pEditTask);
        connect(pNewTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
        connect(pEditTask, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    }
    //在鼠标右键点击的地方显示菜单
    pMenu->exec(cursor().pos());

    //释放内存
    QList<QAction*> list = pMenu->actions();
    foreach (QAction* pAction, list) delete pAction;
    delete pMenu;
}

void ScribbleArea::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender());
    int iType = pEven->data().toInt();

    switch (iType)
    {
    case 1:
        setStartPoint();
        QMessageBox::about(start->getMainWindow(), "提示", pEven->text());
        break;
    case 2:
        setEndPoint();
        QMessageBox::about(start->getMainWindow(), "提示", pEven->text());
        break;
    case 3:
        delete_line();
        QMessageBox::about(start->getMainWindow(), "提示", pEven->text());
        break;
    case 4:
        get_build_name();
        break;
    case 5:
        delete_point();
        QMessageBox::about(start->getMainWindow(), "提示", pEven->text());
        break;
    case 6:
        clearImage();
        drawAllPointFromSQL();
        drawAllLineFromSQL();
        QMessageBox::about(start->getMainWindow(), "提示", pEven->text());
        break;
    case 7:
        set_about();
        break;
    case 8:
        add_point();
        break;
    case 9:
        t2_build();
        break;
    case 10:
        showmap = !showmap;
        qDebug() << showmap << "切换地图模式";
        clearImage();
        drawAllLineFromLib();
        drawAllPointFromSQL();
        break;
    case 11: { // 设置为起点 (lastMyPoint)
        if (thisMyPoint != nullptr) {
            if (lastMyPoint) delete lastMyPoint;
            lastMyPoint = new Point(*thisMyPoint);

            // 插入点到数据库
            MySQL &sql = MySQL::getInstance();
            sql.inser_point(lastMyPoint); // 如果点已存在，不会覆盖

            // 自定义对话框，确保背景为白色
            QMessageBox msgBox(start->getMainWindow());
            msgBox.setStyleSheet("background-color: white; color: black;");
            msgBox.setText(tr("设置起点成功:\n%1").arg(lastMyPoint->to_string()));
            msgBox.exec();

            qDebug() << "设置 lastMyPoint 为：" << lastMyPoint->to_string();
        } else {
            QMessageBox::warning(start->getMainWindow(), tr("警告"), tr("未选中有效的点！"));
        }
        break;
    }
    case 12: { // 连接到起点 (lastMyPoint)
        if (lastMyPoint && thisMyPoint) {
            // 绘制连线
            drawLineA2B(lastMyPoint->toQPoint(), thisMyPoint->toQPoint());

            // 插入两点及其连接到数据库
            MySQL &sql = MySQL::getInstance();
            sql.inser_point(lastMyPoint); // 插入起点
            sql.inser_point(thisMyPoint); // 插入终点
            sql.inser_near(lastMyPoint->x.toInt(), lastMyPoint->y.toInt(),
                           thisMyPoint->x.toInt(), thisMyPoint->y.toInt()); // 连接起点和终点
            sql.inser_near(thisMyPoint->x.toInt(), thisMyPoint->y.toInt(),
                           lastMyPoint->x.toInt(), lastMyPoint->y.toInt()); // 连接终点和起点（双向）

            // 显示成功消息
            QMessageBox msgBox(start->getMainWindow());
            msgBox.setStyleSheet("background-color: white; color: black;");
            msgBox.setText(tr("已连接起点到目标点！\n起点: %1\n目标点: %2")
                               .arg(lastMyPoint->to_string())
                               .arg(thisMyPoint->to_string()));
            msgBox.exec();

            qDebug() << "连接点：" << lastMyPoint->to_string() << " -> " << thisMyPoint->to_string();
        } else {
            QMessageBox::warning(start->getMainWindow(), tr("警告"), tr("请确保已设置起点和点击了目标点！"));
        }
        break;
    }
    case 13 : {
        if (thisMyPoint != nullptr) {
            waypoints.append(thisMyPoint->toQPoint()); // 将点加入到待经过点列表
            QMessageBox::information(start->getMainWindow(), "提示", tr("已将点加入到待经过点列表！\n点坐标: (%1, %2)")
                                                                         .arg(thisMyPoint->x)
                                                                         .arg(thisMyPoint->y));
            qDebug() << "当前待经过点列表:" << waypoints;
        } else {
            QMessageBox::warning(start->getMainWindow(), "警告", "未选中有效的点！");
        }
        break;
    }
    case 14: { // 清空待经过点
        waypoints_clear();
        break;
    }
    case 15: { // 计算最短路径
        find_waypoints_path();
        break;
    }
    default:
        break;
    }
}

void ScribbleArea::waypoints_clear(){
    waypoints.clear();
    QMessageBox::information(start->getMainWindow(), "提示", "已清空待经过点列表！");
    qDebug() << "待经过点列表已清空";
}

void ScribbleArea::find_waypoints_path(){
    if (waypoints.isEmpty()) {
        QMessageBox::warning(start->getMainWindow(), "警告", "待经过点列表为空，无法计算路径！");
        return;
    }
    if (waypoints.size() < 2) {
        QMessageBox::warning(start->getMainWindow(), "警告", "待经过点数量不足，无法计算路径！");
        return;
    }

    QVector<QPoint> path; // 最终路径
    for (int i = 0; i < waypoints.size() - 1; ++i) {
        QVector<QPoint> subPath = start->LP->get_min_path(waypoints[i], waypoints[i + 1]);
        if (subPath.isEmpty()) {
            QMessageBox::warning(start->getMainWindow(), "警告", tr("从点 (%1, %2) 到点 (%3, %4) 无法找到路径！")
                                                                     .arg(waypoints[i].x())
                                                                     .arg(waypoints[i].y())
                                                                     .arg(waypoints[i + 1].x())
                                                                     .arg(waypoints[i + 1].y()));
            return;
        }
        // 将路径段加入最终路径
        path.append(subPath);
    }
    if (!path.isEmpty()) {
        // setStartPoint(path.begin());
        // setEndPoint(&path.back());
        start->LP->init_from_sql();
        QPainter painter(&image);
        painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
        painter.setPen(QPen(myPenColor, 10, Qt::SolidLine, Qt::RoundCap,   Qt::RoundJoin));
        for (int i = 0;i < path.size() - 1;i++){
            qDebug() << "绘制线段：从" << path.at(i) << "到" << path.at(i + 1);
            painter.drawLine(path.at(i),path.at(i + 1));
        }
        modified = true;
        update();
        QMessageBox::information(start->getMainWindow(), "提示", "最短路径已绘制完成！");
    }
    else{
        QMessageBox::information(start->getMainWindow(), "Error", "无法找到通路");
    }
}
void ScribbleArea:: showLine(QPoint A,QPoint B){
        start->LP->init_from_sql();
        QPainter painter(&image);
        painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                                                                  Qt::RoundJoin));
        painter.setPen(QPen(myPenColor, 10, Qt::SolidLine, Qt::RoundCap,   Qt::RoundJoin));
        QVector<QPoint> gval =  start->LP->get_min_path(A,B);
        qDebug() << gval.size();
        for (int i = 0;i < gval.size() - 1;i++){
                qDebug() << "绘制线段：从" << gval.at(i) << "到" << gval.at(i + 1);
               painter.drawLine(gval.at(i),gval.at(i + 1));
        }
        modified = true;
        update();
}

void ScribbleArea::setStartPoint()
{
    if (setStrat){
        startPoint = new QPoint(thisMyPoint->toQPoint());
    }else {
        QMessageBox::about(start->getMainWindow(), "tip", "请选择一个有效点！");
    }
    setStrat = false;
}

void ScribbleArea::setStartPoint(QPoint *q)
{
    if (setStrat){
        startPoint = new QPoint(*q);
    }else {
        QMessageBox::about(start->getMainWindow(), "tip", "请选择一个有效点！");
    }
    setStrat = false;
}
void ScribbleArea::setEndPoint(){
    if(startPoint != NULL){
        endPoint = new QPoint(thisMyPoint->toQPoint());
        showLine(*startPoint,*endPoint);
        qDebug() << "设置终点为：" << endPoint->x() << "," << endPoint->y();
    }else {
        QMessageBox::about(start->getMainWindow(), "tip", "请选择起始点！");
    }
     setStrat = false;
}
void ScribbleArea::setEndPoint(QPoint *q){
    if(startPoint != NULL){
        endPoint = new QPoint(*q);
        showLine(*startPoint,*endPoint);
        qDebug() << "设置终点为：" << endPoint->x() << "," << endPoint->y();
    }else {
        QMessageBox::about(start->getMainWindow(), "tip", "请选择起始点！");
    }
    setStrat = false;
}

void ScribbleArea::delete_line(){
    clearImage();
    drawAllLineFromSQL();
    drawAllPointFromSQL();
}
void ScribbleArea::t2_build(){
    bool ok = 1;
    QString text_name = QInputDialog::getText(start->getMainWindow(), tr("输入建筑名称"),tr("请输入"), QLineEdit::Normal,0, &ok);
    QString text_about = QInputDialog::getText(start->getMainWindow(), tr("输入建筑信息"),tr("请输入"), QLineEdit::Normal,0, &ok);
    MySQL &sql = MySQL::getInstance();
    Point tep = Point(thisMyPoint->x,thisMyPoint->y,"1",text_about,text_name);
    sql.inser_point(&tep);

}
void ScribbleArea::update_about(){
    bool ok = 1;
    QString text = QInputDialog::getText(start->getMainWindow(), tr("输入建筑名称"),tr("请输入"), QLineEdit::Normal,0, &ok);
    qDebug() << text;
    if (text.length() != 0){
        MySQL sql;
        sql.update(thisMyPoint->x,thisMyPoint->y,thisMyPoint->build,text,thisMyPoint->about);
    }
}

void ScribbleArea::update_name(){
    bool ok = 1;
    QString text = QInputDialog::getText(start->getMainWindow(), tr("修改名称"),tr("请输入"), QLineEdit::Normal,0, &ok);
    qDebug() << text;
    if (text.length() != 0){
        MySQL sql;
        sql.update(thisMyPoint->x,thisMyPoint->y,thisMyPoint->build,text,thisMyPoint->about);
    }
    clearImage();
    drawAllLineFromSQL();
    drawAllPointFromSQL();
}
void ScribbleArea::delete_point(){
    MySQL &sql = MySQL::getInstance();
    sql.remove_point_by_XY(thisMyPoint->x.toInt(),thisMyPoint->y.toInt());
    clearImage();
    drawAllPointFromSQL();
    drawAllLineFromSQL();
}
void ScribbleArea::add_point() {
    // 创建 MySQL 实例
    MySQL &sql = MySQL::getInstance();

    // 检查当前点是否已存在（允许误差范围）
    Point *existingPoint = nullptr;
    sql.get_point_by_XY(&existingPoint, thisMyPoint->x.toInt(), thisMyPoint->y.toInt());

    if (existingPoint != nullptr) {
        // 如果存在点，则不进行任何操作
        qDebug() << "添加点失败：该点已存在 (" << existingPoint->x << "," << existingPoint->y << ")";
        delete existingPoint; // 释放内存
        return;
    }

    // 如果不存在点，则标记为普通点并添加到数据库
    thisMyPoint->build = "0"; // 标记为普通点
    sql.inser_point(thisMyPoint); // 插入新点到数据库

    // 在界面上绘制新点
    drawPointAt(thisMyPoint->toQPoint());
    qDebug() << "成功添加新点：" << thisMyPoint->x << "," << thisMyPoint->y;
    clearImage(); // 清空当前图像
    drawAllPointFromSQL(); // 从数据库重新绘制所有点
    drawAllLineFromSQL(); // 从数据库重新绘制所有线
}


void ScribbleArea::set_about(){
    bool ok = 1;
    QString text = QInputDialog::getText(start->getMainWindow(), tr("修改About"),tr("请输入"), QLineEdit::Normal,0, &ok);
    qDebug() << text;
    if (text.length() != 0){
        MySQL sql;
        sql.update(thisMyPoint->x,thisMyPoint->y,thisMyPoint->build,thisMyPoint->name,text);
    }
}

void ScribbleArea::get_build_name(){
            bool ok = 1;
            QString text = QInputDialog::getText(start->getMainWindow(), tr("建筑名称修改"),tr("请输入："), QLineEdit::Normal,0, &ok);
            qDebug() << text;
            if (text.length() != 0){

            }
}

void ScribbleArea::drawAllPointFromSQL(){
    MySQL &sql = MySQL::getInstance();
    bool admin = start->isAdmin();
    QVector<Point> getval =  sql.getAllPoints();
    if (admin){
        qDebug() << "draw as admin";
        for (auto val : getval) {
            qDebug() << "drawing..:" << val.to_string();
            drawPointAt(val.toQPoint());
            drawtextAt(val.toQPoint(),val.name);
        }
    }else {
        qDebug() << "draw common";
        for (auto val : getval) {
            qDebug() << val.to_string();
            if (QString::compare(val.build,"1") == 0){
                QPoint tep = QPoint(val.x.toUInt(),val.y.toInt());
                drawPointAt(tep);
                drawtextAt(val.toQPoint(),val.name);
            }
        }
    }

}

void ScribbleArea:: drawtextAt(QPoint pos,QString s){

        QPainter painter(&image);
        painter.setPen(QPen(myPenColor, 5, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
        painter.drawPoint(pos);

        painter.drawText(pos,s);
        modified = true;
        int rad = (myPenWidth / 2) + 2;
        update();


}
void ScribbleArea::drawAllLineFromLib(){

    start->LP->init_from_sql();
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                                                              Qt::RoundJoin));
    QVector<Point> getval = start->LP->getAllLines();

        for (auto val : getval) {
        qDebug() << val.to_string() << val.next_to_point();
        painter.drawLine(val.next_to_point(),val.toQPoint());
        painter.drawText(val.toQPoint(),val.name);
    }

    modified = true;
    update();
}

void ScribbleArea::drawAllLineFromSQL(){
    MySQL &sql = MySQL::getInstance();
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                                                              Qt::RoundJoin));
    QVector<Point> getval =  sql.getAllLines();
    for (auto val : getval) {
        qDebug() << val.to_string() << val.next_to_point();

        painter.drawLine(val.next_to_point(),val.toQPoint());
    }
    modified = true;
    update();
}

QPoint ScribbleArea::getltPoint(int x1, int y1, int x2, int y2){
    int x = x1 < x2 ? x1 : x2;
    int y = y1 < y2 ? y1 : y2;
    qDebug() << "lt{x:" << x << ",y:" << y <</* ",w:" << w << ",h:" <<h <<*/ "}";
    return QPoint(x,y);
}
QPoint ScribbleArea::getrdPoint(int x1, int y1, int x2, int y2){
    int x = x1 > x2 ? x1 : x2;
    int y = y1 > y2 ? y1 : y2;
    qDebug() << "rd{x:" << x << ",y:" << y <</* ",w:" << w << ",h:" <<h <<*/ "}";
    return QPoint(x ,y );
}

////clean 部分，以透明色画图实现擦除
