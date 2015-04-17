#include "panorama.h"

panorama::panorama(QObject *parent) : QObject(parent)
{

}

panorama::~panorama()
{

}

void panorama::calaulateHomography(const cv::Mat &sceneImg, const cv::Mat &objectImg, const int &minHessian, cv::Mat &dst)
{

    //cv::imshow("sceneImg",sceneImg);
    //cv::imshow("objectImg",objectImg);
    //int minHessian = 300; //1500;
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(minHessian);
    std::vector<cv::KeyPoint> keypointsObject,keypointsScene;

    qDebug() << "surf detect";
    surf->detect(objectImg,keypointsObject);
    surf->detect(sceneImg,keypointsScene);


    qDebug() << "surf compute";
    cv::Mat descriptorsObject, descriptorsScene;
    surf->compute(objectImg,keypointsObject,descriptorsObject);
    surf->compute(sceneImg,keypointsScene,descriptorsScene);

    qDebug() << "flannMatcher";
    cv::FlannBasedMatcher flanMatcher;
    std::vector<cv::DMatch> matches;
    flanMatcher.match(descriptorsObject, descriptorsScene, matches);
    double max_dist = 0;
    double min_dist = 75;


    for(int i = 0; i < descriptorsObject.rows; i++)
    {
        double dist = matches[i].distance;
        if(dist < min_dist)
            min_dist = dist;
        if(dist > max_dist)
            max_dist = dist;
    }

//    qDebug() << "-- Max dist : " + QString::number(max_dist);
//    qDebug() << "-- Min dist : " + QString::number(min_dist);

    //-- Use only "good" matches (i.e. whose distance is less than 3*min_dist )
    std::vector<cv::DMatch> good_matches;
    qDebug() << "choose good match";
    for(int i = 0; i < descriptorsObject.rows; i++)
    {
        if(matches[i].distance < 3*min_dist)
        {
            good_matches.push_back( matches[i]);
        }
    }
     std::vector<cv::Point2f> obj;
     std::vector<cv::Point2f> scene;

    for( int i = 0; i < good_matches.size(); i++ )
    {
     //-- Get the keypoints from the good matches
        obj.push_back( keypointsObject[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypointsScene[ good_matches[i].trainIdx ].pt );
    }

    // Find the Homography Matrix
     homography = findHomography( obj, scene, CV_RANSAC );

     cv::warpPerspective(objectImg,dst,homography,cv::Size(objectImg.cols+sceneImg.cols,objectImg.rows));
     cv::imwrite("homo.jpg",dst);
     cv::Mat half(dst,cv::Rect(0,0,sceneImg.cols,sceneImg.rows));
     sceneImg.copyTo(half);
     //cv::imshow( "Result", dst );
     cv::imwrite("result.jpg",dst);
}

void panorama::saveHomography(const std::string &fileName)
{
    if(homography.empty())
    {
        qDebug() << "Homography matrix is empty";
    }
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);

    fs << "homography" << homography;
    qDebug()<<"Homography File Saved "+QString::fromStdString(fileName);

}

void panorama::loadHomography(const std::string &fileName)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    fs["homography"] >> homography;
    qDebug()<<"Homography File Loaded "+ QString::fromStdString(fileName);

}

