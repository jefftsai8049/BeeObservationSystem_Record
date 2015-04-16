#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T15:17:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BeeObservationSystem_Record
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cam_cap.cpp \
    camera_calibration.cpp \
    video_record.cpp \
    panorama.cpp

HEADERS  += mainwindow.h \
    cam_cap.h \
    camera_calibration.h \
    video_record.h \
    panorama.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\\opencv300b_x64_extra_vc2013_cuda70\\include \
                C:\\opencv300b_x64_extra_vc2013_cuda70\\include\\opencv \
                C:\\opencv300b_x64_extra_vc2013_cuda70\\include\\opencv2 \

#debug libs
LIBS += C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_bgsegm300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_bioinspired300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_calib3d300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_ccalib300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_core300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudaarithm300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudabgsegm300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudacodec300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudafeatures2d300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudafilters300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudaimgproc300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudalegacy300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudaobjdetect300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudaoptflow300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudastereo300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudawarping300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudev300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_datasets300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_face300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_features2d300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_flann300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_highgui300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_imgcodecs300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_imgproc300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_latentsvm300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_line_descriptor300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_ml300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_objdetect300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_optflow300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_photo300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_reg300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_rgbd300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_saliency300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_shape300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_stitching300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_superres300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_surface_matching300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_text300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_tracking300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_ts300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_video300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_videoio300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_videostab300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_xfeatures2d300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_ximgproc300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_xobjdetect300d.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_xphoto300d.lib \
#release libs
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_bgsegm300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_bioinspired300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_calib3d300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_ccalib300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_core300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudaarithm300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudabgsegm300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudacodec300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudafeatures2d300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudafilters300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudaimgproc300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudalegacy300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudaobjdetect300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudaoptflow300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudastereo300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudawarping300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_cudev300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_datasets300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_face300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_features2d300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_flann300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_highgui300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_imgcodecs300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_imgproc300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_latentsvm300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_line_descriptor300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_ml300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_objdetect300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_optflow300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_photo300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_reg300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_rgbd300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_saliency300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_shape300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_stitching300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_superres300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_surface_matching300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_text300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_tracking300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_ts300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_video300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_videoio300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_videostab300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_xfeatures2d300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_ximgproc300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_xobjdetect300.lib \
        C:\\opencv300b_x64_extra_vc2013_cuda70\\lib\\opencv_xphoto300.lib \


