#ifndef UDP_RECV_H
#define UDP_RECV_H

#include <QThread>
#include <mainwindow.h>


class UDP_Recv : public QThread
{
    Q_OBJECT
public:
    explicit UDP_Recv(MainWindow* mainwindow);

    MainWindow* mainWindow;
    QUdpSocket* udpSocket;


    BYTE* bufPtr;
    shared_ptr<BYTE*> RECORD_BUF;
    QByteArray datagram;
    QByteArray datagramHEX;
    qint64 lenoDatagram;
    qint64 lenoDatagramHEX;
    bool isStart;
    bool isASCII;
    bool isHEX;
    QHostAddress clientAddr;
    quint16 clientPort;
    qint64 LenoUDP = 4096*10000; //1s发送的数据个数(Bytes)
    shared_ptr<CirQueue<unsigned char>> CHdata2;
    shared_ptr<CirQueue<unsigned char>> CHdata3;
    shared_ptr<CirQueue<unsigned char>> CHdata4;
    shared_ptr<CirQueue<unsigned char>> CHdata5;
    shared_ptr<CirQueue<unsigned char>> CHdata6;
    shared_ptr<CirQueue<unsigned char>> CHdata7;
    shared_ptr<CirQueue<unsigned char>> CHdata8;
    shared_ptr<CirQueue<unsigned char>> CHdata9;
    shared_ptr<CirQueue<unsigned char>> CHdata10;
    shared_ptr<CirQueue<unsigned char>> CHdata11;

protected:
    void run();

signals:

};

#endif // UDP_RECV_H
