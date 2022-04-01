#include "En_Decrypt.h"
#include "sm4.h"
#include <QString>
#include <string.h>
#include <QDebug>
#include <fstream>
#include <QFile>
#include <QTextCodec>
#include "base64.h"
#include "Common/common.h"
#include "Common/logrecord.h"
#include <cstring>
#include "include/JlCompress.h"

#define BUFF_SIZE 256
#define MAXBUFFSIZE (100*1024*1024)

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

QList<QString> pList;
QMap<QString, QString> keyMap;
unsigned char BuffBase64[MAXBUFFSIZE] = {0};

SM4Decrypt::SM4Decrypt()
{

}
SM4Decrypt::~SM4Decrypt()
{

}

void SM4Decrypt::Decrypt_Test()
{
    //uint8_t keytest[17] = "1111111111111111";
    //unsigned char inputtest[9] = "12345678";
    unsigned char output[128] = {};
    //unsigned char key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98,0x76, 0x54, 0x32, 0x10};
    //unsigned char input[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98,0x76, 0x54, 0x32, 0x10};
    unsigned char key[16] = {0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31};
    unsigned char input[16] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};

    /*QString strKey = "1111111111111111";
    std::string strKey1 = strKey.toStdString();
    char *pStrKey = (char*)strKey1.c_str();
    unsigned char *pKey = reinterpret_cast<unsigned char*>(pStrKey);
    int num = strlen(pStrKey);
    for(int m = 0;m < num;m++)
    {
        //qDebug() << pStrKey[m] << pKey[m] << num;
        //qDebug() << pKey[m];
    }*/

    /*sm4_ctx ctx;
    sm4_set_key(key, &ctx);
    sm4_encrypt(input, output, &ctx);

    sm4_set_key(key, &ctx);
    sm4_decrypt(output, output, &ctx);

    qDebug() << "--------------";
    qDebug() << sizeof (int);
    char *pOuput = reinterpret_cast<char*>(output);
    int lenghOutput = strlen(pOuput);
    int strlen = pOuput[lenghOutput-1];
    int lengh = 0;
    if(strlen < 16)
    {
        lengh = lenghOutput - strlen;
    }
    else {
        lengh = lenghOutput;
    }

    for(int j = 0;j < lengh;j++)
    {
        qDebug() << output[j] << QString().sprintf("%02X",output[j]) << lenghOutput;
    }
    QString str = QString(QLatin1String(pOuput));
    qDebug() << "******";*/

    FILE *frin = NULL;
    FILE *frout = NULL;
    FILE *frout1 = NULL;
    frin = fopen("C:\\Users\\fyg\\Desktop\\U180.txt","rb");
    //frin = fopen("C:\\Users\\fyg\\Desktop\\UU.txt","rb");
    frout = fopen("C:\\Users\\fyg\\Desktop\\fyg.txt","wb+");
    //frout1 = fopen("C:\\Users\\fyg\\Desktop\\fyg1.txt","w+");
    sm4_ctx ctx;
    sm4_set_key(key, &ctx);
    sm4_encrypt_file(frin, frout, &ctx);
    fclose(frin);
    fclose(frout);
    //fclose(frout1);

    //sm4_ctx ctx;
    sm4_set_key(key, &ctx);
    //sm4_decrypt_file(frout, frout1, &ctx);
    sm4_decrypt_file_test(&ctx);

    /*sm4_ctx ctx;
    QString strEnc = "1234567812345678";
    sm4_set_key(key, &ctx);
    QString ret0 = sm4_encrypt_string(strEnc,&ctx);
    qDebug() << ret0;
    sm4_ctx ctx;
    QString ret0 = "8K5BHsLQSVxaOLnbKuuAOR0TQn4Q5mFQUwwqyZ31bCo=";
    sm4_set_key(key, &ctx);
    QString ret1 = sm4_decrypt_string(ret0,&ctx);
    qDebug() << ret1;
    qDebug() << "ok.";*/

    //sm4_ctx ctx;
    //sm4_set_key(key, &ctx);
    //QString kk = sm4_encrypt_string(&ctx);

    //sm4_set_key(key, &ctx);
    //sm4_decrypt_string(kk,&ctx);
}

