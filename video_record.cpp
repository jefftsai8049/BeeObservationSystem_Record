#include "video_record.h"

video_record::video_record(const cv::Size &size)
{
    this->imgSize = size;
    status = 0;
    writer = 0;
}

video_record::~video_record()
{

}

void video_record::videoStart(const QString &fileName)
{
    qDebug() <<"video file:" << fileName;
    writer = new cv::VideoWriter(fileName.toStdString(),cv::VideoWriter::fourcc('X','V','I','D'),12,this->imgSize,true);
    //writer->open(fileName.toStdString(),cv::VideoWriter::fourcc('X','V','I','D'),12,this->imgSize,true);

}

void video_record::videoEnd()
{
    if(!writer->isOpened())
        return;
    while(status != 0){}
    if(status == 0){
        writer->release();
        //delete writer;
    }

}

void video_record::videoWrite(const cv::Mat &src)
{
    buffer = src.clone();
}

bool video_record::isVideoStart()
{
    if(writer !=0)
    {
        return writer->isOpened();
    }
    else
    {
        return 0;
    }
}

void video_record::run()
{
    QTime t;
    t.start();
    status =1;
    if(!buffer.empty())
        writer->write(buffer);

    status =0;
    qDebug()  << "record"<< t.elapsed();
}

