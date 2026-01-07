#include "mixadcdevice.h"

int mixAdcDevice::filter(const dirent *entry)
{
    return entry->d_type == DT_LNK && strncmp(entry->d_name, "iio:", 4) == 0;
}

// 构造函数，创建 mixAdcDevice 实例时调用
mixAdcDevice::mixAdcDevice(QObject *parent) : QObject(parent)
{
}

// 打开 ADC 设备文件描述符
void mixAdcDevice::openAdcDevice(QString function)
{
    struct dirent **namelist;
    int n = scandir("/sys/bus/iio/devices/", &namelist, filter, alphasort);
    if (n < 0) {
        perror("scandir");
    }

    for (int i = 0; i < n; i++) {
        char device_path[1024];
        if(function.compare("A") == 0){
            snprintf(device_path, sizeof(device_path), "/sys/bus/iio/devices/%s/in_voltage4_raw", namelist[i]->d_name);
        }else if(function.compare("F") == 0){
            snprintf(device_path, sizeof(device_path), "/sys/bus/iio/devices/%s/in_voltage3_raw", namelist[i]->d_name);
        }else if(function.compare("S") == 0){
            snprintf(device_path, sizeof(device_path), "/sys/bus/iio/devices/%s/in_voltage0_raw", namelist[i]->d_name);
        }else if(function.compare("L") == 0){
            snprintf(device_path, sizeof(device_path), "/sys/bus/iio/devices/%s/in_voltage3_raw", namelist[i]->d_name);
        }

        // Check if 'in_voltage2_raw' exists using stat
        struct stat device_file_stat;
        if (stat(device_path, &device_file_stat) == 0) {
            qDebug()<<"IIO device with 'in_voltage_raw': "<<device_path;
            // 打开 ADC 设备文件描述符
            adcfd = open(device_path, O_RDWR);
            qDebug()<<"device_path"<<device_path;
            // 如果打开失败，打印错误信息
            if (adcfd < 0) {
                perror("open device");
            }else{
                qDebug()<<"device openning";
            }
        } else {
            qDebug()<<"No 'in_voltage_raw' in device directory:  "<< device_path;
        }

        free(namelist[i]);
    }

    free(namelist);
}


// 读取 ADC 设备的数据
void mixAdcDevice::readData(QString function)
{
    closeAdcFd();
   // isAdcRunning = true;
    // 只要 ADC 正在运行，就一直读取数据
    while (isAdcRunning) {
        //qDebug()<<"Function"<<function;
        // 存储读取到的数据
        unsigned char data[20];
        // 初始化新数据为 0
        int newdata = 0;
        openAdcDevice(function);
        // 从 ADC 设备文件描述符中读取数据
        int err = read(adcfd, &data, sizeof(data));
//         qDebug()<<"data"<<data;
//         qDebug()<<"adcfd"<<adcfd;
        if(err > 0){
            int i = 0;
            for(i = 0; i < err; i++){
                if(data[i] >= '0' && data[i] <= '9'){
                    newdata = newdata*10 + (data[i] - 48);
                }
            }

        }else{
            qDebug()<<"read failed err:"<<err;
        }
        int senddata = newdata * 3.8;
//        qDebug()<<"sendData"<<senddata;
        emit sendData(senddata);
        QThread::usleep(500000);
        closeAdcFd();
    }
}

// 改变线程状态，用于控制读取数据的线程是否运行
void mixAdcDevice::changeThreadState(bool state)
{
    // 设置 ADC 是否正在运行的标志位
    isAdcRunning = state;
}

// 关闭 ADC 设备文件描述符
void mixAdcDevice::closeAdcFd()
{
    // 关闭 ADC 设备文件描述符
    close(adcfd);
    adcfd = 0;
}
