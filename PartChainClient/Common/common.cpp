#include "common.h"
#include <QDateTime>
#include "networkclean.h"
#include <QNetworkInterface>
#include <QSysInfo>
#include <QHostInfo>
#include <winsock2.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

QString pGetJsToken,pGetJsUrl,pGetForensicsName,pGetNameNoTime,pGetHostIp,pGetDirPath,pDownLoadFileName;
QString pIpAddress,pMacAddress,pOsVersion,pGateway;

Common::Common()
{

}

Common::~Common()
{

}

bool Common::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    if(dir.exists())
    {
      return true;
    }
    else
    {
       bool ok = dir.mkpath(fullPath);//只创建一级子目录，即必须保证上级目录存在
       return ok;
    }
}

QString Common::FileDirPath(RecordType recordType)
{
    QString filePathDir,strHalfPath;
    QString getDirPath = QCoreApplication::applicationDirPath();
    switch(recordType)
    {
        case WebRecord:         strHalfPath = "/OutPut/网页取证/";break;
        case CameraRecord:      strHalfPath = "/OutPut/拍摄取证/";break;
        case VideoRecord:       strHalfPath = "/OutPut/录屏取证/";break;
        case ScreenShotRecord:  strHalfPath = "/OutPut/截图取证/";break;
        default:break;
    }

    filePathDir = getDirPath + strHalfPath + pGetForensicsName + "/";
    return filePathDir;
}

QString Common::ReadLog(void)
{
    QString filePath = QCoreApplication::applicationDirPath() + "/OutPut/networkclean/Log.txt";
    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray t = file.readAll();
    file.close();
    
    QString str = QString(t);
    return str;
}

void Common::WriteIpTrack(RecordType recordType, QString str)
{
    QString filePathDir = FileDirPath(recordType);
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss-zzz");
    QString fileName = "IpTrack" + getTime + ".txt.aisino";
    pIpTrackFileName = fileName;
    QString filePath = filePathDir + fileName;
    isDirExist(filePathDir);

    QDir dir(filePath);
    QFile file(filePath);
    if(dir.exists())
    {
        file.remove(filePath);
    }
        
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(str.toUtf8());
    file.close();
}

QString Common::RenameLogFile(RecordType recordType, QString fileName)
{
    QString filePathDir = FileDirPath(recordType);
    pFileLog = fileName;
    QString filePath = filePathDir + fileName;
    isDirExist(filePathDir);

    QString strName = fileName.append(".aisino");
    QString strFullName = filePathDir + strName;

    QFile file(filePath);
    file.rename(strFullName);
    return strName;
}

void Common::RemoveWebLogFile(RecordType recordType, QString fileName)
{
    QString filePathDir = FileDirPath(recordType);
    QString filePath = filePathDir + fileName;
    QFile file(filePath);
    file.remove();
}

void Common::RemoveScnLogFile(QString fileName)
{
    QFile file(fileName);
    file.remove();
}

void Common::WriteLog(RecordType recordType, QString fileName, QString str)
{
    QString filePathDir = FileDirPath(recordType);
    pFileLog = fileName;
    QString filePath = filePathDir + fileName;
    isDirExist(filePathDir);

    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    file.write(str.toUtf8());
    file.close();
}

void Common::RemoveLog(RecordType recordType, QString fileName)
{
    QString filePathDir = FileDirPath(recordType);
    QString filePath = filePathDir + fileName;

    QFile file(filePath);
    if(file.exists() == true)
    {
        file.remove();
    }
}

void Common::CommunicationWriteLog(QString str1,QString str2,QString str3)
{
    QString filePath = QCoreApplication::applicationDirPath() + "/ForensicLogs.txt";
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append);
    QString m_str0 = QString("**********\n");
    QString m_str1 = QString("type : ") + str1 + QString("\n");
    QString m_str2 = QString("key : ") + str2 + QString("\n");
    QString m_str3 = QString("str : ") + str3 + QString("\n");
    QString str =  m_str0 +  m_str1 + m_str2 + m_str3;
    file.write(str.toUtf8());
    file.close();
}

QString Common::SetLogTimeFromat(void)
{
    QString getTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString timeFromat = "==[" + getTime + "]";
    return timeFromat;
}

void Common::CreateForensicsLog(RecordType recordType, QString fileName)
{
    QString timeFromat = SetLogTimeFromat();
    QString str;
    switch(recordType)
    {
        case WebRecord:         str = "创建网页取证=\n";break;
        case CameraRecord:      str = "创建拍摄取证=\n";break;
        case VideoRecord:       str = "创建录屏取证=\n";break;
        case ScreenShotRecord:  str = "创建截图取证=\n";break;
        default:break;
    }
    QString mForensics = timeFromat + str;
    WriteLog(recordType, fileName, mForensics);
}

