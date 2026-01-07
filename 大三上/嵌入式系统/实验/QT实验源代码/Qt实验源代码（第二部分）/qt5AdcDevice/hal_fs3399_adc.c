#include "hal_fs3399_adc.h"

int voltage = 0;
int fd = 0;

#define DEVICE_DIR "/sys/bus/iio/devices/"
#define DEVICE_PREFIX "iio:"

int filter(const struct dirent *entry)
{
    return entry->d_type == DT_LNK && strncmp(entry->d_name,"iio:",4) == 0;
}

//打开节点
int adc_init()
{
    struct dirent **namelist;
    int n = scandir(DEVICE_DIR, &namelist, filter, alphasort);
    if (n < 0) {
        perror("scandir");
    }
    for (int i = 0; i < n; i++) {
        char device_path[1024];
        snprintf(device_path, sizeof(device_path), "/sys/bus/iio/devices/%s/in_voltage2_raw", namelist[i]->d_name);

        struct stat device_file_stat;
        if (stat(device_path, &device_file_stat) == 0) {
            //printf("IIO device with 'in_voltage_raw': %s\n", device_path);
            // 打开 ADC 设备文件描述符
            fd = open(device_path, O_RDWR);
            // 如果打开失败，打印错误信息
            if (fd < 0) {
                perror("open device");
            }else{
            }
        } else {
            printf("No 'in_voltage_raw' in device directory: %s\n", device_path);
        }
        free(namelist[i]);
    }
    free(namelist);
}

//选择通道读取数据
int read_sysfs_int(int val)
{
    adc_init();
    char data[20] = {0};
    int err = read(fd, data, sizeof(data));
    if (err > 0) {
        int num_data;
        int sscanf_result = atoi(data);
//            val = sscanf_result * 1.8;
            val = sscanf_result;
            usleep(1000000);
            return val;
    } else {
        return -1;
    }
    adc_close();
}

//在Run函数中读取数据
int Run()
{
    int data = 0;
    voltage = read_sysfs_int(data);
    //printf("vol:%d\n",voltage);
    return voltage;
}

int adc_close()
{
    return close(fd);
}


