#ifndef CAM_CAP_H
#define CAM_CAP_H

#include <QThread>
#include <QDebug>
#include <QTime>

#include "opencv.hpp"
#include "camera_calibration.h"

class cam_cap : public QThread
{
    Q_OBJECT
public:
    explicit cam_cap(const std::vector<int> pos, QObject *parent = 0);
    ~cam_cap();
    void capStop();
//    void setCapPosition(const int &pos);
    bool isCamEnd();
    bool camStatus();
    void setUndistorted(const bool &status);
signals:
    void capSend(const std::vector<cv::Mat> &src);
public slots:

private:
    cv::VideoCapture *capL;
    cv::VideoCapture *capM;
    cv::VideoCapture *capR;
//    img_process *imgProcess;
    camera_calibration *cc;

//    std::string cap_name;
    std::vector<int> camPos;
    std::vector<cv::Mat> capFrame;
    bool capStatus;
    bool capEnd;

    bool calibrationLoaded;

    void run();


};

#endif // CAM_CAP_H
