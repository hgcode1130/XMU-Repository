#include "temdevice.h"  // 包含 temDevice 类的定义

// 构造函数
temDevice::temDevice(QObject *parent) : QObject(parent)
{
}

// 打开温度设备
void temDevice::openTemDevice()
{
    temfd=open("/dev/i2c-4",O_RDWR);
        if(temfd < 0)
        {
            perror("open error");
        }
}

// 读取温度数据
void temDevice::readData()
{
    openTemDevice();
    int ret = 0;
    struct i2c_rdwr_ioctl_data lm75_data;
    short temp_val = 0;
    lm75_data.nmsgs=2;
        lm75_data.msgs=(struct i2c_msg*)malloc(lm75_data.nmsgs*sizeof(struct i2c_msg));
        if(!lm75_data.msgs)
        {
            perror("malloc error");
            exit(1);
        }
        ioctl(temfd,I2C_TIMEOUT,1);/*超时时间*/
        ioctl(temfd,I2C_RETRIES,2);/*重复次数*/
        sleep(1);
    while(isTemRunning){  // 在设备运行标志为真的情况下持续运行
                lm75_data.nmsgs=2;
                (lm75_data.msgs[0]).len=1; //lm75 目标数据的地址
                (lm75_data.msgs[0]).addr=0x4f; // lm75 设备地址
                (lm75_data.msgs[0]).flags=0;//write
                (lm75_data.msgs[0]).buf=(unsigned char*)malloc(2);
                (lm75_data.msgs[0]).buf[0]=0x0;//lm75数据地址
                (lm75_data.msgs[1]).len=2;//读出的数据
                (lm75_data.msgs[1]).addr=0x4f;// lm75 设备地址
                (lm75_data.msgs[1]).flags=I2C_M_RD;//read
                (lm75_data.msgs[1]).buf=(unsigned char*)malloc(2);//存放返回值的地址。
                (lm75_data.msgs[1]).buf[0]=0;//初始化读缓冲
                (lm75_data.msgs[1]).buf[1]=0;//初始化读缓冲
                ret=ioctl(temfd,I2C_RDWR,(unsigned long)&lm75_data);
                if(ret < 0)
                {
                    perror("ioctl error2");
                    return;
                }

                temp_val = (lm75_data.msgs[1]).buf[0] << 8 | (lm75_data.msgs[1]).buf[1];

                if(temp_val >> 15)
                    temp_val = (~(temp_val - 0x80) >> 7);
                else
                    temp_val = temp_val >> 7;

                printf("temp =  %01f\n", (float)temp_val / 2);
                emit sendData((float)temp_val / 2);  // 发送转换后的温度值
                usleep(100000);  // 暂停100毫秒，减少CPU占用
    }
    closeTemFd();
}

// 更改温度设备的运行状态
void temDevice::changeThreadState(bool state)
{
    isTemRunning = state;  // 设置温度设备的运行状态
}

// 关闭温度设备
void temDevice::closeTemFd()
{
    close(temfd);  // 关闭与温度设备关联的文件描述符
}
