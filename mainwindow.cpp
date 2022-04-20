#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     //Share space, link father object
    udpSocket = new QUdpSocket(this);

    //bind port
    udpSocket->bind(8000);

    //set Local Message
    setLocalMsg();

    //Counting 60s
    udpTimer = new QTimer();
    udpTimer->setTimerType(Qt::PreciseTimer);//设置定时器对象精确度模式，分辨率为1ms
    isTimeUpdate = false;
    udpTimer->start(60000);

    //new DealMsg Thread
    dealMsg  = new DealMsg(udpSocket);

    //new WriteToFiles Thread
    writeToFiles = new WriteToFiles(dealMsg);

    //Every Source send a packet, connect OpenDealMsgThread
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::OpenDealMsgThread);

    //Every time dealMsg is finished, connect dealMsgFinshedSlot()
    connect(dealMsg,&QThread::finished,this,&MainWindow::FinishDealMsgThread);

    //Every 60s emit a timeout(), connect OpenWriteToFilesThread
    connect(udpTimer,&QTimer::timeout,this,&MainWindow::OpenWriteToFilesThread);

    //Every time dealMsg is finished, connect dealMsgFinshedSlot()
    connect(writeToFiles,&QThread::finished,this,&MainWindow::FinishWriteToFilesThread);

 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLocalMsg()
{
    //获取本机的计算机名
   QString localHostName = QHostInfo:: localHostName();
   qDebug() <<"localHostName: "<<localHostName<<endl;

   ui->textEdit_Msg->insertPlainText("localHostName: "+localHostName+'\n');

   //获取本机IP
   QHostInfo info = QHostInfo::fromName(localHostName);
   QList<QHostAddress> strIpAddress  = info.addresses();
   QHostAddress IpAddress =  strIpAddress.back();
   qDebug() << "IpAddress: " << IpAddress<<endl;
   qDebug()<<"--------------------------"<<endl;

   ui->textEdit_Msg->insertPlainText("IpAddress: "+IpAddress.toString()+'\n');

   //设置窗口的标题
   QString title = QString("Server IP: %1, Port: 8000").arg(IpAddress.toString());
   setWindowTitle(title);
}

void MainWindow::OpenDealMsgThread()
{
    dealMsg->setFlag();

    //If dealMsg is Running, wait until it finished
       if(dealMsg->isRunning())
           dealMsg->wait();

    //run DealMsg Thread
    dealMsg->start();

    ui->textEdit_Msg->insertPlainText("Pending...");
}

void MainWindow::FinishDealMsgThread()
{
    //quit Thread
    dealMsg->quit();

    dealMsg->wait();

}

void MainWindow::OpenWriteToFilesThread()
{
//    //first quit dealMsg Thread
//    dealMsg->resetFlag();

    //then writeToFiles->run()
    writeToFiles->start();
}

void MainWindow::FinishWriteToFilesThread()
{
    //quit Thread
    writeToFiles->quit();

    writeToFiles->wait();

}

void MainWindow::on_pushButton_Send_clicked()
{

}

void MainWindow::on_pushButton_Stop_clicked()
{


}

void MainWindow::stopThread()
{


}