void panorama::panoramaThreeImgs(const std::vector<cv::Mat> &imgs, const int &&minHessian, cv::Mat &dst)
{
    cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create(minHessian);
//    cv::Ptr<cv::ORB> orb = cv::ORB::create()

    cv::Mat sceneImg = imgs[1].clone();
    cv::Mat objectImg = imgs[2].clone();

    std::vector<cv::KeyPoint> keypointsObject,keypointsScene;

    qDebug() << "surf detect";
    surf->detect(objectImg,keypointsObject);
    surf->detect(sceneImg,keypointsScene);


    qDebug() << "surf compute";
    cv::Mat descriptorsObject, descriptorsScene;
    surf->compute(objectImg,keypointsObject,descriptorsObject);
    surf->compute(sceneImg,keypointsScene,descriptorsScene);

    qDebug() << "flannMatcher";
    cv::FlannBasedMatcher flanMatcher;
    std::vector<cv::DMatch> matches;
    flanMatcher.match(descriptorsObject, descriptorsScene, matches);
    double max_dist = 0;
    double min_dist = 100;


    for(int i = 0; i < descriptorsObject.rows; i++)
    {
        double dist = matches[i].distance;
        if(dist < min_dist)
            min_dist = dist;
        if(dist > max_dist)
            max_dist = dist;
    }


    std::vector<cv::DMatch> good_matches;
    qDebug() << "choose good match";
    for(int i = 0; i < descriptorsObject.rows; i++)
    {
        if(matches[i].distance < 3*min_dist)
        {
            good_matches.push_back( matches[i]);
        }
    }
     std::vector<cv::Point2f> obj;
     std::vector<cv::Point2f> scene;

    for( int i = 0; i < good_matches.size(); i++ )
    {
     //-- Get the keypoints from the good matches
        obj.push_back( keypointsObject[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypointsScene[ good_matches[i].trainIdx ].pt );
    }

    // Find the Homography Matrix
     homographyR = findHomography( obj, scene, CV_RANSAC );
    cv::Mat temp;
    cv::warpPerspective(objectImg,temp,homographyR,cv::Size(objectImg.cols+sceneImg.cols,objectImg.rows));
    cv::Mat half(temp,cv::Rect(0,0,sceneImg.cols,sceneImg.rows));
    sceneImg.copyTo(half);


    objectImg = temp.clone();
    sceneImg = imgs[0].clone();

    keypointsObject.clear();
    keypointsScene.clear();

    qDebug() << "surf detect";
    surf->detect(objectImg,keypointsObject);
    surf->detect(sceneImg,keypointsScene);


    qDebug() << "surf compute";
    surf->compute(objectImg,keypointsObject,descriptorsObject);
    surf->compute(sceneImg,keypointsScene,descriptorsScene);

    qDebug() << "flannMatcher";
    matches.clear();
    flanMatcher.match(descriptorsObject, descriptorsScene, matches);

    for(int i = 0; i < descriptorsObject.rows; i++)
    {
        double dist = matches[i].distance;
        if(dist < min_dist)
            min_dist = dist;
        if(dist > max_dist)
            max_dist = dist;
    }


    good_matches.clear();
    qDebug() << "choose good match";
    for(int i = 0; i < descriptorsObject.rows; i++)
    {
        if(matches[i].distance < 3*min_dist)
        {
            good_matches.push_back( matches[i]);
        }
    }
    obj.clear();
    scene.clear();

    for( int i = 0; i < good_matches.size(); i++ )
    {
     //-- Get the keypoints from the good matches
        obj.push_back( keypointsObject[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypointsScene[ good_matches[i].trainIdx ].pt );
    }

    // Find the Homography Matrix
    homographyL = findHomography( obj, scene, CV_RANSAC );
    cv::warpPerspective(objectImg,dst,homographyL,cv::Size(objectImg.cols+sceneImg.cols,objectImg.rows));
    cv::Mat half_2(dst,cv::Rect(0,0,sceneImg.cols,sceneImg.rows));
    sceneImg.copyTo(half_2);
    cv::imwrite("result.jpg",dst);
}

void panorama::saveTwoHomography(const std::string &fileName)
{
    if(homography.empty())
    {
        qDebug() << "Homography matrix is empty";
    }
    cv::FileStorage fs(fileName, cv::FileStorage::WRITE);

    fs << "homographyR" << homographyR;
    fs << "homographyL" << homographyL;
    qDebug()<<"Homography File Saved "+QString::fromStdString(fileName);
}

void panorama::loadTwoHomography(const std::string &fileName)
{
    cv::FileStorage fs(fileName, cv::FileStorage::READ);
    fs["homographyR"] >> homographyR;
    fs["homographyL"] >> homographyL;
    qDebug()<<"Homography File Loaded "+ QString::fromStdString(fileName);
}

void panorama::warpingThreeImgs(const std::vector<cv::Mat> &imgs,cv::Mat &dst)
{
    QTime t;
    //t.start();
    cv::Mat temp;
    cv::warpPerspective(imgs[2],temp,homographyR,cv::Size(imgs[2].cols+imgs[1].cols,imgs[2].rows));
    cv::Mat half(temp,cv::Rect(0,0,imgs[1].cols,imgs[1].rows));
    imgs[1].copyTo(half);

    cv::warpPerspective(temp,dst,homographyL,cv::Size(temp.cols+imgs[0].cols,temp.rows));
    cv::Mat half_2(dst,cv::Rect(0,0,imgs[0].cols,imgs[0].rows));
    imgs[0].copyTo(half_2);

    cv::imwrite("result.jpg",dst);

    std::cout  << "yaya"<< t.elapsed() << "/n";


}

