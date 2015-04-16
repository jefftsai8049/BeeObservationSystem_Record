#include "mainwindow.h"
#include "ui_mainwindow.h"
QReadWriteLock lock;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qRegisterMetaType< std::vector<cv::Mat> >("std::vector<cv::Mat>");
    cam = 0;

    vr = new video_record(cv::Size(3600,1600));
    recordTime = new QDateTime;

    progress = 0;
    ui->progressBar->setValue((int)progress);

    pano = new panorama;
    cc = new camera_calibration;

    getImageStatus = false;
    getImageOK =false;
}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::closeEvent(QCloseEvent *event)
{

    if(cam == 0)
        return;



    if(!cam->isFinished())
    {
        cam->capStop();
        while(cam->isCamEnd() == true)
        {
            delete cam;
        }
    }

//this->on_video_stop_pushButton_clicked();
    vr->deleteLater();
}

void MainWindow::capReceive(const std::vector<cv::Mat> &src)
{



//            QTime t;
//            t.start();
    if(getImageStatus)
    {
        qDebug() <<  "okok";
        cameraImage[0] = src[0].clone();
        cameraImage[1] = src[1].clone();
        cameraImage[2] = src[2].clone();
//        QTime t;
//        t.currentTime();
//        cv::imwrite(t.toString("yy-MM-dd-HH-mm-ss").toStdString()+"_R.jpg",cameraImage[0]);
//        cv::imwrite(t.toString("yy-MM-dd-HH-mm-ss").toStdString()+"_M.jpg",cameraImage[1]);
//        cv::imwrite(t.toString("yy-MM-dd-HH-mm-ss").toStdString()+"_L.jpg",cameraImage[2]);
        getImageStatus = false;
        getImageOK = true;

//        cv::imshow("test1",cameraImage[0]);
    }

    cv::Mat dst;
    dst.create(src[0].rows,src[0].cols+src[1].cols+src[2].cols,src[0].type());
    cv::Mat part = dst(cv::Rect(0,0,src[0].cols,src[0].rows));
    src[0].copyTo(part);
    part = dst(cv::Rect(src[0].cols,0,src[1].cols,src[1].rows));
    src[1].copyTo(part);
    part = dst(cv::Rect(src[0].cols+src[1].cols,0,src[2].cols,src[2].rows));
    src[2].copyTo(part);

    if(ui->show_image_checkBox->isChecked())
    {
        cv::Mat resizeDst;
        cv::resize(dst,resizeDst,cv::Size(1800,800));
        cv::imshow("dst",resizeDst);
    }
    if(vr->isVideoStart())
    {
        progress = progress+100.0/ui->record_time_spinBox->value()/60.0/12.0;
        ui->progressBar->setValue(progress);
        vr->videoWrite(dst);
        vr->start();
    }
    //qDebug() << t.elapsed();
//    cv::resize(dst,dst,cv::Size((src[0].cols+src[1].cols+src[2].cols)/4,src[0].rows/4));
//    cv::imshow("image",dst);

}

void MainWindow::recordClockTimeout()
{
    qDebug() << "record clock restart!";

    progress = 0;
    ui->progressBar->setValue(progress);

    if(vr->isVideoStart())
    {
        qDebug() << "end";
        vr->videoEnd();
    }

    *recordTime = recordTime->currentDateTime();
    QString fileName = recordTime->toString("yy-MM-dd-HH-mm-ss");

    vr->videoStart("video/"+fileName+"_raw.avi");
    //    ui->statusBar->showMessage(fileName+"_raw.avi is recording...");
}

void MainWindow::getCameraImage()
{
    cameraImage.clear();
    cameraImage.resize(3);
    getImageStatus = true;
    getImageOK = false;
}

void MainWindow::on_connect_camera_pushButton_clicked()
{
    ui->connect_camera_pushButton->setEnabled(0);
    ui->disconnect_camera_pushButton->setEnabled(1);
    ui->video_record_pushButton->setEnabled(1);


    std::vector<int> camPos;
    camPos.resize(3);
    camPos[0] = ui->cam_ID_L_spinBox->value();
    camPos[1] = ui->cam_ID_M_spinBox->value();
    camPos[2] = ui->cam_ID_R_spinBox->value();
    cam = new cam_cap(camPos);
    if(cam != 0)
    {
        connect(cam,SIGNAL(capSend(std::vector<cv::Mat>)),this,SLOT(capReceive(std::vector<cv::Mat>)));
        cam->start();
        ui->statusBar->showMessage("Camera Connected!");
    }




}

