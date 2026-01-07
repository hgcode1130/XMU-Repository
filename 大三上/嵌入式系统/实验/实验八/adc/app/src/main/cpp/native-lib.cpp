#include <jni.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <android/log.h>
#include <unistd.h>

int fd = 0; // �ļ������������ڲ���ADC�豸
int data = 0; // ��ȡ��ԭʼ����

// ��ADC�豸
extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_temperature_adc_open(JNIEnv* env, jobject /* this */) {
    // ��ADC�豸�ļ�
    fd = open("/sys/bus/iio/devices/iio:device0/in_voltage2_raw", O_RDONLY); // �滻ΪADC·��
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_INFO, "adc", "open ADC device Error");
    } else {
        __android_log_print(ANDROID_LOG_INFO, "adc", "open ADC device success");
    }
    return 0;
}

// ��ȡADC����
extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_temperature_adc_read(JNIEnv* env, jobject /* this */) {
    char buffer[16]; // ���ڴ洢��ȡ���ַ�������
    lseek(fd, 0, SEEK_SET); // �����ļ�ƫ����
    read(fd, buffer, sizeof(buffer)); // ���豸�ļ���ȡ����
    data = atoi(buffer); // ת��Ϊ����
    __android_log_print(ANDROID_LOG_INFO, "adc", "ADC Value: %d", data);
    return data; // ����ADCֵ
}

// �ر�ADC�豸
extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_temperature_adc_close(JNIEnv* env, jobject /* this */) {
    if (fd > 0) {
        close(fd); // �ر��豸
        __android_log_print(ANDROID_LOG_INFO, "adc", "close ADC device success");
    }
    return 0;
}