QString SM4Decrypt::EncodeSM4_Base64(QString key,const QString strInput)
{
    unsigned char *szSM4 = new unsigned char[BUFF_SIZE];
    memset(szSM4, 0x0, BUFF_SIZE);
    unsigned char output[128] = {};

    std::string strkey1 = key.toStdString();
    char *pStrkey = (char*)strkey1.c_str();
    unsigned char *pkey = reinterpret_cast<unsigned char*>(pStrkey);

    std::string strInput1 = strInput.toStdString();
    char *pStrInput = (char*)strInput1.c_str();
    unsigned char *pIn = reinterpret_cast<unsigned char*>(pStrInput);

    sm4_ctx ctx;
    sm4_set_key(pkey, &ctx);
    sm4_encrypt(pIn, output, &ctx);

    int nCount = 0;
    char *szBase64 = new char[BUFF_SIZE];
    memset(szBase64, 0x0, BUFF_SIZE);

    Base64_Encode_New(output, strlen((char*)output), szBase64, nCount);
    //std::string strResult = szBase64;
    //qDebug() <<  QString::fromStdString(strResult);
    QString strResult = QString::fromStdString(szBase64);

    delete []szSM4;
    delete []szBase64;
    return strResult;
}

QString SM4Decrypt::DecodeSM4_Base64(const QString& key,const QString& strInput)
{
    qDebug()<<"DecodeSM4_Base641111111111111";
    long long nCount = 0;
    long long len = 0;
    len = strInput.length();
    LogRecord wLog;
    wLog.LogTrack(pDownLoadFileName);
    //wLog.LogTrack(strInput);
    qDebug()<<"len:"<<len;
    //unsigned char *szBase64 = new unsigned char[len];
    wLog.LogTrack("start memset.");
    //memset(szBase64, 0, len);
    memset(BuffBase64, 0, MAXBUFFSIZE);
    wLog.LogTrack("memset success.");

    //wLog.LogTrack("start base64 decode.");
    //单独定义变量传递，则程序会崩溃
    //Base64_Decode_New(qPrintable(strInput), len, szBase64, nCount);
    QByteArray ba = strInput.toLatin1();
    qDebug()<<"baaaaaaaaaaaaaaaaaaaa0";
    const char* base64_data = ba.data();
    qDebug()<<"baaaaaaaaaaaaaaaaaaaa1";
    Base64_Decode_New(base64_data, len, BuffBase64, nCount);

    wLog.LogTrack("base64 decode finish.");
    qDebug()<<"nCount:"<<nCount;

    qDebug()<<"DecodeSM4_Base642222222222222222";
    FILE *file_in = NULL;
    file_in = fopen(TEMPFILENAME,"wb+");
    //fwrite(szBase64, 1, nCount, file_in);
    fwrite(BuffBase64, 1, nCount, file_in);
    fclose(file_in);
    file_in = NULL;
    //delete [] szBase64;
    //szBase64 = nullptr;

    qDebug()<<"DecodeSM4_Base643333333333333333333333";
    const char *pStrkey = key.toLocal8Bit().constData();
    unsigned char *pkey = (unsigned char *)pStrkey;
    sm4_ctx ctx;
    sm4_set_key(pkey, &ctx);
    sm4_decrypt_file_test(&ctx);

    QString tmpFile = QString(QLatin1String(TEMPFILENAME));
    Common *pCommon = NULL;
    pCommon->RemoveOverageFile(tmpFile);

    QFile file(pDownLoadFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    //QByteArray encrypted_data = file.readAll().toBase64();
    //QTextStream stream(&encrypted_data);
    //stream.seek(0);//将当前读取文件指针移动到文件开始
    QString str = "";
    //str = stream.readAll();//为了节省通信时长，直接返回一个固定字符串
    str = "I5Zfz235g7H37KKdoE0ruVHKhBE/6yR99rDLQlbTC8u9pobmy325JBbmosjIljlKyzqkX9mbiysmW1zWzke0wBWlLZt364al2qXrQ6Ky9Ie2Jz9uu4rSeVYivmtR+WI9/XLhEAYr2MHrO/xSNEHPrQ==";
    qDebug()<<"ready end.";
    file.close();
    pList << pDownLoadFileName;
    wLog.LogTrack("decry is over.");
    return str;
}

QString SM4Decrypt::DecodeSM4_Base64Test(const QString& key,const char* strInput,int len)
{
    qDebug()<<"DecodeSM4_Base641111111111111";
    long long nCount = 0;
    LogRecord wLog;
    wLog.LogTrack(pDownLoadFileName);
    qDebug()<<"len:"<<len;
    wLog.LogTrack("start memset.");
    memset(BuffBase64, 0, MAXBUFFSIZE);
    wLog.LogTrack("memset success.");

    qDebug()<<"baaaaaaaaaaaaaaaaaaaa1";
    Base64_Decode_New(strInput, len, BuffBase64, nCount);
    wLog.LogTrack("base64 decode finish.");
    qDebug()<<"nCount:"<<nCount;

    qDebug()<<"DecodeSM4_Base642222222222222222";
    FILE *file_in = NULL;
    file_in = fopen(TEMPFILENAME,"wb+");
    fwrite(BuffBase64, 1, nCount, file_in);
    fclose(file_in);
    file_in = NULL;

    qDebug()<<"DecodeSM4_Base643333333333333333333333";
    const char *pStrkey = key.toLocal8Bit().constData();
    unsigned char *pkey = (unsigned char *)pStrkey;
    sm4_ctx ctx;
    sm4_set_key(pkey, &ctx);
    sm4_decrypt_file_test(&ctx);

    QString tmpFile = QString(QLatin1String(TEMPFILENAME));
    Common *pCommon = NULL;
    pCommon->RemoveOverageFile(tmpFile);

    pList << pDownLoadFileName;
    wLog.LogTrack("decry is over.");
    qDebug()<<"ready end.";
    return "";
}

QString SM4Decrypt::DecodeSM4_Base64Test2(const QString& key,const QByteArray& strInput)
{
    qDebug()<<"DecodeSM4_Base641111111111111";
    long long nCount = 0;
    long long len = 0;
    len = strInput.length();
    LogRecord wLog;
    wLog.LogTrack(pDownLoadFileName);
    //wLog.LogTrack(strInput);
    qDebug()<<"len:"<<len;
    //unsigned char *szBase64 = new unsigned char[len];
    wLog.LogTrack("start memset.");
    //memset(szBase64, 0, len);
    memset(BuffBase64, 0, MAXBUFFSIZE);
    wLog.LogTrack("memset success.");

    //wLog.LogTrack("start base64 decode.");
    //单独定义变量传递，则程序会崩溃
    //Base64_Decode_New(qPrintable(strInput), len, szBase64, nCount);
    //QByteArray ba = strInput;
    qDebug()<<"baaaaaaaaaaaaaaaaaaaa0";
    //const char* base64_data = strInput.data();
    qDebug()<<"baaaaaaaaaaaaaaaaaaaa1";
    Base64_Decode_New(strInput.data(), len, BuffBase64, nCount);

    wLog.LogTrack("base64 decode finish.");
    qDebug()<<"nCount:"<<nCount;

    qDebug()<<"DecodeSM4_Base642222222222222222";
    FILE *file_in = NULL;
    file_in = fopen(TEMPFILENAME,"wb+");
    //fwrite(szBase64, 1, nCount, file_in);
    fwrite(BuffBase64, 1, nCount, file_in);
    fclose(file_in);
    file_in = NULL;
    //delete [] szBase64;
    //szBase64 = nullptr;

    qDebug()<<"DecodeSM4_Base643333333333333333333333";
    const char *pStrkey = key.toLocal8Bit().constData();
    unsigned char *pkey = (unsigned char *)pStrkey;
    sm4_ctx ctx;
    sm4_set_key(pkey, &ctx);
    sm4_decrypt_file_test(&ctx);

    QString tmpFile = QString(QLatin1String(TEMPFILENAME));
    Common *pCommon = NULL;
    pCommon->RemoveOverageFile(tmpFile);

    QFile file(pDownLoadFileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    //QByteArray encrypted_data = file.readAll().toBase64();
    //QTextStream stream(&encrypted_data);
    //stream.seek(0);//将当前读取文件指针移动到文件开始
    QString str = "";
    //str = stream.readAll();//为了节省通信时长，直接返回一个固定字符串
    str = "I5Zfz235g7H37KKdoE0ruVHKhBE/6yR99rDLQlbTC8u9pobmy325JBbmosjIljlKyzqkX9mbiysmW1zWzke0wBWlLZt364al2qXrQ6Ky9Ie2Jz9uu4rSeVYivmtR+WI9/XLhEAYr2MHrO/xSNEHPrQ==";
    qDebug()<<"ready end.";
    file.close();
    pList << pDownLoadFileName;
    wLog.LogTrack("decry is over.");
    return str;
}

QString SM4Decrypt::DecodeSM4_StreamTest(const QStringList& key,const QStringList& fileNameList,const char* strInput,int len)
{
    qDebug()<<"DecodeSM4_Base641111111111111";
    LogRecord wLog;
    wLog.LogTrack("start write download file become to zip file.");
//    FILE *file_in = NULL;
//    file_in = fopen(TEMPFILEZIPNAME,"wb+");
//    fwrite(strInput, 1, len, file_in);
//    fclose(file_in);
//    file_in = NULL;
    wLog.LogTrack("write download file become to zip file over.");

    QString tmpCompressName = QCoreApplication::applicationDirPath() + "/tmp";
    JlCompress::extractDir(TEMPFILEZIPNAME,tmpCompressName);
    QDir dir(tmpCompressName);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())
    {
        wLog.LogTrack("JlCompress::extractDir fail, dir no exists!");
        qDebug()<<"dir no exists.";
        return "";   //文件不存，则返回false
    }
    fileList = dir.entryInfoList(QDir::Dirs | QDir::Files \
                               |QDir::Readable|QDir::Writable \
                               |QDir::Hidden|QDir::NoDotAndDotDot \
                               ,QDir::Name);
    wLog.LogTrack("JlCompress::extractDir success.");
    if(fileList.size() > 0)
    {
        int infoNum = fileList.size();
        QString strPath = "";
        QStringList RecvfilesList;
        for(int i = infoNum - 1; i >= 0; i--)
        {
            curFile = fileList[i];
            qDebug()<<curFile.filePath();
            fileList.removeAt(i);
            strPath = curFile.filePath();

            QString tmpKey,tmpFileName;
            for(QMap<QString,QString>::ConstIterator ite=keyMap.constBegin(); ite!=keyMap.constEnd(); ++ite)
            {
                //qDebug()<<ite.key()<<": "<<ite.value();
                bool temp = strPath.contains(ite.key(), Qt::CaseInsensitive);
                if(temp == true){
                    tmpKey = ite.value();
                    for(int j = 0; j < key.size(); ++j){
                            if(key.at(j) == tmpKey){
                                tmpFileName = fileNameList.at(j);
                                break;
                            }
                    }
                    break;
                }
            }
            qDebug()<<tmpKey<<tmpFileName;
            RecvfilesList << tmpFileName;

            const char *pStrkey = tmpKey.toLocal8Bit().constData();
            unsigned char *pkey = (unsigned char *)pStrkey;
            sm4_ctx ctx;
            sm4_set_key(pkey, &ctx);
            sm4_decrypt_file_test2(&ctx,curFile.filePath(),tmpFileName);
        }

        if(pBatchSingle == "batch"){
            JlCompress::compressFiles(BatchCompressFileName, RecvfilesList);
            for(int i = 0; i < RecvfilesList.size(); ++i){
                Common *pCommon = NULL;
                QString getName = RecvfilesList.at(i);
                pCommon->RemoveOverageFile(getName);
            }
            pDownLoadFileName = BatchCompressFileName;
        }
        else{
            pDownLoadFileName = RecvfilesList.at(0);
        }
        RecvfilesList.clear();
    }

    QString tmpFile = QString(QLatin1String(TEMPFILEZIPNAME));
    Common *pCommon = NULL;
    pCommon->RemoveOverageFile(tmpFile);
    pCommon->RemoveDirFile(tmpCompressName);

    qDebug()<<"ready end.";
    return "";
}

QString SM4Decrypt::DecodeSM4_CertificateStreamTest(const QStringList& key,const QStringList& fileNameList)
{
    LogRecord wLog;
    wLog.LogTrack("start DecodeSM4 Certificate.");
    QString tmpKey = key.at(0);
    QString tmpFileName = fileNameList.at(0);
    qDebug() << tmpKey << tmpFileName;

    const char *pStrkey = tmpKey.toLocal8Bit().constData();
    unsigned char *pkey = (unsigned char *)pStrkey;
    sm4_ctx ctx;
    sm4_set_key(pkey, &ctx);
    sm4_decrypt_file_test2(&ctx,TEMPFILENAME,tmpFileName);
    pDownLoadFileName = tmpFileName;
    QString tmpFile = QString(QLatin1String(TEMPFILENAME));
    Common *pCommon = NULL;
    pCommon->RemoveOverageFile(tmpFile);
    qDebug()<<"ready end.";
    return "";
}

QString SM4Decrypt::DecodeSM4_DetailStreamTest(const QStringList& key,const QStringList& fileNameList)
{
    LogRecord wLog;
    wLog.LogTrack("start DecodeSM4 Detail.");
    QString tmpKey = key.at(0);
    QString tmpFileName = fileNameList.at(0);
    qDebug() << tmpKey << tmpFileName;

    const char *pStrkey = tmpKey.toLocal8Bit().constData();
    unsigned char *pkey = (unsigned char *)pStrkey;
    sm4_ctx ctx;
    sm4_set_key(pkey, &ctx);
    sm4_decrypt_file_test2(&ctx,TEMPFILEZIPNAME,tmpFileName);
    pDownLoadFileName = tmpFileName;
    QString tmpFile = QString(QLatin1String(TEMPFILEZIPNAME));
    Common *pCommon = NULL;
    pCommon->RemoveOverageFile(tmpFile);
    qDebug()<<"ready end.";
    return "";
}

void SM4Decrypt::Encrypt_String(QByteArray& source_array, QByteArray& result_array, unsigned char key[16] )
{
    /*result_array.resize( source_array.length( ) );
    sm4_context ctx;
    sm4_setkey_enc( &ctx, key );
    sm4_crypt_ecb( &ctx, 1, source_array.length( ), (unsigned char*)source_array.data( ), (unsigned char*)result_array.data( ) );*/
    //unsigned char* test = (unsigned char*)result_array.data( );
    //printf("%02x ",test);
}

void SM4Decrypt::Decrypt_String(const QString& source_array0, const QString& result_array0, unsigned char key[16] )
{

}

void SM4Decrypt::Encrypt_ByteArray( QByteArray & source_file, QByteArray& result_file, unsigned char key[16] )
{
    /*result_file.resize( source_file.size( ) );
    sm4_context ctx;
    sm4_setkey_enc( &ctx, key );
    sm4_crypt_ecb( &ctx, 1, source_file.length( ), (unsigned char*)source_file.data( ), (unsigned char*)result_file.data( ) );*/
}

void SM4Decrypt::Decrypt_ByteArray( QByteArray & source_file, QByteArray& result_file, unsigned char key[16] )
{
    /*result_file.resize( source_file.size( ) );
    sm4_context ctx;
    sm4_setkey_dec( &ctx, key );
    sm4_crypt_ecb( &ctx, 0, source_file.length( ), (unsigned char*)source_file.data( ), (unsigned char*)result_file.data( ) );*/
}
