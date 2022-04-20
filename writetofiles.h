#ifndef WRITETOFILES_H
#define WRITETOFILES_H

#include <QThread>
#include <QUdpSocket>
#include <QDebug>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include"dealmsg.h"

class DealMsg;
class  WriteToFiles;

class WriteToFiles : public QThread
{
public:
    WriteToFiles(DealMsg* dealmsg);

    QTimer* udpTimer;
    DealMsg* dealMsg;
    bool isTimeUpdate;
    QDateTime dateTime; //当前系统时间
    string saveFolder;//存储目录（文件夹）
    QString saveFilename1; //CH1存储文件名
    QString saveFilename2;
    QString saveFilename3;
    QString file1;
    QString file2;
    QString file3;
    ofstream outfile1;//CH1
    ofstream outfile2;
    ofstream outfile3;
    int PeakNum=31;

protected:
        //QThread的虚函数
        //线程处理函数
        //不能直接调用，通过start()间接调用
    void run();

signals:

};

#endif // WRITETOFILES_H
