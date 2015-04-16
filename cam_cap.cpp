#include "cam_cap.h"


cam_cap::cam_cap(const std::vector<int> pos, QObject *parent) :
    QThread(parent)
{
    this->camPos.resize(pos.size());
    //setting capture parameter
    for(int i=0;i<pos.size();i++)
    {
        this->camPos[i] = pos[i];
    }


    this->capStatus = false;
    this->capEnd = false;
    //load calibration model file
    cc = new camera_calibration;
    calibrationLoaded = 0;
    cc->loadYMLFile("cam_init.yml");


}

cam_cap::~cam_cap()
{

    //delete imgProcess;
    delete cc;

}

void cam_cap::run()
{

    capL = new cv::VideoCapture(this->camPos[0]);
    capM = new cv::VideoCapture(this->camPos[1]);
    capR = new cv::VideoCapture(this->camPos[2]);
    capFrame.resize(3);

    //read capture img
    this->capStatus = true;
    while(capL->isOpened() && capM->isOpened() && capR->isOpened() && this->capStatus)
    {
        capL->read(this->capFrame[0]);
        capM->read(this->capFrame[1]);
        capR->read(this->capFrame[2]);
        for(int i=0;i<this->capFrame.size();i++)
        {
            cv::transpose(this->capFrame[i],this->capFrame[i]);
            cv::flip(this->capFrame[i],this->capFrame[i],1);



        }
        if(calibrationLoaded)
        {
            std::vector<cv::Mat> undistorted;
            undistorted.resize(3);
            cc->undistorted(capFrame[0],undistorted[0]);
            cc->undistorted(capFrame[1],undistorted[1]);
            cc->undistorted(capFrame[2],undistorted[2]);
            emit capSend(undistorted);
        }
        else
        {
            emit capSend(capFrame);
        }
    }
    this->capEnd = true;
    capL->release();
    capM->release();
    capR->release();
    cv::destroyAllWindows();
}
//stop camera capture
void cam_cap::capStop()
{
    this->capStatus = false;
}

bool cam_cap::isCamEnd()
{
    return this->capEnd;
}
//check camera status(connectting or not)
bool cam_cap::camStatus()
{
    return this->capStatus;
}

void cam_cap::setUndistorted(const bool &status)
{
    calibrationLoaded = status;
}

