#include "dealmsg.h"

DealMsg::DealMsg(QUdpSocket *socket)
{
    udpSocket = socket;

    CHdata2 = make_shared<CirQueue<unsigned char>>(LenoUDP);
}

void DealMsg::setFlag()
{
    isDone = false;
}

void DealMsg::resetFlag()
{
    isDone = true;
}

void DealMsg::run()
{
    while(true){

        if(isDone)
            break;

        else {

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

                  //测试
                  CHdata2->push(usCHDATA);
               }
             }

            resetFlag();
        }
    }

    qDebug()<<"DealMsg Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;

//    exec();
}
