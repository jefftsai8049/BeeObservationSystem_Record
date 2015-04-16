#ifndef PANORAMA_H
#define PANORAMA_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QTime>

#include "stdlib.h"

#include "opencv.hpp"
#include "features2d.hpp"
#include "xfeatures2d.hpp"

class panorama : public QObject
{
    Q_OBJECT
public:
    explicit panorama(QObject *parent = 0);
    ~panorama();

    //two images panorama
    void calaulateHomography(const cv::Mat &sceneImg, const cv::Mat &objectImg, const int &minHessian, cv::Mat &dst);

    void saveHomography(const std::string &fileName);

    void loadHomography(const std::string &fileName);
    //three images panorama(form left to right)
    void panoramaThreeImgs(const std::vector<cv::Mat> &imgs, const int &&minHessian, cv::Mat &dst);

    void saveTwoHomography(const std::string &fileName);

    void loadTwoHomography(const std::string &fileName);

    void warpingThreeImgs(const std::vector<cv::Mat> &imgs, cv::Mat &dst);


signals:

public slots:

private:

    cv::Mat homography;

    cv::Mat homographyR;
    cv::Mat homographyL;
};

#endif // PANORAMA_H
