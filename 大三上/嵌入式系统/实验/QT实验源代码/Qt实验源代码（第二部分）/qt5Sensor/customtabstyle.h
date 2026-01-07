#ifndef CUSTOMTABSTYLE_H  // 预处理指令，防止头文件被多次包含
#define CUSTOMTABSTYLE_H

#include <QStyleOptionTab>  // 包含用于绘制标签页的样式选项类
#include <QStylePainter>  // 包含用于绘制样式元素的画笔类
#include <QTabBar>  // 包含标签条类
#include <QPainter>  // 包含画笔类
#include <QProxyStyle>  // 包含代理样式类，可以基于现有的样式进行修改

// 自定义标签页样式类
class CustomTabStyle : public QProxyStyle  // 继承自 QProxyStyle
{
public:
    // 重写 sizeFromContents 方法，用于根据内容确定标签大小
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const override;

    // 重写 drawControl 方法，用于绘制控制元素，如标签页本身
    void drawControl(ControlElement element, const QStyleOption *option,
                     QPainter *painter, const QWidget *widget) const override;
};

#endif // CUSTOMTABSTYLE_H  // 结束头文件包含保护
