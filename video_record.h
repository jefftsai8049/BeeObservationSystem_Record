#ifndef VIDEO_RECORD_H
#define VIDEO_RECORD_H

#include <QThread>
#include <QObject>
#include <QString>
#include <QTime>
#include <QDebug>

#include "opencv.hpp"

class video_record : public QThread
{
public:
    video_record(const cv::Size &size);
    ~video_record();
    void videoStart(const QString &fileName);
    void videoEnd();
    void videoWrite(const cv::Mat &src);

    bool isVideoStart();

private:
    cv::VideoWriter *writer;

    cv::Size imgSize;

    cv::Mat buffer;


    bool status;
    void run();

};

#endif // VIDEO_RECORD_H
