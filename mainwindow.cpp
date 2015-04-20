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
    //    connect(vr,SIGNAL(msgSend(QString)),this,SLOT(vrReceive(QString)));
    recordTime = new QDateTime;

    progress = 0;
    ui->progressBar->setValue((int)progress);

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
    vr->deleteLater();
}

void MainWindow::capReceive(const std::vector<cv::Mat> &src)
{



    if(getImageStatus)
    {
        cameraImage[0] = src[0].clone();
        cameraImage[1] = src[1].clone();
        cameraImage[2] = src[2].clone();
        QDateTime t;
        t = t.currentDateTime();
        cv::imwrite("snapshot/"+t.toString("yy-MM-dd-HH-mm-ss").toStdString()+"_R.jpg",cameraImage[0]);
        cv::imwrite("snapshot/"+t.toString("yy-MM-dd-HH-mm-ss").toStdString()+"_M.jpg",cameraImage[1]);
        cv::imwrite("snapshot/"+t.toString("yy-MM-dd-HH-mm-ss").toStdString()+"_L.jpg",cameraImage[2]);
        getImageStatus = false;
        getImageOK = true;
    }

    cv::Mat dst;

    dst.create(src[0].rows,src[0].cols+src[1].cols+src[2].cols,src[0].type());
    cv::Mat part = dst(cv::Rect(0,0,src[0].cols,src[0].rows));
    src[0].copyTo(part);
    part = dst(cv::Rect(src[0].cols,0,src[1].cols,src[1].rows));
    src[1].copyTo(part);
    part = dst(cv::Rect(src[0].cols+src[1].cols,0,src[2].cols,src[2].rows));
    src[2].copyTo(part);
    //qDebug() << vr->isVideoStart();


    if(ui->show_image_checkBox->isChecked())
    {
        cv::Mat resizeDst;
        cv::resize(dst,resizeDst,cv::Size(1800,800));
        cv::imshow("dst",resizeDst);
    }

    if(vr->isVideoStart())
    {
//        qDebug() << progress;
        progress = progress+100.0/ui->record_time_spinBox->value()/60.0/12.0;
        ui->progressBar->setValue(progress);
        vr->videoWrite(dst);
        vr->start();
    }
}

void MainWindow::fpsReceive(const int &time)
{
    ui->fps_lcdNumber->display(1000/time);
}

void MainWindow::recordClockTimeout()
{

    progress = 0;
    ui->progressBar->setValue(progress);

    if(vr->isVideoStart())
    {
//        qDebug() <<vr->isVideoStart();
//        recordClock->stop();
        vr->videoEnd();
//        qDebug() << vr->isRunning();
        while(vr->isRunning()){}
    }



    *recordTime = recordTime->currentDateTime();
    QString fileName = recordTime->toString("yy-MM-dd-HH-mm-ss");

    vr->videoStart("video/"+fileName+"_raw.avi");
    ui->statusBar->showMessage(fileName+"_raw.avi is recording...");
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
    ui->get_image_pushButton->setEnabled(1);


    std::vector<int> camPos;
    camPos.resize(3);
    camPos[0] = ui->cam_ID_L_spinBox->value();
    camPos[1] = ui->cam_ID_M_spinBox->value();
    camPos[2] = ui->cam_ID_R_spinBox->value();
    cam = new cam_cap(camPos);
    if(cam != 0)
    {
        connect(cam,SIGNAL(capSend(std::vector<cv::Mat>)),this,SLOT(capReceive(std::vector<cv::Mat>)));
        connect(cam,SIGNAL(fpsSend(int)),this,SLOT(fpsReceive(int)));
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
    ui->statusBar->showMessage("Camera Disconnected!");

    while(cam->isCamEnd() == true)
    {
        disconnect(cam,SIGNAL(fpsSend(int)),this,SLOT(fpsReceive(int)));
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

    int timeInterval = ui->record_time_spinBox->value()*1000*60; //to msec
    recordClock = new QTimer;
    recordClock->setInterval(timeInterval);
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




void MainWindow::on_get_image_pushButton_clicked()
{
    getCameraImage();
}

void MainWindow::on_show_image_checkBox_clicked()
{
    if(!ui->show_image_checkBox->isChecked())
    {
        cv::destroyAllWindows();
    }
}

void MainWindow::on_calibration_checkBox_clicked()
{
    cam->setCalibration(ui->calibration_checkBox->isChecked());
}
