#include <jni.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <android/log.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define BUZZER_ON   _IO('b',1)
#define BUZZER_OFF  _IO('b',0)

int fd = 0;

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_buzzer_Buzzer_open(
        JNIEnv* env,
jobject /* this */) 
{
    fd = open("/dev/buzzer_ctl",O_RDWR);
    if (fd < 0) {
        __android_log_print(ANDROID_LOG_INFO, "serial", "open /dev/buzzer_ctl Error");
    }
    return fd;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_buzzer_Buzzer_BuzzerOn(
        JNIEnv* env,
        jobject /* this */) 
{
    ioctl(fd, BUZZER_ON);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_buzzer_Buzzer_BuzzerOff(
        JNIEnv* env,
        jobject /* this */) 
{
    ioctl(fd, BUZZER_OFF);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_buzzer_Buzzer_close(
        JNIEnv* env,
        jobject /* this */) 
{
    if (fd > 0) 
    {
        close(fd);
    }
    return 0;
}