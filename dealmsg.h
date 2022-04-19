#ifndef DEALMSG_H
#define DEALMSG_H

#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include "ui_mainwindow.h"
#include "mainwindow.h"

class DealMsg;
class  WriteToFiles;

/*QThread DealMsg used for dealing UDP response*/

class DealMsg : public QThread
{
public:
    DealMsg(QUdpSocket *socket);


    void readDatagram();
    void getDatafromByteToFloat();
    void execute();
    void OpenDealMsgThread();

    QUdpSocket *udpSocket;
    BYTE* bufPtr;
    shared_ptr<BYTE*> RECORD_BUF; //接收数据的Buffer
    qint64 lenoDatagram; //Datagram的长度
    QByteArray datagram; //接收UDP的容器
    QHostAddress clientAddr; //客户端IP
    quint16 clientPort; //客户端port
    shared_ptr<CirQueue<float>> CHdata; //存放Channel数据的容器
    shared_ptr<CirQueue<unsigned char>> CHdata2; //测试
     qint64 LenoUDP = 2000*60000;
     bool readFlag;  //if has received readyRead signal

protected:
        //QThread的虚函数
        //线程处理函数
        //不能直接调用，通过start()间接调用
         void run();

signals:
    //线程执行完发送
//    void finished();
};

#endif // DEALMSG_H
