#include "mythread.h"

MyThread::MyThread(QString openpath,QString savepath,QObject *parent) :
    QThread(parent)
{
    this->openpath = openpath;
    this->savepath = savepath;
}
void MyThread::run()
{
    int beforePre = 0;
    //判断源文件和目标文件地址是否存在
    if(openpath == "" || savepath == "")
    {
        //发射信号  提示弹窗
        emit messageBoxSignal();
    }
    else
    {
        //拷贝过程中关闭按钮
        emit progressBarSignal(0);
        emit btnUnAble();
        //创建QFile对象
        QFile fileread(openpath);
        fileread.open(QIODevice::ReadOnly);
        QFile filesave(savepath);
        filesave.open(QIODevice::WriteOnly);
        //创建字符数组 用了暂时存储
        QByteArray buf;
        qint64 totalSize = fileread.size();
        qint64 copySize =0;
        //循环读取
        while(!fileread.atEnd())
        {
            //读取
            buf = fileread.read(1024);
            //写出
            copySize += filesave.write(buf);
           double percent = 100 *copySize/totalSize;
           if(percent != beforePre)
           emit progressBarSignal(qCeil(percent));
            beforePre = percent;
        }
        emit messageBoxInfoSignal();
        emit btnAble();
        filesave.flush();
        filesave.close();
        fileread.close();
     }

}
