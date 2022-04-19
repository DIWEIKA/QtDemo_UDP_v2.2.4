#include "dealmsg.h"

DealMsg::DealMsg(QUdpSocket *socket)
{
    udpSocket = socket;

    //CHdata初始化
     CHdata2 = make_shared<CirQueue<unsigned char>>(LenoUDP);

     readFlag = 0;
}

void DealMsg::run()
{
    while(udpSocket->hasPendingDatagrams()){

        //发送的UDP数据包的大小
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

       //define a new BYTE[]
       bufPtr = new BYTE[lenoDatagram]();

        //define a new RECORD_BUF
       RECORD_BUF = make_shared<BYTE*>(bufPtr);

       //RECORD_BUF << datagram
       memcpy(*RECORD_BUF,datagram.data(),lenoDatagram);

       //CHData << RECORD_BUF
       qDebug()<<"getDatafromByteToFloat ... "<<endl;

      for(int i=0; i<lenoDatagram; i++)
       {
         unsigned char usCHDATA =(*RECORD_BUF)[i];

          //测试
          CHdata2->push(usCHDATA);

      }
       readFlag = 0;
     }

    qDebug()<<"DealMsg Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;

    // loop the Thread
//     this->exec();
}

void DealMsg::OpenDealMsgThread()
{

}

void DealMsg::readDatagram()
{

}

void DealMsg::getDatafromByteToFloat()
{

}
