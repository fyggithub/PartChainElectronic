#ifndef AUDIO_H
#define AUDIO_H

#include <QWidget>
#include <QFile>
#include <QPushButton>
#include <QAudioInput>
#include <QAudioOutput>
#include <QAudioDeviceInfo>

class Audio : public QWidget
{
    Q_OBJECT
public:
    Audio();
    ~Audio();

signals:

private:
    int AddWavHeader(char * ,QString m_filePath);
    int ApplyVolumeToSample(short iSample);
    void InitMonitor();
    void CreateAudioInput();
    void CreateAudioOutput();

private slots:
    void OnReadMore();

public:
    void AudioInit(QString m_filePath);
    void OnRecordStart(int type);
    void OnRecordSave(QString m_filePath);

private:
    QAudioFormat mFormatFile;
    QFile *mpOutputFile;

    QAudioInput *mpAudioInputFile;		// 负责读写文件
    QAudioOutput *mpAudioOutputFile;

    QAudioFormat mFormatSound;
    QAudioInput *mpAudioInputSound;		// 负责监听声音
    QAudioOutput *mpAudioOutputSound;

    QIODevice *mpInputDevSound;
    QIODevice *mpOutputDevSound;

};

extern QString pAudioName;

#endif // AUDIO_H
