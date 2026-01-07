#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H


#include <QObject>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFile>
#include <alsa/asoundlib.h> // 包含ALSA库头文件
#include <QDateTime>
#include <QDebug>
#include <QTimer>

// AudioRecorder类定义
class AudioRecorder : public QObject
{
    Q_OBJECT // 声明这是一个Qt对象，以便使用信号和槽机制

public:
    // 构造函数
    explicit AudioRecorder(QObject *parent = nullptr);

    // 析构函数
    ~AudioRecorder();

    // 获取录音文件的完整路径
    QString getPathName();

    // 获取录音文件的目录路径
    QString getPath();

    // 获取录音经过的时间
    QString getElapsedRecordingTime();

    // 更改录音文件保存的路径
    void changePath(QString path);

    // 开始录音，指定音频格式
    void startRecording(QString audioFormat);

    // 停止录音
    void stopRecording();

    // 开始播放指定文件名的音频文件
    void startPlaying(QString playFileName);

    // 停止播放
    void stopPlaying();

private:
    // 定时器，用于记录录音时间
    QTimer *timer = nullptr;

    // 开始录音的时间
    QTime startTime;

    // 当前时间
    QTime currentTime;

    // 录音文件路径
    QString filePath;

    // 录音文件名
    QString filename;

    // 捕获PCM设备句柄
    snd_pcm_t *capture_handle = nullptr;

    // 播放PCM设备句柄
    snd_pcm_t *playback_handle = nullptr;

    // 音频格式
    snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

    // 是否正在录音
    bool isRecording = false;

    // 是否正在播放
    bool isPlaying = false;

signals:
    // 播放结束信号
    void playEnd();
};
#endif
