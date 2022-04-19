#ifndef COMMON_H
#define COMMON_H

#include <QWidget>
#include <QDir>
#include <QCoreApplication>
#include <QNetworkInterface>

enum RecordType{
    WebRecord = 0,
    CameraRecord,
    VideoRecord,
    VideoRecordDialog,
    ScreenShotRecord
};

class Common
{
public:
    Common();
    ~Common();
    bool isDirExist(QString fullPath);
    QString ReadLog(void);
    QString FileDirPath(RecordType recordType);
    void WriteIpTrack(RecordType recordType, QString str);
    void WriteLog(RecordType recordType, QString fileName, QString str);
    void RemoveLog(RecordType recordType, QString fileName);
    void CommunicationWriteLog(QString str1,QString str2,QString str3);

    QString SetLogTimeFromat(void);
    void CreateForensicsLog(RecordType recordType, QString fileName);
    void StorageForensicsLog(RecordType recordType, const QString& fileName,const QString& str);
    void FromBaiDuJumpTime(RecordType recordType, QString fileName);
    void FromBaiDuJumpUrl(RecordType recordType, QString fileName, QString url);
    void WebJumpTime(RecordType recordType, QString fileName);
    void WebJumpUrl(RecordType recordType, QString fileName, QString url);
    void StartForensicsLog(RecordType recordType, QString fileName);
    void SaveForensicsLog(RecordType recordType, QString fileName);

    QString GetIpAddress();
    QString GetGateway(QString ip);
    void tests();
    void RemoveDirFile(QString &folderDir);
    void RemoveOverageFile(QString &filePathName);
    QString RenameLogFile(RecordType recordType, QString fileName);
    void RemoveScnLogFile(QString fileName);
    void RemoveWebLogFile(RecordType recordType,QString fileName);
    void RemoveFailFiles(RecordType recordType);
};

extern QString pGetJsToken,pGetJsUrl,pGetForensicsName,pGetNameNoTime,pGetHostIp,pGetDirPath;
extern QString pDownLoadFileName, pBatchSingle;
extern QString pIpAddress,pMacAddress,pOsVersion,pGateway;
extern int pRecordDialogFlag;

#endif // COMMON_H
