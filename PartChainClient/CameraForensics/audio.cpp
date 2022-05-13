#include "audio.h"
#include <QLayout>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QCoreApplication>
#include "Common/common.h"
#include <QTextCodec>

#define BufferSize 14096
QString pAudioName;

struct HEADER
{
    char RIFFNAME[4];
    unsigned long nRIFFLength;
    char WAVNAME[4];
    char FMTNAME[4];
    unsigned long nFMTLength;
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned long nSampleRate;
    unsigned long nBytesPerSecond;
    unsigned short nBytesPerSample;
    unsigned short    nBitsPerSample;
    char    DATANAME[4];
    unsigned long   nDataLength;
};

Audio::Audio()
{

}

Audio::~Audio()
{

}

void Audio::AudioInit(QString m_filePath)
{
    mpOutputFile = NULL;
    mpAudioInputFile = NULL;
    mpAudioOutputFile = NULL;

    mpAudioInputSound = NULL;
    mpAudioOutputSound = NULL;

    mpInputDevSound = NULL;
    mpInputDevSound = NULL;

    QString filePath = m_filePath;
    QString audioName = filePath + "record.raw";
    Common *pcom = NULL;
    pcom->isDirExist(filePath);
    //qDebug() << filePath;

    mpOutputFile = new QFile(filePath);
    mpOutputFile->setFileName(audioName);

    //mFormatFile.setFrequency(8000);
    //mFormatFile.setChannels(1);
    mFormatFile.setSampleSize(16);
    mFormatFile.setSampleType(QAudioFormat::SignedInt);
    mFormatFile.setByteOrder(QAudioFormat::LittleEndian);
    mFormatFile.setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(mFormatFile)) {
        qWarning("input default mFormatFile not supported try to use nearest");
        mFormatFile = info.nearestFormat(mFormatFile);
    }

    QAudioDeviceInfo info1(QAudioDeviceInfo::defaultOutputDevice());
    if (!info1.isFormatSupported(mFormatFile)) {
        qWarning() << "output default mFormatFile not supported - trying to use nearest";
        //           mFormatFile = info.nearestFormat(mFormatSound);
        qWarning() << "output no support input mFormatFile.";
        return;
    }

    if(mFormatFile.sampleSize() != 16) {
//        qWarning("audio device doesn't support 16 bit support %d bit samples, example cannot run",
//                    <span style="white-space:pre">		</span>mFormatFile.sampleSize());

        mpAudioInputFile = 0;
        return;
    }

    mpAudioInputFile = NULL;
    mpAudioOutputFile = NULL;

    InitMonitor();
}

void Audio::OnRecordStart(int type)
{
    mpOutputFile->open(QIODevice::WriteOnly | QIODevice::Truncate);
    mpAudioInputFile = new QAudioInput(mFormatFile, this);
    if(type != 2)
    {//拍摄取证不带录音功能
        mpAudioInputFile->start(mpOutputFile);
    }

    qDebug() << "OnRecordStart.";
}

void Audio::OnRecordSave(QString m_filePath)
{
    QString filePath = m_filePath;
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    QString filePathName = "Audio-" + getTime + ".wav";
    QString fileFullPathName = filePath + filePathName;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QByteArray fullPath = fileFullPathName.toLocal8Bit();
    char* strFullPath = fullPath.data();
    AddWavHeader(strFullPath, filePath);
    //AddWavHeader(fileFullPathName.toLatin1().data(), filePath);

    qDebug() << "OnRecordSave.";
    pAudioName = filePathName;

    mpOutputFile->close();
    mpAudioInputFile->stop();
}

void Audio::InitMonitor()
{
    mFormatSound.setSampleSize(16); //set sample sze to 16 bit
    mFormatSound.setSampleType(QAudioFormat::UnSignedInt ); //Sample type as usigned integer sample
    mFormatSound.setByteOrder(QAudioFormat::LittleEndian); //Byte order
    mFormatSound.setCodec("audio/pcm"); //set codec as simple audio/pcm

    QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
    if (!infoIn.isFormatSupported(mFormatSound))
    {
        //Default format not supported - trying to use nearest
        mFormatSound = infoIn.nearestFormat(mFormatSound);
    }

    /*QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());
    if (!infoOut.isFormatSupported(mFormatSound))
    {
        //Default format not supported - trying to use nearest
        mFormatSound = infoOut.nearestFormat(mFormatSound);
    }*/

    CreateAudioInput();
    //CreateAudioOutput();

    //mpOutputDevSound = mpAudioOutputSound->start();
    mpInputDevSound = mpAudioInputSound->start();
    //connect(mpInputDevSound, SIGNAL(readyRead()), SLOT(OnReadMore()));
}

void Audio::CreateAudioInput()
{
    if (mpInputDevSound != 0) {
        disconnect(mpInputDevSound, 0, this, 0);
        mpInputDevSound = 0;
    }

    QAudioDeviceInfo inputDevice(QAudioDeviceInfo::defaultInputDevice());
    qDebug()<<"---device name:"<<inputDevice.deviceName();
    mpAudioInputSound = new QAudioInput(inputDevice, mFormatSound, this);
}

