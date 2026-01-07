#include "audiorecorder.h"

AudioRecorder::AudioRecorder(QObject *parent) : QObject(parent) {
    // 构造函数，初始化成员变量
}

// 析构函数
AudioRecorder::~AudioRecorder()
{
    // 如果正在录音，停止录音
    if (isRecording) stopRecording();
    // 如果正在播放，停止播放
    if (isPlaying) stopPlaying();
    // 如果存在捕获句柄，关闭它
    if (capture_handle) snd_pcm_close(capture_handle);
    // 如果存在播放句柄，关闭它
    if (playback_handle) snd_pcm_close(playback_handle);
}

// 返回录音文件的完整路径
QString AudioRecorder::getPathName()
{
    return filename;
}

// 返回录音文件的目录路径
QString AudioRecorder::getPath()
{
    return filePath;
}

// 返回录音经过的时间
QString AudioRecorder::getElapsedRecordingTime()
{
    currentTime = QTime::currentTime();
    int elapsedMsecs = startTime.msecsTo(currentTime);
    //qDebug()<<"startTime"<<startTime<<"currentTime"<<currentTime<<"elapsedMsecs"<<elapsedMsecs;
    int elapsedSeconds = elapsedMsecs / 1000;
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    QString formattedTime = QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0')).arg(seconds, 2, 10, QLatin1Char('0'));
    return formattedTime;
}

void AudioRecorder::changePath(QString path)
{
    // 更改录音文件保存的路径
    filePath = path;
}

// 开始录音
void AudioRecorder::startRecording(QString audioFormat)
{
    // 如果已经在录音，则直接返回
    if (isRecording) return;
    startTime = QTime::currentTime();
    // 打开ALSA捕获句柄
    if (snd_pcm_open(&capture_handle, "default", SND_PCM_STREAM_CAPTURE, 0) < 0) {
        qDebug() << "Error opening capture handle"; // 打开捕获句柄失败，输出错误信息
        return;
    }
    // 设置参数，如格式、通道数、采样率等
    if (snd_pcm_set_params(capture_handle, format, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 500000) < 0) {
        qDebug() << "Error setting capture parameters"; // 设置捕获参数失败，输出错误信息
        snd_pcm_close(capture_handle);
        capture_handle = nullptr;
        return;
    }
    // 生成文件名和时间戳
    QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd_hh_mm_ss");
    QString dir("/home/linux/Videos");
    filePath = QString("%1/%2.%3").arg(dir).arg(timeStr).arg(audioFormat);
    changePath(filePath);
    filename = QString("%1.%2").arg(timeStr).arg(audioFormat);
    QFile file(filePath);
    // 打开文件以写入
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening file for writing"; // 打开文件失败，输出错误信息
        snd_pcm_close(capture_handle);
        capture_handle = nullptr;
        return;
    }
    isRecording = true;
    qDebug() << "Recording started"; // 录音开始，输出信息
    while (isRecording) {
        char buffer[128];
        // 从捕获句柄读取数据
        int frames = snd_pcm_readi(capture_handle, buffer, sizeof(buffer) / 4);
        if (frames < 0) {
            qDebug() << "Error reading from capture handle"; // 读取失败，输出错误信息
            break;
        }
        file.write(buffer, frames * 4);
    }
    file.close();
    // 关闭捕获句柄
    snd_pcm_close(capture_handle);
    capture_handle = nullptr;
}

// 停止录音
void AudioRecorder::stopRecording()
{
    // 如果不在录音，则直接返回
    if (!isRecording) return;
    isRecording = false;
    while(isPlaying){
        QCoreApplication::processEvents(); // 等待结束
    }
    qDebug() << "Recording stopped"; // 录音停止，输出信息
}

// 开始播放
void AudioRecorder::startPlaying(QString playFileName)
{
    // 如果已经在播放，则直接返回
    if (isPlaying) return;
    qDebug()<<"playFileName"<<playFileName;
    startTime = QTime::currentTime();
    // 打开ALSA播放句柄
    if (snd_pcm_open(&playback_handle, "hw:0,0", SND_PCM_STREAM_PLAYBACK, 0) < 0) {
        qDebug() << "Error opening playback handle"; // 打开播放句柄失败，输出错误信息
        return;
    }

    // 设置句柄参数
    if (snd_pcm_set_params(playback_handle, format, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 500000) < 0) {
        qDebug() << "Error setting playback parameters";
        snd_pcm_close(playback_handle);
        playback_handle = nullptr;
        isPlaying = false;
        return;
    }

    QFile file(playFileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file for reading";
        snd_pcm_close(playback_handle);
        playback_handle = nullptr;
        isPlaying = false;
        return;
    }

    isPlaying = true;
    qDebug() << "Playback started";

    while (isPlaying) {
        char buffer[128];
        qint64 bytesRead = file.read(buffer, sizeof(buffer));
        if (bytesRead < 0) {
            qDebug() << "Error reading file";
            break;
        }else if(bytesRead == 0) {
            qDebug()<< "End of file" ;
            break;
        }

        int frames = bytesRead / 4;
        if (snd_pcm_writei(playback_handle, buffer, frames) < 0) {
            qDebug() << "Error writing to playback handle";
            break;
        }
    }

    file.close();
    snd_pcm_close(playback_handle);
    emit playEnd();
    playback_handle = nullptr;
    isPlaying = false;
}

// 停止播放
void AudioRecorder::stopPlaying()
{
    if (!isPlaying) return;
    isPlaying = false;
    qDebug() << "Playback stopped";
}
