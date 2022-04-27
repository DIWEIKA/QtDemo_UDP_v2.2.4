#include "writetofiles.h"

WriteToFiles::WriteToFiles(UDP_Recv* udp_Recv)
{
    udp_recv = udp_Recv;

    CHdata = make_shared<CirQueue<unsigned char>>(udp_recv->LenoUDP);
}

void WriteToFiles::run()
{
    qDebug() << "TimeUpdate" << endl;

    //更新当前时间
    dateTime = QDateTime::currentDateTime();

    saveFolder =  string("F:/Desktop/UDPConnect/data/");

    //    saveFilename1 = QString(saveFolder.c_str())+QString("/[CH1][")+QString::number(PeakNum)
    //            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    //    saveFilename2 = QString(saveFolder.c_str())+QString("/[CH2][")+QString::number(PeakNum)
    //            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    //    saveFilename3 = QString(saveFolder.c_str())+QString("/[CH3][")+QString::number(PeakNum)
    //            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    //    saveFilename4 = QString(saveFolder.c_str())+QString("/[CH4][")+QString::number(PeakNum)
    //            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    saveFilenameAll = QString(saveFolder.c_str())+QString("[All][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");


    //打开文件
    //   outfile1.open(saveFilename1.toStdString().data(),ofstream::binary);
    //   outfile2.open(saveFilename2.toStdString().data(),ofstream::binary);
    //   outfile3.open(saveFilename3.toStdString().data(), ofstream::binary);
    //   outfile4.open(saveFilename4.toStdString().data(), ofstream::binary);
    outfileAll.open(saveFilenameAll.toStdString().data(), ofstream::binary);

    //打开文件失败则结束运行
    //    if (!outfile1.is_open() || !outfile2.is_open() || !outfile3.is_open() || !outfile4.is_open()) return;
    if (!outfileAll.is_open()) return;


    unsigned int sizeoCHdata; //CHdata的长度

    //如果CHdata2不为空，则CHdata2 >> CHdata >> ofStream
    if(!udp_recv->CHdata2->isEmpty()){

        sizeoCHdata = udp_recv->CHdata2->size();

        CHdata = udp_recv->CHdata2;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata2->clear();
    }

    //如果CHdata3不为空，则继续CHdata3 >> CHdata >> ofStream
    if (!udp_recv->CHdata3->isEmpty()){

        sizeoCHdata = udp_recv->CHdata3->size();

        CHdata = udp_recv->CHdata3;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata3->clear();
    }

    //如果CHdata4不为空，则继续CHdata4 >> CHdata >> ofStream
    if (!udp_recv->CHdata4->isEmpty()){

        sizeoCHdata = udp_recv->CHdata4->size();

        CHdata = udp_recv->CHdata4;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata4->clear();
    }

    //如果CHdata5不为空，则继续CHdata5 >> CHdata >> ofStream
    if (!udp_recv->CHdata5->isEmpty()){

        sizeoCHdata = udp_recv->CHdata5->size();

        CHdata = udp_recv->CHdata5;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata5->clear();
    }

    //如果CHdata6不为空，则继续CHdata6 >> CHdata >> ofStream
    if (!udp_recv->CHdata6->isEmpty()){

        sizeoCHdata = udp_recv->CHdata6->size();

        CHdata = udp_recv->CHdata6;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata6->clear();
    }

    //如果CHdata7不为空，则继续CHdata7 >> CHdata >> ofStream
    if (!udp_recv->CHdata7->isEmpty()){

        sizeoCHdata = udp_recv->CHdata7->size();

        CHdata = udp_recv->CHdata7;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata7->clear();
    }

    //如果CHdata8不为空，则继续
    if (!udp_recv->CHdata8->isEmpty()){

        sizeoCHdata = udp_recv->CHdata8->size();

        CHdata = udp_recv->CHdata8;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata8->clear();
    }

    //如果CHdata9不为空，则继续
    if (!udp_recv->CHdata9->isEmpty()){

        sizeoCHdata = udp_recv->CHdata9->size();

        CHdata = udp_recv->CHdata9;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata9->clear();
    }

    //如果CHdata10不为空，则继续
    if (!udp_recv->CHdata10->isEmpty()){

        sizeoCHdata = udp_recv->CHdata10->size();

        CHdata = udp_recv->CHdata10;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata10->clear();
    }

    //如果CHdata11不为空，则继续
    if (!udp_recv->CHdata11->isEmpty()){

        sizeoCHdata = udp_recv->CHdata11->size();

        CHdata = udp_recv->CHdata11;

        for(unsigned int i=0; i<sizeoCHdata; ++i){
            outfileAll.write((const char*)CHdata->begin(),sizeof (unsigned char));
            CHdata->pop();
        }

        //                udp_recv->CHdata11->clear();
    }

    qDebug()<<"ofstream writing over ! "<<endl;


    //close stream
    //    outfile1.close();
    //    outfile2.close();
    //    outfile3.close();
    //    outfile4.close();

    outfileAll.close();

    qDebug()<< "WriteToFiles Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;
}

