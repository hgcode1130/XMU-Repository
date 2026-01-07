#ifndef CHATLABEL
#define CHATLABE
#include <QDebug>
#include <QWidget>
#include <QListWidgetItem>
#include <QPainter>
#include <QFontMetrics>

class ChatBubbleItem : public QWidget {
public:
    enum BubbleType { Received, Sent };

    ChatBubbleItem(const QString &text, BubbleType type, QWidget *parent = nullptr)
        : QWidget(parent), m_text(text), m_type(type) {
        //setAttribute(Qt::WA_TransparentBackground);
        this->setFont(QFont("Noto Sans CJK SC Regular",20));
       // this->setSizePolicy(QSizePolicy::preferred,QSizePolicy::preferred,);
    }

    QSize getRealString(QString src)
    {
        QFontMetricsF fm(this->font());
        m_lineHeight = fm.lineSpacing();
        int nCount = src.count("\n");
        int nMaxWidth = 0;
        if(nCount == 0) {
            nMaxWidth = fm.width(src);
            QString value = src;
            if(nMaxWidth > m_textWidth) {
                nMaxWidth = m_textWidth;
                int size = m_textWidth / fm.width(" ");
                int num = fm.width(value) / m_textWidth;
                int ttmp = num*fm.width(" ");
                num = ( fm.width(value) ) / m_textWidth;
                nCount += num;
                QString temp = "";
                for(int i = 0; i < num; i++) {
                    temp += value.mid(i*size, (i+1)*size) + "\n";
                }
                src.replace(value, temp);
            }
        } else {
            for(int i = 0; i < (nCount + 1); i++) {
                QString value = src.split("\n").at(i);
                nMaxWidth = fm.width(value) > nMaxWidth ? fm.width(value) : nMaxWidth;
                if(fm.width(value) > m_textWidth) {
                    nMaxWidth = m_textWidth;
                    int size = m_textWidth / fm.width(" ");
                    int num = fm.width(value) / m_textWidth;
                    num = ((i+num)*fm.width(" ") + fm.width(value)) / m_textWidth;
                    nCount += num;
                    QString temp = "";
                    for(int i = 0; i < num; i++) {
                        temp += value.mid(i*size, (i+1)*size) + "\n";
                    }
                    src.replace(value, temp);
                }
            }
        }
        return QSize(nMaxWidth+m_spaceWid, (nCount + 1) * m_lineHeight+2*m_lineHeight);
    }

//    QSize fontRect(QString str)
//    {
//        m_text = str;
//        int minHei = 30;
//        int iconWH = 40;
//        int iconSpaceW = 20;
//        int iconRectW = 5;
//        int iconTMPH = 10;
//        int sanJiaoW = 6;
//        int kuangTMP = 20;
//        int textSpaceRect = 12;
//        m_kuangWidth = this->width() - kuangTMP - 2*(iconWH+iconSpaceW+iconRectW);
//        m_textWidth = m_kuangWidth - 2*textSpaceRect;
//        m_spaceWid = this->width() - m_textWidth;
//        m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);
//        m_iconRightRect = QRect(this->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);

//        QSize size = getRealString(m_text); // 整个的size

//        qDebug() << "fontRect Size:" << size;
//        int hei = size.height() < minHei ? minHei : size.height();

//        m_sanjiaoLeftRect = QRect(iconWH+iconSpaceW+iconRectW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);
//        m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);

//        if(size.width() < (m_textWidth+m_spaceWid)) {
//            m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
//            m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
//                                     m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
//        } else {
//            m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
//            m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
//        }
//        m_textLeftRect.setRect(m_kuangLeftRect.x()+textSpaceRect,m_kuangLeftRect.y()+iconTMPH,
//                               m_kuangLeftRect.width()-2*textSpaceRect,m_kuangLeftRect.height()-2*iconTMPH);
//        m_textRightRect.setRect(m_kuangRightRect.x()+textSpaceRect,m_kuangRightRect.y()+iconTMPH,
//                                m_kuangRightRect.width()-2*textSpaceRect,m_kuangRightRect.height()-2*iconTMPH);

//        return QSize(size.width()-20, hei);
//    }

    QSize fontRect(QString src){
        QFontMetricsF fm(this->font());
        int nMaxWidth = 0;
        int nCount = 0;
        int m_minWidth = 30;
        int m_height = 30;
        int m_margin = 15;
        QStringList lines = src.split("\n");

        foreach (const QString &line,lines) {
            int lineWidth = fm.width(line);
            nMaxWidth = qMax(nMaxWidth,lineWidth);
            nCount++;
        }
        int minWidth = qMax(nMaxWidth,m_minWidth);
        int height = nCount * fm.height() + 2 * m_margin;
        qDebug()<<"minWidth"<<minWidth<<"height"<<height;
        return QSize(minWidth+20,height);
    }



    void paintEvent(QPaintEvent *event) override{
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.setPen(Qt::NoPen);
        painter.setFont(QFont("Noto Sans CJK SC Regular",20));
        // 根据消息类型设置背景颜色
        QColor backgroundColor;
        if (m_type == ChatBubbleItem::Received) {
            backgroundColor = QColor(234, 234, 234); // 接收消息的背景色
            //painter.setPen(QPen(Qt::black));
        } else {
            backgroundColor = QColor(75, 164, 242); // 发送消息的背景色
            //painter.setPen(QPen(Qt::white));
        }
        painter.setBrush(backgroundColor);

        // 绘制消息框的圆角矩形
        QRectF bubbleRect = rect().adjusted(10, 10, -10, -10);
        painter.drawRoundedRect(bubbleRect, 4, 4);

        // 绘制三角形
        QPointF trianglePoints[3];
        if (m_type == ChatBubbleItem::Received) {
            trianglePoints[0] = QPointF(bubbleRect.left(), bubbleRect.bottom());
            trianglePoints[1] = QPointF(bubbleRect.left() - 10, bubbleRect.center().y());
            trianglePoints[2] = QPointF(bubbleRect.left(), bubbleRect.top());

        } else {
            trianglePoints[0] = QPointF(bubbleRect.right(), bubbleRect.bottom());
            trianglePoints[1] = QPointF(bubbleRect.right() + 10, bubbleRect.center().y());
            trianglePoints[2] = QPointF(bubbleRect.right(), bubbleRect.top());
        }
        painter.drawPolygon(trianglePoints, 3);
        if (m_type == ChatBubbleItem::Received) {
            //backgroundColor = QColor(234, 234, 234); // 接收消息的背景色
            painter.setPen(QPen(Qt::black));
        } else {
            //backgroundColor = QColor(75, 164, 242); // 发送消息的背景色
            painter.setPen(QPen(Qt::white));
        }
        // 绘制文本
        QFontMetrics metrics(painter.font());
        int textWidth = metrics.width(m_text);
        int textHeight = metrics.height();
        QRect textRect(bubbleRect.left(), bubbleRect.top() + (bubbleRect.height() - textHeight) / 2, textWidth, textHeight + 6);
        painter.drawText(textRect, Qt::AlignHCenter, m_text);
    }

private:
    QString m_text;
    BubbleType m_type;

    QSize m_allSize;

    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

    QRect m_iconLeftRect;
    QRect m_iconRightRect;
    QRect m_sanjiaoLeftRect;
    QRect m_sanjiaoRightRect;
    QRect m_kuangLeftRect;
    QRect m_kuangRightRect;
    QRect m_textLeftRect;
    QRect m_textRightRect;
    QPixmap m_leftPixmap;
    QPixmap m_rightPixmap;
};
#endif // CHATLABEL






