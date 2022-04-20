#include "writetofiles.h"

WriteToFiles::WriteToFiles(DealMsg* dealmsg)
{
    dealMsg = dealmsg;
}

void WriteToFiles::run()
{
    qDebug() << "TimeUpdate" << endl;

    //更新当前时间
    dateTime = QDateTime::currentDateTime();

    saveFolder =  string("F:/Desktop/UDPConnect/data/");

    saveFilename1 = QString(saveFolder.c_str())+QString("/[CH1][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    saveFilename2 = QString(saveFolder.c_str())+QString("/[CH2][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
    saveFilename3 = QString(saveFolder.c_str())+QString("/[CH3][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");
//    saveFilenameAll = QString(saveFolder.c_str())+QString("/[ALL][")+QString::number(PeakNum)
//            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    //打开文件
   outfile1.open(saveFilename1.toStdString().data(),ofstream::binary);
   outfile2.open(saveFilename2.toStdString().data(),ofstream::binary);
   outfile3.open(saveFilename3.toStdString().data(), ofstream::binary);

    //打开文件失败则结束运行
    if (!outfile1.is_open() || !outfile2.is_open() || !outfile3.is_open()) return;

    //按先后顺序将CH1、CH2、CH3的数据分开存储
    unsigned int sizeoCHdata2 = dealMsg->CHdata2->size();

    for(unsigned int i=0; i<sizeoCHdata2/3; ++i)
    {
        outfile1.write((const char*)dealMsg->CHdata2->begin(),sizeof (unsigned char));
        dealMsg->CHdata2->pop();
        outfile2.write((const char*)dealMsg->CHdata2->begin(),sizeof (unsigned char));
        dealMsg->CHdata2->pop();
        outfile3.write((const char*)dealMsg->CHdata2->begin(),sizeof (unsigned char));
        dealMsg->CHdata2->pop();
    }

    //clear CHdata
    dealMsg->CHdata2->clear();

    qDebug()<<"ofstream writing over ! "<<endl;

    qDebug()<<"CHdata have been cleared ! "<<endl;

    //close stream
    outfile1.close();
    outfile2.close();
    outfile3.close();

    qDebug()<< "WriteToFiles Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;
}