void MainWindow::on_disconnect_camera_pushButton_clicked()
{
    ui->disconnect_camera_pushButton->setEnabled(0);
    ui->connect_camera_pushButton->setEnabled(1);
    ui->video_record_pushButton->setEnabled(0);
    ui->video_stop_pushButton->setEnabled(0);

    cam->capStop();

    while(cam->isCamEnd() == true)
    {

        disconnect(cam,SIGNAL(capSend(std::vector<cv::Mat>)),this,SLOT(capReceive(std::vector<cv::Mat>)));
        delete cam;
    }


}

void MainWindow::on_video_record_pushButton_clicked()
{
    ui->statusBar->showMessage("Video record start!");
    ui->video_stop_pushButton->setEnabled(1);
    ui->video_record_pushButton->setEnabled(0);


    this->recordClockTimeout();

    recordClock = new QTimer;
    recordClock->setInterval(1000*60*30);
    connect(recordClock,SIGNAL(timeout()),this,SLOT(recordClockTimeout()));
    recordClock->start();





}

void MainWindow::on_video_stop_pushButton_clicked()
{
    ui->video_record_pushButton->setEnabled(1);
    ui->video_stop_pushButton->setEnabled(0);

    recordClock->stop();
    vr->videoEnd();


    ui->statusBar->showMessage("Video record end!");
}

void MainWindow::on_stitch_image_pushButton_clicked()
{
    ui->get_image_pushButton->setEnabled(true);
    ui->stitch_image_pushButton->setEnabled(false);
    cc = new camera_calibration;
    pano = new panorama;

    if(!cc->loadYMLFile("cam_init.yml"))
    {
        ui->statusBar->showMessage("Load Camera Calibration File Failure!");
        return;
    }

    if(getImageStatus == false && getImageOK == true)
    {
        //cv::imshow("test",cameraImage[0]);
        std::vector<cv::Mat> undistorted;
        undistorted.resize(3);
        for(int i=0;i<3;i++)
        {
//            cv::cvtColor(cameraImage[i],cameraImage[i],cv::COLOR_BGR2GRAY);
//            cv::equalizeHist(cameraImage[i],cameraImage[i]);
            cc->undistorted(cameraImage[i],undistorted[i]);
//            cv::cvtColor(cameraImage[i],cameraImage[i],cv::COLOR_GRAY2BGR);
        }
//        int minHessian = ui->stitich_match_point_spinBox->value();
//        cv::detail::FeaturesFinder detector = cv::detail::SurfFeaturesFinder(minHessian);
//        cv::detail::ImageFeatures obj,scn;

//        detector.find(undistorted[0],scn);
//        detector.find(undistorted[1],obj);

//        cv::detail::FeaturesMatcher matcher;
//        matcher.match(obj,scn);

//        cv::detail::PlaneWarper warper;
//        warper.warp()

        cv::Mat dst;
        cv::Stitcher stitcher = cv::Stitcher::createDefault(false);
        //cv::Ptr<cv::WarperCreator> warper = cv::PlaneWarper();
        stitcher.setWarper(new cv::PlaneWarper());
        stitcher.setFeaturesFinder(new cv::detail::SurfFeaturesFinder(300));
        stitcher.setWaveCorrectKind(cv::detail::WAVE_CORRECT_HORIZ);
        //stitcher.stitch(undistorted,dst);
        stitcher.estimateTransform(undistorted);
        qDebug() << "okokok";
        stitcher.composePanorama(undistorted,dst);

//        cv::Mat dst;
//        pano->panoramaThreeImgs(cameraImage,ui->stitich_match_point_spinBox->value(),dst);
//        pano->saveTwoHomography("homography.yml");
//        cv::resize(dst,dst,cv::Size(1800,800));
        cv::imshow("Stitch",dst);
    }
    delete cc;
    delete pano;

    //cc->undistorted(cap_frame,undistorted);
}

void MainWindow::on_get_image_pushButton_clicked()
{
    ui->get_image_pushButton->setEnabled(false);
    ui->stitch_image_pushButton->setEnabled(true);
    getCameraImage();
}

void MainWindow::on_show_image_checkBox_clicked()
{
    if(!ui->show_image_checkBox->isChecked())
    {
        cv::destroyAllWindows();
    }
}

void MainWindow::on_warp_image_pushButton_clicked()
{
    pano = new panorama;
    pano->loadTwoHomography("homography.yml");
    std::vector<cv::Mat> undistorted;
    undistorted.resize(3);
    for(int i=0;i<3;i++)
    {
//            cv::cvtColor(cameraImage[i],cameraImage[i],cv::COLOR_BGR2GRAY);
//            cv::equalizeHist(cameraImage[i],cameraImage[i]);
        cc->undistorted(cameraImage[i],undistorted[i]);
//            cv::cvtColor(cameraImage[i],cameraImage[i],cv::COLOR_GRAY2BGR);
    }
        cv::Mat dst;
        pano->warpingThreeImgs(undistorted,dst);
        cv::imshow("yaya",dst);
        delete pano;
}
