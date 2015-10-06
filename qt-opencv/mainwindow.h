#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>

#include "scalespacecomputer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setDisplayImage(cv::Mat& dst);

protected:
    cv::Mat applyFilter( cv::Mat &cvImage );
    
protected:
    cv::Mat currentImage;
    cv::VideoCapture m_cvCamera;
    ScaleSpaceComputer scaleProcesseur;
    QTimer m_timer;

protected slots:
    void captureAndShowVideoFrame();

private slots:
    void on_actionLoadImage_triggered();

    void on_actionSaveImage_triggered();

    void on_actionProcessing_triggered();

    void on_actionReset_triggered();

    void on_actionCameraCapture_triggered();

    void on_actionCameraCapture_toggled(bool toggle);

    void on_actionPyramid_triggered();

    void on_actionGradientMagnitude_toggled(bool arg1);

    void on_scale_0_toggled(bool checked);

    void on_scale_1_toggled(bool checked);

    void on_scale_2_toggled(bool checked);

    void on_scale_3_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    int current_scale;
};

#endif // MAINWINDOW_H
