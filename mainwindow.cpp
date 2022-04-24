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

     //Share space, link father object
    udpSocket = new QUdpSocket(this);

    //bind port
    udpSocket->bind(7000);

    //set Local Message
    setLocalMsg();

    //Counting 60s
    udpTimer = new QTimer();
    udpTimer->setTimerType(Qt::PreciseTimer);//设置定时器对象精确度模式，分辨率为1ms
    udpTimer->start(60000);

    //new WriteToFiles Thread
    writeToFiles = new WriteToFiles(this);

    //Every Source send a packet, connect OpenDealMsgThread
    connect(udpSocket, &QUdpSocket::readyRead, this, &MainWindow::OpenDealMsgThread);

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
    if(isStart){

        while(udpSocket->hasPendingDatagrams()){

            qDebug()<<"pending UDP datagram size = "<< udpSocket->pendingDatagramSize()<<endl;

            qDebug()<<"readDatagram ... "<<endl;

            //clear datagram
            datagram.clear();

            //datagram init
            datagram.resize(udpSocket->pendingDatagramSize());

            //读取对方发送的内容，并存入datagram
            lenoDatagram = udpSocket->readDatagram(datagram.data(),datagram.size(),&clientAddr,&clientPort);

           //release bufPtr
            delete bufPtr;
            bufPtr = NULL;

            isASCII = ui->checkBox_ASCII->isChecked();

            isHEX = ui->checkBox_Hex->isChecked();

           //ASCII接收
           if(isASCII && (!isHEX)){

               //define a new BYTE[]
               bufPtr = new BYTE[lenoDatagram]();

                //define a new RECORD_BUF
               RECORD_BUF = make_shared<BYTE*>(bufPtr);

               //RECORD_BUF << datagram
               memcpy(*RECORD_BUF,datagram.data(),lenoDatagram);

               //CHData << RECORD_BUF
               qDebug()<<"CHData << RECORD_BUF "<<endl;

               for(int i=0; i<lenoDatagram; i++) {

                 unsigned char usCHDATA =(*RECORD_BUF)[i];

                  CHdata2->push(usCHDATA);
               }

            }

           //HEX接收
           else if((!isASCII) && isHEX){

               lenoDatagramHEX = lenoDatagram * 2;

               //define a new BYTE[]
               bufPtr = new BYTE[lenoDatagramHEX]();

                //define a new RECORD_BUF
               RECORD_BUF = make_shared<BYTE*>(bufPtr);

               datagramHEX = datagram.toHex().toUpper();

               memcpy(*RECORD_BUF,datagramHEX,lenoDatagramHEX);

               //CHData << RECORD_BUF
               qDebug()<<"CHData << RECORD_BUF "<<endl;

               for(int i=0; i<lenoDatagramHEX; i++) {

                 unsigned char usCHDATA =(*RECORD_BUF)[i];

                  CHdata2->push(usCHDATA);

               }//end for

           } //end else if

         else
               break;

         }//end while

        ui->textEdit_Msg->insertPlainText("Pending...");

    } //end if

}

void MainWindow::FinishDealMsgThread()
{
//    //quit Thread
//    dealMsg->quit();

//    dealMsg->wait();

}

void MainWindow::OpenWriteToFilesThread()
{
  isSave = ui->checkBox_Save->isChecked();

  if(isSave){
      writeToFiles->start();
  }

}

void MainWindow::FinishWriteToFilesThread()
{
    //quit Thread
    writeToFiles->quit();

    writeToFiles->wait();

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
}

