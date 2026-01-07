/***************************************************************************
**
**  <SYSZUXpinyin 1.0 , a chinese input method based on Qt for Embedded linux>
**  Copyright (C) <2010> <Gemfield> <gemfield@civilnet.cn>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License version 3 as published
**  by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
**  If you have questions regarding the use of this file, please contact
**  Gemfield at gemfield@civilnet.cn or post your questions at
**  http://civilnet.cn/syszux/bbs
**
****************************************************************************/

#include <QtGui>
#include "syszuxpinyin.h"
#include <QPalette>
#include <QMessageBox>
#include <QButtonGroup>
QString syszux_lower_letter[52]={"1","2","3","4","5","6","7","8","9","0","-","=","<-","q","w","e","r","t","y","u","i",
                            "o","p","[","]","\\","a","s","d","f","g","h","j","k","l",";","\'","enter","z","x","c","v",
                            "b","n","m",",",".","/","shift"," "};
QString syszux_upper_letter[52]={"!","@","#","$","%","^","&&","*","(",")","_","+","<-","Q","W","E","R","T","Y","U","I",
                            "O","P","{","}","|","A","S","D","F","G","H","J","K","L",":","\"","enter","Z","X","C","V",
                            "B","N","M","<",">","?","SHIFT"," "};
SyszuxPinyin::SyszuxPinyin() :QDialog(0,Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint),button_group(new QButtonGroup(this)),input_method(0),lower_upper(0),page_count(0)
{                                                                  //参数列表：设置了一下窗口到属性
    int ret=0;
    setupUi(this);

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0x46,0x45,0x47));        //009ad6  464547

    this->setPalette(palette);
    initGb();                                               //
    pinyin_file.setFileName(":/syszux/syszuxpinyin");       //设置QFile的名称
    if( !pinyin_file.open(QIODevice::ReadOnly) )            //只读模式，打开文件
        QMessageBox::warning(0,tr("syszuxpinyin"),tr("can't load"));    //打开失败，则报错

    regExp.setCaseSensitivity(Qt::CaseSensitive);           //设置正则表达式的参数,Qt::CaseInsensitive,大小写敏感
    regExp.setPattern(QString("([a-z]+)"));                 //获得正则本身,获取a-z

    while(!pinyin_file.atEnd())
    {
        QByteArray data = pinyin_file.readLine();           //读取一行
        ret = regExp.indexIn(QString(data.data()),0,QRegExp::CaretAtZero);      //进行匹配，如果成功则返回index，不成功返回-1  ，data.data()是读取到的一行数据，返回值应该是匹配到的位置
        pinyin_map.insert(regExp.cap(1),QString(data.data()).left(ret)); //将mmap对象的成员初始化;key是字母，value是行字
//        qDebug()<<pinyin_map;
    }
}
SyszuxPinyin::~SyszuxPinyin()
{
}
void SyszuxPinyin::initGb()
{
    //创建QPalette对象
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0xFF,0xFF,0xFF));        //009ad6  464547

    QPushButton *pushButton=new QPushButton(this);          //创建一个按钮对象
    pushButton->hide();                                     //按钮隐藏起来
    pushButton=pushButton_hanzi_left;                       //按钮指向pushButton_hanzi_left这个按钮的地址
    for(int i=1;i<67;i++)
    {
        //setFocusPolicy ( Qt::NoFocus )；
        pushButton->setAutoFillBackground(true);
        pushButton->setPalette(palette);
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setFlat(true);

        button_vector.push_back(pushButton);                //按钮集合，push_back（）～～ It is equivalent to append(value)，往按钮集合中添加一个按钮
        button_group->addButton(pushButton,i);              //添加一个按钮到button_group中，并且给按钮编号
        pushButton=qobject_cast<QPushButton *>(pushButton->nextInFocusChain());     //焦点指向下一个button
    }
    connect(button_group,SIGNAL(buttonClicked(int)),SLOT(buttonClickResponse(int)));    //连接button_group的点击信号，和本对象的buttonClickResponse函数，传递参数为按钮号
}
void SyszuxPinyin::buttonClickResponse(int gemfield)        //
{
    if(gemfield==1)                                         //按钮1是汉字向左移
    {
        selectHanziPre();                                   //page_count-1;
        return;
    }
    else if(gemfield==10)                                   //按钮10是汉字向右移
    {
        selectHanziNext();                                  //page_count+1;
        return;
    }
    else if(gemfield<10)                                    //按钮小于10,即显示汉字到按钮被点击了
    {
        lineEdit_window->insert(button_vector.at(gemfield-1)->text());  //将按钮上对应的值，设置到lineEdit_window到内容的后面
        lineEdit_pinyin->clear();                                       //清空lineEdit_pinyin内容
        clearString();                                      //清空显示汉字的按钮内容
        return;
    }
    else if(gemfield==23)                                   //backspace按钮被点击了
    {
        deleteString();                                     //删除数据
        return;
    }
    else if(gemfield==59)                                   //
    {
         changeLowerUpper();                                //设置大小写
         return;
    }

    //add by me
    else if(gemfield == 48 ){
        lineEdit_window->insert(lineEdit_pinyin->text());
        lineEdit_pinyin->clear();
        return;

    }

    else if(gemfield>10 && gemfield<=60)                    //如果点击到是字母的值
    {
        if(lower_upper)
            event=new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,syszux_upper_letter[gemfield-11]);  //如果是大写，则新建一个键盘事件，并带键值
        else
            event=new QKeyEvent(QEvent::KeyPress, 0, Qt::NoModifier,syszux_lower_letter[gemfield-11]);  //如果是小写，则新建一个键盘事件，并带键值
    }
    else if(gemfield==61)                                   //中文，英文切换按钮
    {
        changeInputMethod();                                //改变input_method的值，ENG和CH的切换
        return;
    }
    else if(gemfield==62)                                   //发送数据按钮
    {
        affirmString();                                     //发送数据函数
        return;
    }
    else if(gemfield>62)                                    //上下左右键
    {
        switch(gemfield)
        {
        case 63:
            event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);    //新建左键触发事件
            break;
        case 64:
            event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);    //新建下键触发事件
            break;
        case 65:
            event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);   //新建右键触发事件
            break;
        case 66:
            event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);      //新建上键触发事件
            break;
        }
    }
    if(input_method)                                        //如果是汉字输入
    {
        lineEdit_pinyin->setFocus();                        //lineEdit_pinyin则为焦点
        QApplication::sendEvent(focusWidget(),event);       //执行键盘事件
        matching(lineEdit_pinyin->text().toUtf8());                  //在8个汉字按钮上显示匹配到输入到引文对应的汉字
    }
    else
    {
        lineEdit_window->setFocus();                        //如果是英文输入模式，则将焦点设置为lineEdit_window
        QApplication::sendEvent(focusWidget(),event);       //执行键盘事件
    }
}
void SyszuxPinyin::matching(QString gemfield)   //根据用户输入的值，来匹配值
{
    pinyin_list = pinyin_map.values(gemfield);  //对pinyin_list进行初始化，根据用户输入的值，来初始化pinyin_list
    changePage(0);                              //设置8个汉字按钮的值
    page_count=0;                               //page_cout清零
}

