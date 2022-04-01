#pragma once
#ifndef EN_DECRYPT_H_
#define EN_DECRYPT_H_

#include<QString>
#include<QByteArray>


class SM4Decrypt
{
public:
    SM4Decrypt();
    ~SM4Decrypt();
    void Encrypt_String( QByteArray& source, QByteArray& result, unsigned char key[16] );
    void Decrypt_String(const QString& source, const QString& result, unsigned char key[16] );
    void Encrypt_ByteArray( QByteArray& source_file, QByteArray& result_file, unsigned char key[16] );
    void Decrypt_ByteArray( QByteArray& source_file, QByteArray& result_file, unsigned char key[16] );
    void Decrypt_Test();
    QString EncodeSM4_Base64(QString key,const QString strInput);
    QString DecodeSM4_Base64(const QString& key,const QString& strInput);
    QString DecodeSM4_Base64Test(const QString& key,const char* strInput,int len);
    QString DecodeSM4_Base64Test2(const QString& key,const QByteArray& strInput);
    QString DecodeSM4_StreamTest(const QStringList& key,const QStringList& fileNameList,const char* strInput,int len);
    QString DecodeSM4_CertificateStreamTest(const QStringList& key,const QStringList& fileNameList);
    QString DecodeSM4_DetailStreamTest(const QStringList& key,const QStringList& fileNameList);
};

extern QList<QString> pList;
extern QMap<QString, QString> keyMap;

#endif // !EN_DECRYPT_H_

