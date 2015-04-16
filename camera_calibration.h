#ifndef CAMERA_CALIBRATION_H
#define CAMERA_CALIBRATION_H

#include "opencv.hpp"

#include "QDebug"
#include "QTime"

class camera_calibration
{
public:
    camera_calibration();

    void CameraCalibration(bool ShowPts, cv::Size SizePattern, cv::Size2f SizeGrid, std::vector<std::string> files);

    void FindGetCornerPts(bool ShowPts, std::vector<std::string> files);

    void SaveIntrinsic(std::string &folder, std::string &filename);

    void DisplayUndistortedImg(bool ShowPts);

    bool loadYMLFile(const std::string &fileName);

    void undistorted(const cv::Mat &src,cv::Mat &dst);


private:

    void LoadFile(std::vector<std::string> files);

    void GetSupposePts();

    std::vector<cv::Mat> imgSrc;

    // Record images for calibration
    std::vector<std::vector<cv::Point3f> > supposePts;
    std::vector<std::vector<cv::Point2f> > PatternPts;
    cv::Size patternSize;       // Number of corner
    cv::Size2f gridSize;          // Size of grid

    // Output parameter
    cv::Mat  intrinsicMat, distortionMat;
};

#endif // CAMERA_CALIBRATION_H
