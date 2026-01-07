#include "customtabstyle.h"

QSize CustomTabStyle::sizeFromContents(QStyle::ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const {
    // 获取父类默认的标签页尺寸
    QSize itemSize = QProxyStyle::sizeFromContents(type, option, size, widget);
    // 如果是标签页类型，则调整其尺寸
    if (type == QStyle::CT_TabBarTab) {
        itemSize.transpose();// 交换宽度和高度，以实现垂直标签页
        itemSize.rwidth() = 140;// 设置标签页的宽度
        itemSize.rheight() = 60;// 设置标签页的高度
    }
    return itemSize; // 返回调整后的尺寸
}

void CustomTabStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    // 如果是标签页的文本和图标部分
    if (element == CE_TabBarTabLabel) {
        const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option);
        if (tab) {
            QRect allRect = tab->rect;// 获取整个标签页的矩形区域

            // 绘制背景
            if (tab->state & QStyle::State_Selected) {
                painter->save();// 保存画笔状态
                painter->setPen(QColor(0x557a8b));// 设置选中状态的背景边框颜色
                painter->setBrush(QColor(0x557a8b)); // 设置选中状态的背景填充颜色
                painter->drawRoundedRect(allRect.adjusted(6, 6, -6, -6), 10, 10);// 绘制圆角矩形
                painter->restore(); // 恢复画笔状态
            }

             // 设置图标大小
            QSize iconSize(30, 30);
            QRect iconRect(allRect.left() + 10, allRect.top() + (allRect.height() - iconSize.height()) / 2, iconSize.width(), iconSize.height());
            if (!tab->icon.isNull()) {
                tab->icon.paint(painter, iconRect);
            }

            // 调整文本位置以适应图标
            QRect textRect = allRect.adjusted(iconRect.width() + 15, 0, -5, 0);

            // 设置文本样式和绘制文本
            QTextOption textOption;
            textOption.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            if (tab->state & QStyle::State_Selected) {
                painter->setPen(QColor(0xffffff));  // 选中状态的文本颜色
            } else {
                painter->setPen(QColor(0xaaaaaa));  // 非选中状态的文本颜色
            }
            painter->drawText(textRect, tab->text, textOption);
        }
    } else if (element == CE_TabBarTab) {
         // 调用父类的默认绘制方法
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}
