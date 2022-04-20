#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QtNetwork>
#include <recvdata.h>
#include <QtDebug>
#include <windows.h>
#include <dealmsg.h>
#include <writetofiles.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Recvdata; //使用前向声明
class Senddata;
class DealMsg;
class  WriteToFiles;

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
    WriteToFiles* writeToFiles;
    bool isStopSend;

    void setLocalMsg();
    void OpenDealMsgThread();
    void OpenWriteToFilesThread();
    void stopThread();

private slots:
    void on_pushButton_Send_clicked();
    void on_pushButton_Stop_clicked();
    void FinishDealMsgThread();
    void FinishWriteToFilesThread();


private:
    bool isTimeUpdate;
};
#endif // MAINWINDOW_H