void Common::FromBaiDuJumpTime(RecordType recordType, QString fileName)
{
    QString timeFromat = SetLogTimeFromat();
    QString mForensics = timeFromat + "网页加载==\n";
    WriteLog(recordType, fileName, mForensics);
}

void Common::FromBaiDuJumpUrl(RecordType recordType, QString fileName, QString url)
{
    FromBaiDuJumpTime(recordType, fileName);
    QString str = "网页地址：" + url + "\n";
    WriteLog(recordType, fileName, str);
}

void Common::WebJumpTime(RecordType recordType, QString fileName)
{
    QString timeFromat = SetLogTimeFromat();
    QString mForensics = timeFromat + "页面跳转==\n";
    WriteLog(recordType, fileName, mForensics);
}

void Common::WebJumpUrl(RecordType recordType, QString fileName, QString url)
{
    WebJumpTime(recordType, fileName);
    QString str = "跳转地址：" + url + "\n";
    WriteLog(recordType, fileName, str);
}

void Common::SaveForensicsLog(RecordType recordType, QString fileName)
{
    QString timeFromat = SetLogTimeFromat();
    QString str;
    switch(recordType)
    {
        case WebRecord:         str = "保存网页取证=\n";break;
        case CameraRecord:      str = "保存拍摄取证=\n";break;
        case VideoRecord:       str = "保存录屏取证=\n";break;
        case ScreenShotRecord:  str = "保存截图取证=\n";break;
        default:break;
    }

    QString mForensics = timeFromat + str;
    WriteLog(recordType, fileName, mForensics);
}

//注意：通过过滤的方法，和获取网关的方法来筛选出最终电脑使用的IP。只有连上的ip才会有网关
QString Common::GetIpAddress()
{
    /*QString strLocalHostName = QHostInfo::localHostName(); // 获取主机名
    qDebug() << "本地主机名 : " << strLocalHostName;

    QHostInfo info = QHostInfo::fromName(strLocalHostName);// 根据上边获得的主机名来获取本机的信息
    // QHostInfo的address函数获取本机ip地址
    // QHostAddress类是管理ip地址的类，所有的ip都归这个类管理。
    foreach (QHostAddress address, info.addresses())
    {
     if(address.protocol() == QAbstractSocket::IPv4Protocol && \
                            address != QHostAddress::Null &&  \
                            address != QHostAddress::LocalHost)//只取ipv4协议的地址
         qDebug() << "IP(IPv4Protocol) ： " << address.toString();
    }
    return strLocalHostName;*/

    QString ip="";
    QList<QNetworkInterface> interFaceList = QNetworkInterface::allInterfaces();
    for(int i=0; i< interFaceList.size(); i++)
    {
        if(interFaceList.at(i).flags().testFlag(QNetworkInterface::IsRunning)
                &&interFaceList.at(i).flags().testFlag(QNetworkInterface::IsUp)
                &&interFaceList.at(i).flags().testFlag(QNetworkInterface::CanBroadcast)
                &&interFaceList.at(i).flags().testFlag(QNetworkInterface::CanMulticast)
                &&!interFaceList.at(i).flags().testFlag(QNetworkInterface::IsLoopBack)
                &&!interFaceList.at(i).humanReadableName().contains("VMware")
                &&!interFaceList.at(i).humanReadableName().contains("VirtualBox")
                &&!interFaceList.at(i).humanReadableName().contains("Ethernet")
                &&!interFaceList.at(i).humanReadableName().contains("Wireless"))
        {
            QList<QNetworkAddressEntry> entryList = interFaceList.at(i).addressEntries();
            foreach(QNetworkAddressEntry entry, entryList)
            {
                if(QAbstractSocket::IPv4Protocol == entry.ip().protocol() &&
                   entry.ip() != QHostAddress::LocalHost)
                {
                    ip = entry.ip().toString();
                    QString gatway = GetGateway(ip);
                    if(gatway != "0.0.0.0")
                    {
                        QString version = "";
                        version.append(QSysInfo::productType());
                        version.append(QSysInfo::productVersion());

                        pIpAddress = ip;
                        pMacAddress = interFaceList.at(i).hardwareAddress();
                        pGateway = gatway;
                        pOsVersion = version;
                    }
                }
            }
        }
    }

    return ip;
}

