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

       //获取本机的计算机名
    QString localHostName = QHostInfo:: localHostName();
    qDebug() <<"localHostName: "<<localHostName;

    ui->textEdit_Msg->insertPlainText("localHostName: "+localHostName+'\n');

    //获取本机IP
    QHostInfo info = QHostInfo::fromName(localHostName);
    QList<QHostAddress> strIpAddress  = info.addresses();
    QHostAddress IpAddress =  strIpAddress.back();
    qDebug() << "IpAddress: " << IpAddress;

    ui->textEdit_Msg->insertPlainText("IpAddress: "+IpAddress.toString()+'\n');

    //设置窗口的标题
    QString title = QString("Server IP: %1, Port: 8000").arg(IpAddress.toString());
    setWindowTitle(title);

    //new DealMsg Thread
    dealMsg  = new DealMsg(udpSocket,ui);

    //start Thread
    dealMsg->start();

    //new WriteToFiles Thread
    writeToFiles = new WriteToFiles(dealMsg);

    //start Thread
    writeToFiles->start();

 }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Send_clicked()
{
    qDebug()<<" pushButton_Send_clicked "<<endl;

    ui->textEdit_Msg->insertPlainText("pushButton_Send_clicked"+'\n');

    //New Senddata Object
    senddata = new Senddata(udpSocket, ui);

    //ifStream >> sendData
    senddata->ReadFromFiles();

    //sendData >> msgbuf
    senddata->getConfig();

    isStopSend = false;

    while(1)
    {
        //msgbuf >> UDP
        senddata->writeDatagram();

        qDebug()<<"sending data ... "<<endl;

        //delay 1ms
        Sleep(1);
    }
}

void MainWindow::on_pushButton_Stop_clicked()
{


}

void MainWindow::stopThread()
{
    //quit Thread
    dealMsg->quit();
    writeToFiles->quit();

    //waiting until Thread is over
    dealMsg->wait();
    writeToFiles->wait();
}

