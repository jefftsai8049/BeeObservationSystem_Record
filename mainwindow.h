#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QTimer>
#include <QReadWriteLock>

#include "stdlib.h"
#include "vector"

#include "opencv.hpp"
#include "stitching.hpp"

#include "cam_cap.h"
#include "video_record.h"
#include "camera_calibration.h"
#include "panorama.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent (QCloseEvent *event);

private slots:
    void capReceive(const std::vector<cv::Mat> &src);

    void fpsReceive(const int &time);

    void recordClockTimeout();

    void getCameraImage();

    void on_connect_camera_pushButton_clicked();

    void on_disconnect_camera_pushButton_clicked();

    void on_video_record_pushButton_clicked();

    void on_video_stop_pushButton_clicked();

    void on_get_image_pushButton_clicked();

    void on_show_image_checkBox_clicked();



    void on_calibration_checkBox_clicked();

private:
    Ui::MainWindow *ui;

    cam_cap *cam;

    video_record *vr;

    camera_calibration *cc;

    QDateTime *recordTime;

    QTimer *recordClock;

    double progress;

    bool getImageStatus;

    bool getImageOK;

    std::vector<cv::Mat> cameraImage;



};

#endif // MAINWINDOW_H