void Common::tests()
{
    QString text;
    QList<QNetworkInterface> ifaceList = QNetworkInterface::allInterfaces();
    for (int i = 0; i < ifaceList.count(); i++)
    {
        QNetworkInterface var = ifaceList.at(i);
        qDebug() << QString("########## 设备%1 ############").arg(i) << endl;
        qDebug() << QString("接口名称：") << var.humanReadableName() << endl;
        qDebug() << QString("设备名称：") << var.name() << endl;
        qDebug() << QString("硬件地址：") << var.hardwareAddress() << endl;

        //qDebug() << QString("IP地址列表：") << endl;
        // 读取一个IP地址的关联信息列表
        QList<QNetworkAddressEntry> entryList = var.addressEntries();
        for(int j = 1; j < entryList.count(); j++)
        {
            QNetworkAddressEntry entry = entryList.at(j);
            //qDebug() << QString("%1_地址：").arg(j) << endl;
            qDebug() << QString(" IP地址：") << entry.ip().toString() << endl;
            qDebug() << QString(" 子网掩码：") << entry.netmask().toString() << endl;
            qDebug() << QString(" 广播地址：") << entry.broadcast().toString() << endl;
        }
    }
}

//获取网关地址
QString Common::GetGateway(QString ip)
{
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
    if (ERROR_BUFFER_OVERFLOW == nRel){
        // ERROR_BUFFER_OVERFLOW：内存空间不够
        // 释放原来的内存空间
        delete pIpAdapterInfo;
        // 重新申请内存空间用来存储所有网卡信息
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        // 再次调用GetAdaptersInfo
        nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);
    }
    if (ERROR_SUCCESS == nRel){
        while (pIpAdapterInfo){
            switch(pIpAdapterInfo->Type){
            case MIB_IF_TYPE_OTHER:
                break;
            case MIB_IF_TYPE_ETHERNET:
                break;
            case MIB_IF_TYPE_TOKENRING:
                break;
            case MIB_IF_TYPE_FDDI:
                break;
            case MIB_IF_TYPE_PPP:
                break;
            case MIB_IF_TYPE_LOOPBACK:
                break;
            case MIB_IF_TYPE_SLIP:
                break;
            default:
                break;
            }
            for (DWORD i = 0; i < pIpAdapterInfo->AddressLength; i++)
                if (i < pIpAdapterInfo->AddressLength-1){
                }
                else{
                }
                // 多个网卡、多个IP
                IP_ADDR_STRING *pIpAddrString =&(pIpAdapterInfo->IpAddressList);
                do{
                    if(QString(pIpAddrString->IpAddress.String) == ip){
                        return QString(pIpAdapterInfo->GatewayList.IpAddress.String);
                    }
                    pIpAddrString=pIpAddrString->Next;
                } while (pIpAddrString);
                pIpAdapterInfo = pIpAdapterInfo->Next;
        }

    }
    //释放内存空间
    if (pIpAdapterInfo){
        delete pIpAdapterInfo;
    }

    return "0.0.0.0";
}

//删除文件夹及其文件夹中所有内容
void Common::RemoveDirFile(QString &folderDir)
{
    QDir dir(folderDir);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())
    {
        qDebug()<<"dir no exists.";
        return ;   //文件不存，则返回false
    }
    fileList = dir.entryInfoList(QDir::Dirs | QDir::Files \
                               |QDir::Readable|QDir::Writable \
                               |QDir::Hidden|QDir::NoDotAndDotDot \
                               ,QDir::Name);
    while(fileList.size() > 0)
    {
        int infoNum = fileList.size();
        for(int i = infoNum - 1; i >= 0; i--)
        {
            curFile = fileList[i];
            if(curFile.isFile())//如果是文件，删除文件
            {               
                QFile fileTemp(curFile.filePath());                
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir())//如果是文件夹
            {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1 = dirTemp.entryInfoList(QDir::Dirs | QDir::Files \
                                                              |QDir::Readable | QDir::Writable \
                                                              |QDir::Hidden | QDir::NoDotAndDotDot \
                                                              ,QDir::Name);
                if(fileList1.size() == 0)//下层没有文件或文件夹
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else//下层有文件夹或文件
                {
                    for(int j = 0;j < fileList1.size(); j++)
                    {
                        if(!(fileList.contains(fileList1[j])))
                            fileList.append(fileList1[j]);
                    }
                }
            }
        }
    }
    dir.rmdir(folderDir);
}

void Common::RemoveOverageFile(QString &filePathName)
{
    QFile fileTemp(filePathName);
    if (fileTemp.exists())
    {
        if(fileTemp.remove())
        {
            qDebug() << "删除成功";
        }
        else
        {
            qDebug() << "删除失败";
        }
    }
    else
    {
        qDebug()<<"is not exists.";
    }
}
