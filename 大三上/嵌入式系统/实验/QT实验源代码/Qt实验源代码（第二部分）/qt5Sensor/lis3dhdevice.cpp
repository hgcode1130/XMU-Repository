#include "lis3dhdevice.h"
#include <QDebug>

#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <QString>
#include <QDebug>

#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <unistd.h>

Lis3dhDevice::Lis3dhDevice()
{

}

Lis3dhDevice::~Lis3dhDevice()
{

}

int Lis3dhDevice::filter(const dirent *entry)
{
    // 只返回包含 "in_accel" 的设备
    return entry->d_type == DT_LNK && strncmp(entry->d_name, "iio:", 4) == 0;
}

int Lis3dhDevice::openAccelDeviceXYZ(int &adcxfd_x, int &adcxfd_y, int &adcxfd_z, QString function) {
    struct dirent **namelist;
    int n = scandir("/sys/bus/iio/devices/", &namelist, filter, alphasort);
    if (n < 0) {
        perror("scandir");
        return -1;
    }

    bool x_opened = false, y_opened = false, z_opened = false;

    for (int i = 0; i < n; i++) {
        char device_path[1024];

        // 根据function参数决定打开哪个轴的设备文件
        if (function.compare("X") == 0 && !x_opened) {
            snprintf(device_path, sizeof(device_path), "/sys/bus/iio/devices/%s/in_accel_x_raw", namelist[i]->d_name);
            x_opened = true;
        } else if (function.compare("Y") == 0 && !y_opened) {
            snprintf(device_path, sizeof(device_path), "/sys/bus/iio/devices/%s/in_accel_y_raw", namelist[i]->d_name);
            y_opened = true;
        } else if (function.compare("Z") == 0 && !z_opened) {
            snprintf(device_path, sizeof(device_path), "/sys/bus/iio/devices/%s/in_accel_z_raw", namelist[i]->d_name);
            z_opened = true;
        } else {
            continue; // 如果不需要打开当前轴的设备文件，则跳过
        }

        // Check if the device file exists using stat
        struct stat device_file_stat;
        if (stat(device_path, &device_file_stat) == 0) {
            // 打开设备文件描述符
            int adcfd = open(device_path, O_RDWR);

            // 如果打开失败，打印错误信息
            if (adcfd < 0) {
                perror("open device");
                return -1;
            } else {
                // 根据function参数决定将文件描述符赋值给哪个变量
                if (function.compare("X") == 0) {
                    adcxfd_x = adcfd;
                } else if (function.compare("Y") == 0) {
                    adcxfd_y = adcfd;
                } else if (function.compare("Z") == 0) {
                    adcxfd_z = adcfd;
                }
            }
        } else {
            return -1;
        }
        free(namelist[i]);
    }
    free(namelist);
    return 0;
}

int Lis3dhDevice::readDeviceValue(int fd, QString &value)
{
    char buffer[64];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0'; // 确保字符串以空字符结尾
        value = QString(buffer);
        return 0; // 成功读取
    } else {
        return -1; // 读取失败
    }
}

int Lis3dhDevice::readAccelValues(int adcxfd_x, int adcxfd_y, int adcxfd_z)
{
    QString value_x, value_y, value_z;

    // 读取x轴的值
    if (readDeviceValue(adcxfd_x, value_x) == 0) {
        //qDebug() << "X-axis value: " << value_x;
        xValue = value_x;
    } else {
        perror("Failed to read X-axis value");
        return -1;
    }

    // 读取y轴的值
    if (readDeviceValue(adcxfd_y, value_y) == 0) {
        //qDebug() << "Y-axis value: " << value_y ;
        yValue = value_y;
    } else {
        perror("Failed to read Y-axis value");
        return -1;
    }

    // 读取z轴的值
    if (readDeviceValue(adcxfd_z, value_z) == 0) {
        //qDebug() << "Z-axis value: " << value_z ;
        zValue = value_z;
    } else {
        perror("Failed to read Z-axis value");
        return -1;
    }

    // 关闭文件描述符
    close(adcxfd_x);
    close(adcxfd_y);
    close(adcxfd_z);
    return 0;
}

void Lis3dhDevice::run()
{
    runningState = true;
    while(runningState){
        int adcxfd_x, adcxfd_y, adcxfd_z;
        // 假设openAccelDeviceXYZ已经成功打开了设备文件描述符
        int xret = openAccelDeviceXYZ(adcxfd_x, adcxfd_y, adcxfd_z, "X");
        int yret = openAccelDeviceXYZ(adcxfd_x, adcxfd_y, adcxfd_z, "Y");
        int zret = openAccelDeviceXYZ(adcxfd_x, adcxfd_y, adcxfd_z, "Z");
        if(xret < 0 || yret < 0 || zret < 0){
            emit stopthread();
            return;
        }else{
            // 读取x、y、z的值
            readAccelValues(adcxfd_x, adcxfd_y, adcxfd_z);
            if(yValue.toInt() > 700){
                emit change180();
            }else{
                emit change0();
            }
        }
    }
}

void Lis3dhDevice::changeRunningState(bool state)
{
    runningState = state;
}
