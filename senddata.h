#ifndef SENDDATA_H
#define SENDDATA_H

#include <fstream>
#include <sstream>
#include <QMainWindow>
#include <memory>
#include "ui_mainwindow.h"
#include "mainwindow.h"

class Senddata  : public QObject
{
public:
    Senddata(QUdpSocket *socket, Ui::MainWindow *ui);
    ~Senddata();
    void ReadFromFiles(); //ifStream >> sendData
    void getConfig();  //sendData>>msgbuf
    void writeDatagram(); //msgbuf>>UDP

    Ui::MainWindow *UI;

    QUdpSocket *udpSocket;
    ifstream infile; //本地待发送数据
    QString file; //本地文件目录
    QString saveFolder;
    string sendData; //发送一包UDP数据，超过8192Byte会丢包，超过65535Byte会无法发送
    QByteArray msgbuf;
    QString DestIP;
    qint16 DestPort;
};

#endif // SENDDATA_H
