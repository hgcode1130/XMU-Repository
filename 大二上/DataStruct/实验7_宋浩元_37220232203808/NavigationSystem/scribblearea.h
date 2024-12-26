#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H
#include <QTimer>
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QLabel>
#include "point.h"

//! [0]
/**
 * @class ScribbleArea
 * @brief 该类是基于 QWidget 的自定义控件，用于在地图上绘制点、线、路径，同时实现与用户的交互（如鼠标事件和右键菜单）。
 */
class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    // 数据成员：与节点和路径管理相关
    Point *lastMyPoint = NULL;  ///< 记录上一个选中的点
    Point *thisMyPoint = NULL;  ///< 记录当前选中的点
    QImage *lastRect = NULL;    ///< 用于记录绘图过程中被修改的图像区域
    bool draw_line = false;     ///< 是否允许绘制线条
    bool setStrat = false;      ///< 是否设置起点状态
    QLabel* infoLabel ;
     QVector<QPoint> waypoints;
    bool databaseReady;
public:
    /**
     * @brief 构造函数，初始化 ScribbleArea。
     * @param parent 父窗口
     */
    ScribbleArea(QWidget *parent = nullptr);
    ~ScribbleArea(){
        if (infoLabel) {
            delete infoLabel;
            infoLabel = nullptr;
        }
    }
    /**
     * @brief 打开地图图像文件并加载到绘图区域。
     * @param fileName 图像文件路径
     * @return 如果成功加载图像，则返回 true；否则返回 false。
     */
    bool openImage(const QString &fileName);

    /**
     * @brief 保存当前绘制内容到图像文件。
     * @param fileName 保存文件路径
     * @param fileFormat 文件格式
     * @return 如果成功保存，则返回 true；否则返回 false。
     */
    bool saveImage(const QString &fileName, const char *fileFormat);

    /**
     * @brief 设置画笔颜色。
     * @param newColor 新的画笔颜色
     */
    void setPenColor(const QColor &newColor);

    /**
     * @brief 设置画笔宽度。
     * @param newWidth 新的画笔宽度
     */
    void setPenWidth(int newWidth);

    // 点和路径管理
    void add_point();                 ///< 添加新点
    void delete_point();              ///< 删除当前选中点
    void update_about();              ///< 更新点的附加信息
    void update_name();               ///< 更新点的名称
    void t2_build();                  ///< 将点转换为建筑节点
    void drawAllLineFromSQL();        ///< 从数据库中绘制所有路径
    void drawAllLineFromLib();        ///< 从内部数据绘制所有路径
    void delete_line();               ///< 删除选中的路径
    void setStartPoint();             ///< 设置起点
    void setStartPoint(QPoint *);
    void setEndPoint();               ///< 设置终点
    void setEndPoint(QPoint *);
    void showLine(QPoint A, QPoint B);///< 显示从点 A 到点 B 的路径
    void drawtextAt(QPoint pos, QString s); ///< 在指定位置绘制文字

    // 获取当前状态
    bool isModified() const { return modified; } ///< 判断当前内容是否被修改
    QColor penColor() const { return myPenColor; } ///< 获取画笔颜色
    int penWidth() const { return myPenWidth; } ///< 获取画笔宽度

    // 菜单与绘图功能
    void add_right_click_menu();          ///< 添加右键菜单
    void ad_menu_2();                     ///< 添加额外的菜单（未实现）
    void drawPointAt(const QPoint &pos);  ///< 在指定位置绘制点
    void clear_drawPointAt(const QPoint &pos); ///< 清除指定位置的点
    void get_build_name();                ///< 获取建筑名称
    void drawLineA2B(const QPoint &startPoint, const QPoint &endPoint); ///< 绘制从 A 到 B 的线
    void clear_drawLineA2B(const QPoint &startPoint, const QPoint &endPoint); ///< 清除从 A 到 B 的线
    void drawAllPointFromSQL();           ///< 从数据库中绘制所有点
    void clear_drawAllPointFromSQL();     ///< 清除从数据库中绘制的所有点
    void set_about();                     ///< 设置建筑的附加信息
    void test();                          ///< 测试函数
    QPoint getltPoint(int x1, int y1, int x2, int y2); ///< 获取矩形左上角坐标
    QPoint getrdPoint(int x1, int y1, int x2, int y2); ///< 获取矩形右下角坐标
    void waypoints_clear(); //waypoints清空
    void find_waypoints_path(); //waypoints找路径
public slots:
    void onTaskBoxContextMenuEvent(); ///< 右键菜单项的槽函数
    void clearImage();                ///< 清除当前图像内容
    void print();                     ///< 打印当前图像内容

protected:
    /**
     * @brief 鼠标按下事件处理函数。
     * @param event 鼠标事件
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief 鼠标移动事件处理函数。
     * @param event 鼠标事件
     */
    void mouseMoveEvent(QMouseEvent *event) override;

    /**
     * @brief 鼠标释放事件处理函数。
     * @param event 鼠标事件
     */
    void mouseReleaseEvent(QMouseEvent *event) override;

    /**
     * @brief 绘图事件处理函数。
     * @param event 绘图事件
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief 窗口调整大小事件处理函数。
     * @param event 调整大小事件
     */
    void resizeEvent(QResizeEvent *event) override;

public:
    void drawLineTo(const QPoint &endPoint); ///< 绘制从当前点到终点的直线
    void clear_drawLineTo(const QPoint &endPoint); ///< 清除从当前点到终点的直线
    void resizeImage(QImage *image, const QSize &newSize); ///< 调整图像大小

    // 成员变量
    bool modified = false;         ///< 内容是否被修改
    bool scribbling = false;       ///< 是否正在绘图
    int myPenWidth = 1;            ///< 画笔宽度
    QColor myPenColor = Qt::blue;  ///< 画笔颜色
    QImage image;                  ///< 绘图使用的图像
    QPoint lastPoint;              ///< 上一个绘图点
    QPoint *startPoint;            ///< 起点指针
    QPoint *endPoint;              ///< 终点指针
    bool showmap;                  ///< 是否显示地图

};
//! [0]

#endif // SCRIBBLEAREA_H
