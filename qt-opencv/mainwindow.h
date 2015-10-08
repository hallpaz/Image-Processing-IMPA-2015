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
    void updateDisplay();

protected:
    cv::Mat applyFilter( cv::Mat &cvImage );
    
protected:
    cv::Mat currentImage, originalImage;
    cv::VideoCapture m_cvCamera;
    ScaleSpaceComputer scaleProcesseur;
    QTimer m_timer;
    bool shouldDisplayGradientMap;
    bool shouldDisplayGradientOrientation;

protected slots:
    void captureAndShowVideoFrame();

private slots:
    void on_actionLoadImage_triggered();

    void on_actionSaveImage_triggered();

    void on_actionProcessing_triggered();

    void on_actionReset_triggered();

    void on_actionCameraCapture_triggered();

    void on_actionCameraCapture_toggled(bool toggle);

    void on_actionGradientMagnitude_toggled(bool arg1);

    void on_scale_0_toggled(bool checked);

    void on_scale_1_toggled(bool checked);

    void on_scale_2_toggled(bool checked);

    void on_scale_3_toggled(bool checked);

    void on_actionPyramid_toggled(bool toggle);

private:
    Ui::MainWindow *ui;
    int current_scale;
    bool shouldRescale;
};

#endif // MAINWINDOW_H