void Audio::CreateAudioOutput()
{
    QAudioDeviceInfo outputDevice(QAudioDeviceInfo::defaultOutputDevice());
    mpAudioOutputSound = new QAudioOutput(outputDevice, mFormatSound, this);
}

int Audio::AddWavHeader(char *filename, QString m_filePath)
{
    // 开始准备WAV的文件头
    HEADER DestionFileHeader;
    DestionFileHeader.RIFFNAME[0] = 'R';
    DestionFileHeader.RIFFNAME[1] = 'I';
    DestionFileHeader.RIFFNAME[2] = 'F';
    DestionFileHeader.RIFFNAME[3] = 'F';

    DestionFileHeader.WAVNAME[0] = 'W';
    DestionFileHeader.WAVNAME[1] = 'A';
    DestionFileHeader.WAVNAME[2] = 'V';
    DestionFileHeader.WAVNAME[3] = 'E';

    DestionFileHeader.FMTNAME[0] = 'f';
    DestionFileHeader.FMTNAME[1] = 'm';
    DestionFileHeader.FMTNAME[2] = 't';
    DestionFileHeader.FMTNAME[3] = 0x20;
    DestionFileHeader.nFMTLength = 16;  //  表示 FMT 的长度
    DestionFileHeader.nAudioFormat = 1; //这个表示a law PCM

    DestionFileHeader.DATANAME[0] = 'd';
    DestionFileHeader.DATANAME[1] = 'a';
    DestionFileHeader.DATANAME[2] = 't';
    DestionFileHeader.DATANAME[3] = 'a';
    DestionFileHeader.nBitsPerSample = 16;
    DestionFileHeader.nBytesPerSample = 2;    //
    DestionFileHeader.nSampleRate = 8000;    //
    DestionFileHeader.nBytesPerSecond = 16000;
    DestionFileHeader.nChannleNumber = 1;

    int nFileLen = 0;
    int nSize = sizeof(DestionFileHeader);

    FILE *fp_s = NULL;
    FILE *fp_d = NULL;

    QString filePath = m_filePath;
    QString audioName = filePath + "record.raw";

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
    QByteArray fullPath = audioName.toLocal8Bit();
    char* strAudioName = fullPath.data();

    //支持中文路径
    fp_s = fopen(strAudioName, "rb");
    //fp_s = fopen(audioName.toLatin1().data(), "rb");
    if (fp_s == NULL)
        return -1;

    fp_d = fopen(filename, "wb+");
    if (fp_d == NULL)
        return -2;


    int nWrite = fwrite(&DestionFileHeader, 1, nSize, fp_d);
    if (nWrite != nSize)
    {
        fclose(fp_s);
        fclose(fp_d);
        return -3;
    }

    while( !feof(fp_s))
    {
        char readBuf[4096];
        int nRead = fread(readBuf, 1, 4096, fp_s);
        if (nRead > 0)
        {
            fwrite(readBuf, 1, nRead, fp_d);
        }

        nFileLen += nRead;
    }
    fseek(fp_d, 0L, SEEK_SET);

    DestionFileHeader.nRIFFLength = nFileLen - 8 + nSize;
    DestionFileHeader.nDataLength = nFileLen;
    nWrite = fwrite(&DestionFileHeader, 1, nSize, fp_d);
    if (nWrite != nSize)
    {
        fclose(fp_s);
        fclose(fp_d);
        return -4;
    }

    fclose(fp_s);
    fclose(fp_d);
    fp_s = NULL;
    fp_d = NULL;
    return nFileLen;
}

void Audio::OnReadMore()
{
    //Return if audio input is null
    if(!mpAudioInputSound)
        return;

    QByteArray _Buffer(BufferSize, 0);
    //Check the number of samples in input buffer
    qint64 len = mpAudioInputSound->bytesReady();

    //Limit sample size
    if(len > 4096)
        len = 4096;

    //Read sound samples from input device to buffer
    qint64 l = mpInputDevSound->read(_Buffer.data(), len);
    if(l > 0) {
        //Assign sound samples to short array
        short* resultingData = (short*)_Buffer.data();

        short *outdata=resultingData;
        outdata[ 0 ] = resultingData [ 0 ];

        int iIndex;
        if(false) {
            //Remove noise using Low Pass filter algortm[Simple algorithm used to remove noise]
            for ( iIndex=1; iIndex < len; iIndex++ ) {
                outdata[ iIndex ] = 0.333 * resultingData[iIndex ] + ( 1.0 - 0.333 ) * outdata[ iIndex-1 ];
            }
        }

        for ( iIndex=0; iIndex < len; iIndex++ ) {
            //Cange volume to each integer data in a sample
            int value = ApplyVolumeToSample( outdata[ iIndex ]);
            outdata[ iIndex ] = value;
        }

        //write modified sond sample to outputdevice for playback audio
        mpOutputDevSound->write((char*)outdata, len);
    }
}


int Audio::ApplyVolumeToSample(short iSample)
{
    //Calculate volume, Volume limited to  max 30000 and min -30000
    //return std::max(std::min(((iSample * miVolume) / 50) ,20000), -20000);
    return 0;
}
