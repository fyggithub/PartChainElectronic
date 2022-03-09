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

#define BUFF_SIZE 256
#define MAXBUFFSIZE (100*1024*1024)

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

QList<QString> pList;
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