void SyszuxPinyin::changePage(int index)        //肯定要接在matching后面
{
    int count = pinyin_list.size();             //获取到piyin_list的大小
    int i=index*8,j=0;
    while(++j != 9 )                            //
        button_vector.at(j)->setText(pinyin_list.value(count-(++i))); //从第j=1个按钮开始设置text，设置8八个按钮
    if(index==0)
        pushButton_hanzi_left->setEnabled(false);   //按钮不使能
    else
        pushButton_hanzi_left->setEnabled(true);    //按钮使能
    if(pinyin_list.size()>(index*8+8))
        pushButton_hanzi_right->setEnabled(true);   //设置为使能
    else
        pushButton_hanzi_right->setEnabled(false);  //设置为不使能
}
void SyszuxPinyin::selectHanziPre()             //向前移动
{
    changePage(--page_count);                   //改变页数，page_count的初始值为0
}

void SyszuxPinyin::selectHanziNext()            //向后移动
{
    changePage(++page_count);
}
void SyszuxPinyin::clearString()                //将显示汉字的按钮内容清空
{
    int i=0;
    while(++i!=9)
        button_vector.at(i)->setText("");       //全都设置为空字符串
}
void SyszuxPinyin::changeInputMethod()          //设置中英文按钮
{
    if(pushButton_shift->text()=="SHIFT")       //如果shift按钮是大写，则返回
        return;
   lineEdit_pinyin->clear();                    //否则，清空pinyin窗口内容
   if(pushButton_is_hanzi->text()=="Eng")       //如果原来是ENG
       input_method=1,pushButton_is_hanzi->setText("CH");   //则设置为CH
   else
       input_method=0,pushButton_is_hanzi->setText("Eng");  //否则设置为ENG
}
void SyszuxPinyin::changeLowerUpper()           //改变大小写
{
    if(pushButton_shift->text()=="shift")       //如果shift按钮是小写
    {
        lower_upper=1,pushButton_shift->setText("SHIFT");   //设置称大写
        input_method=0,pushButton_is_hanzi->setText("Eng"); //设置称英文模式
        int i=9;
        while(++i!=59)                                      //
            button_vector.at(i)->setText(syszux_upper_letter[i-10]);    //将11到59的按钮值设置为大写
    }
    else
    {
        lower_upper=0,pushButton_shift->setText("shift");   //设置为小写
        int i=9;
        while(++i!=59)
            button_vector.at(i)->setText(syszux_lower_letter[i-10]);    //将11到59到按钮值设置为小写
    }
}
void SyszuxPinyin::deleteString()               //
{
    event=new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);       //新建一个键盘事件
    if(input_method)                            //如果输入法为true，即为汉字
    {
        lineEdit_pinyin->text().isEmpty()?lineEdit_window->setFocus():lineEdit_pinyin->setFocus();  //判断lineEdit_pinyin是不是为空，若是，则将焦点定为lineEdit_window，否则lineEdit_pinyin
        QApplication::sendEvent(focusWidget(),event);       //发送一个键盘事件给焦点组件
        matching(lineEdit_pinyin->text());                  //重新匹配数据
    }
    else
    {
        lineEdit_window->setFocus();                        //英文
        QApplication::sendEvent(focusWidget(),event);
    }
}
void SyszuxPinyin::affirmString()
{
    emit sendPinyin(lineEdit_window->text());               //发送信号给界面
    lineEdit_window->clear();
    lineEdit_pinyin->clear();
    this->hide();
}




