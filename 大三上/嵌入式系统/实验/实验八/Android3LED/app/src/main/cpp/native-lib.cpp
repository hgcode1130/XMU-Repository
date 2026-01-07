#include <jni.h>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <android/log.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define LED1_ON    _IO('y',1)
#define LED1_OFF   _IO('y',0)
#define LED2_ON    _IO('z',1)
#define LED2_OFF   _IO('z',0)
#define LED3_ON    _IO('x',1)
#define LED3_OFF   _IO('x',0)

int fd = 0;

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_led_LED_open(
        JNIEnv* env,
        jobject /* this */) 
{
    fd = open("/dev/leds_ctl", O_RDWR);
    if (-1 == fd) 
    {
        __android_log_print(ANDROID_LOG_INFO, "serial", "open /dev/leds_ctl Error");
    } 
    else 
    {
        __android_log_print(ANDROID_LOG_INFO, "serial", "open /dev/leds_ctl success");
    }
    return fd;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_led_LED_LedOn1(
        JNIEnv* env,
        jobject /* this */) 
{
    ioctl(fd, LED1_ON);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_led_LED_LedOff1(
        JNIEnv* env,
        jobject /* this */) 
{
    ioctl(fd, LED1_OFF);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_led_LED_LedOn2(
        JNIEnv* env,
        jobject /* this */) 
{
    ioctl(fd, LED2_ON);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_led_LED_LedOff2(
        JNIEnv* env,
        jobject /* this */) 
{
    ioctl(fd, LED2_OFF);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_led_LED_LedOn3(
        JNIEnv* env,
        jobject /* this */)
{
    ioctl(fd, LED3_ON);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_led_LED_LedOff3(
        JNIEnv* env,
        jobject /* this */)
{
    ioctl(fd, LED3_OFF);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL
Java_com_farsight_led_LED_close(
        JNIEnv* env,
        jobject /* this */) 
{
    close(fd);
    return 0;
}