#include "dealmsg.h"

DealMsg::DealMsg(QUdpSocket *socket , Ui::MainWindow *ui)
{
    udpSocket = socket;

    UI = ui;

    //CHdata初始化
     CHdata2 = make_shared<CirQueue<unsigned char>>(LenoUDP);
}

void DealMsg::run()
{
    while(udpSocket->hasPendingDatagrams()){
        //发送的UDP数据包的大小
        qDebug()<<"pending UDP datagram size = "<< udpSocket->pendingDatagramSize()<<endl;

//         UI->textEdit_Msg->insertPlainText("Pending...");

        //datagram << UDP
       readDatagram();

       //release bufPtr
        delete bufPtr;
        bufPtr = NULL;

       //define a new BYTE[]
       bufPtr = new BYTE[lenoDatagram]();

        //define a new RECORD_BUF
       RECORD_BUF = make_shared<BYTE*>(bufPtr);

       //RECORD_BUF << datagram
       memcpy(*RECORD_BUF,datagram.data(),lenoDatagram);

       //CHData << RECORD_BUF
       getDatafromByteToFloat();

    }

//    emit finished();

     qDebug()<<"DealMsg Thread is Finished ! "<<endl;
}

void DealMsg::readDatagram()
{
     qDebug()<<"readDatagram ... "<<endl;

        //clear datagram
        datagram.clear();

        //datagram init
        datagram.resize(udpSocket->pendingDatagramSize());

        //读取对方发送的内容，并存入datagram
         lenoDatagram = udpSocket->readDatagram(datagram.data(),datagram.size(),&clientAddr,&clientPort);
}

void DealMsg::getDatafromByteToFloat()
{
     qDebug()<<"getDatafromByteToFloat ... "<<endl;

    for(int i=0; i<lenoDatagram; i++)
     {
       unsigned char usCHDATA =(*RECORD_BUF)[i];

//       qDebug()<<"usCHDATA= "<<usCHDATA<<endl;

//        CHdata->push(float(usCHDATA));

        //测试
        CHdata2->push(usCHDATA);

    }
}
