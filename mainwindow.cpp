#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isStart = false;

    isASCII = false;

    isHEX = false;

    isSave = false;

    CHdata2 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata3 = make_shared<CirQueue<unsigned char>>(LenoUDP);

    //set Local Message
    setLocalMsg();

    //new UDP_Recv Thread
    udp_recv = new UDP_Recv(this);

    udp_recv->start();

    //Counting 10s
    udpTimer = new QTimer();
    udpTimer->setTimerType(Qt::PreciseTimer);
    udpTimer->start(5000);

    //new WriteToFiles Thread
    writeToFiles = new WriteToFiles(udp_recv);

    //clear window
    if(ui->textEdit_Msg->isFullScreen())
        ui->textEdit_Msg->clear();

    connect(udp_recv,&QThread::finished,this,&MainWindow::FinishUDP_RecvThread);

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
    QString title = QString("Server IP: %1, Port: 7000").arg(IpAddress.toString());
    setWindowTitle(title);
}

void MainWindow::OpenDealMsgThread()
{


}

void MainWindow::FinishUDP_RecvThread()
{
    //quit Thread
    udp_recv->quit();

    udp_recv->wait();

}

void MainWindow::OpenWriteToFilesThread()
{
    isSave = ui->checkBox_Save->isChecked();

    if(isSave && isStart){
        writeToFiles->start();
    }

}

void MainWindow::FinishWriteToFilesThread()
{
    //quit Thread
    writeToFiles->quit();

    writeToFiles->wait();

    ui->textEdit_Msg->insertPlainText(" Files have been saved in " + writeToFiles->saveFilenameAll+'\n');

}

void MainWindow::on_pushButton_Start_clicked()
{
    isStart = true;

    ui->textEdit_Msg->insertPlainText(" Started ! ");
}

void MainWindow::on_pushButton_Stop_clicked()
{
    isStart = false;

    ui->checkBox_ASCII->setChecked(isStart);
    ui->checkBox_Hex->setChecked(isStart);

    isSave = false;

    ui->checkBox_Save->setChecked(isSave);

    ui->textEdit_Msg->insertPlainText(" Stopped ! ");
}

void MainWindow::on_pushButton_Clear_clicked()
{

    ui->textEdit_Msg->clear();

}

