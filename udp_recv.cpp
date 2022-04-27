#include "udp_recv.h"

UDP_Recv::UDP_Recv(MainWindow* mainwindow)
{
    mainWindow = mainwindow;

    //Share space, link father object
    udpSocket = new QUdpSocket(this);

    //bind port
    udpSocket->bind(7000);

    CHdata2 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata3 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata4 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata5 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata6 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata7 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata8 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata9 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata10 = make_shared<CirQueue<unsigned char>>(LenoUDP);
    CHdata11 = make_shared<CirQueue<unsigned char>>(LenoUDP);
}

void UDP_Recv::run()
{
    while(1)
    {
        isStart = mainWindow->isStart;

        if(isStart){

            isASCII = mainWindow->ui->checkBox_ASCII->isChecked();

            isHEX = mainWindow->ui->checkBox_Hex->isChecked();

            while(udpSocket->hasPendingDatagrams()){

                qDebug()<<"pending UDP datagram size = "<< udpSocket->pendingDatagramSize()<<endl;

                //datagram init
                datagram.resize(udpSocket->pendingDatagramSize());

                //读取对方发送的内容，并存入datagram
                lenoDatagram = udpSocket->readDatagram(datagram.data(),datagram.size(),&clientAddr,&clientPort);

                //release bufPtr
                delete bufPtr;
                bufPtr = NULL;


                //ASCII接收
                if(isASCII && (!isHEX)){

                    //define a new BYTE[]
                    bufPtr = new BYTE[lenoDatagram]();

                    //define a new RECORD_BUF
                    RECORD_BUF = make_shared<BYTE*>(bufPtr);

                    //RECORD_BUF << datagram
                    memcpy(*RECORD_BUF,datagram.data(),lenoDatagram);

                    //clear datagram
                    datagram.clear();

                    //CHData << RECORD_BUF
                    for(int i=0; i<lenoDatagram; i++) {

                        unsigned char usCHDATA =(*RECORD_BUF)[i];

                        //CHdata2满了，存入CHdata3
                        if(CHdata2->isFull()){
                            CHdata3->push(usCHDATA);
                        }
                        else
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

                    datagramHEX = datagram.toHex().toUpper(); //.toHex().toUpper()

                    memcpy(*RECORD_BUF,datagramHEX,lenoDatagramHEX);

                    //clear datagram
                    datagram.clear();

                    //CHData << RECORD_BUF
                    for(int i=0; i<lenoDatagramHEX; i++) {

                        unsigned char usCHDATA =(*RECORD_BUF)[i];

                        //如果CHdata2没满，存入CHdata2
                        if(!CHdata2->isFull())
                            CHdata2->push(usCHDATA);

                        //否则，如果CHdata3没满，存入CHdata3
                        else if(!CHdata3->isFull())
                            CHdata3->push(usCHDATA);

                        //否则，如果CHdata4没满，存入CHdata4
                        else if(!CHdata4->isFull())
                            CHdata4->push(usCHDATA);

                        //否则，如果CHdata5没满，存入CHdata5
                        else if(!CHdata5->isFull())
                            CHdata5->push(usCHDATA);

                        //否则，如果CHdata6没满，存入CHdata6
                        else if(!CHdata6->isFull())
                            CHdata6->push(usCHDATA);

                        //否则，如果CHdata7没满，存入CHdata7
                        else if(!CHdata7->isFull())
                            CHdata7->push(usCHDATA);

                        //否则，如果CHdata8没满，存入CHdata8
                        else if(!CHdata8->isFull())
                            CHdata8->push(usCHDATA);

                        //否则，如果CHdata9没满，存入CHdata9
                        else if(!CHdata9->isFull())
                            CHdata9->push(usCHDATA);

                        //否则，如果CHdata10没满，存入CHdata10
                        else if(!CHdata10->isFull())
                            CHdata10->push(usCHDATA);

                        //否则，如果CHdata11没满，存入CHdata11
                        else if(!CHdata11->isFull())
                            CHdata11->push(usCHDATA);

                    }//end for

                } //end else if

                else
                    break;

                break;

            }//end while

        } //end if
    }
}
