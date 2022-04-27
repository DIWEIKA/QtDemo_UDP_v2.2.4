#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QQueue>
#include "CirQueue.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QtNetwork>
#include <recvdata.h>
#include <QtDebug>
#include <vector>
#include <windows.h>
#include <writetofiles.h>
#include <udp_recv.h>


typedef unsigned char BYTE;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Recvdata; //使用前向声明
class Senddata;
class DealMsg;
class WriteToFiles;
class UDP_Recv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

    Senddata *senddata;
    QUdpSocket *udpSocket; //udp pointer
    QTimer* udpTimer;
    DealMsg* dealMsg;
    UDP_Recv* udp_recv;
    WriteToFiles* writeToFiles;
    bool isSave;
    bool isStart;
    bool isASCII;
    bool isHEX;
    BYTE* bufPtr;
    shared_ptr<BYTE*> RECORD_BUF; //接收数据的Buffer
    qint64 lenoDatagram; //Datagram的长度
    qint64 lenoDatagramHEX;
    QByteArray datagram; //接收UDP的容器
    QByteArray datagramHEX;
    QHostAddress clientAddr; //客户端IP
    quint16 clientPort; //客户端port
    shared_ptr<CirQueue<unsigned char>> CHdata2;
    shared_ptr<CirQueue<unsigned char>> CHdata3;
    qint64 LenoUDP = 4096*10000;

    void setLocalMsg();
    void OpenDealMsgThread();
    void OpenWriteToFilesThread();
    void stopThread();

private slots:

    void FinishUDP_RecvThread();
    void FinishWriteToFilesThread();
    void on_pushButton_Start_clicked();
    void on_pushButton_Stop_clicked();

    void on_pushButton_Clear_clicked();

private:
    bool isTimeUpdate;
};
#endif // MAINWINDOW_H
