#include "senddata.h"

Senddata::Senddata(QUdpSocket *socket, Ui::MainWindow *ui)
{
    udpSocket = socket;

    UI = ui;
}

Senddata:: ~Senddata()
{

}

void Senddata:: ReadFromFiles()
{
    //file dir
    saveFolder  = QString("F:/Desktop/UDPConnect/");
    file = saveFolder + QString("SendData2")+QString(".txt");

    //open file
    infile.open(file.toStdString().data(),ios_base::in);

    //
    sendData.resize(200000);

    //if open failed, exit
    if(!infile.is_open())
    {
        qDebug()<< "open file failed !" << endl;
    }

    //ifstream >> sendData
    while(getline(infile, sendData))
    {
        qDebug()<< "reading file succeed !" << endl;
    }

    //close ifstream
    infile.close();
}

void Senddata::getConfig()
{
    //待发送消息buf
    msgbuf = QByteArray::fromStdString(sendData);
  //  msgbuf = QString(sendData.c_str());

    //目的IP
    DestIP = UI->lineEdit_Ip->text();

    //目的端口号
    DestPort = UI->lineEdit_Port->text().toInt();
}

void Senddata:: writeDatagram()
{
    //msgbuf >>UDP
    udpSocket->writeDatagram(msgbuf,QHostAddress(DestIP),DestPort);

}
