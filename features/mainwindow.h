#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void applyHarrisCornerDetector();
    void applyAKAZEDetector();
    
protected:
    cv::Mat currentImage;
    cv::VideoCapture m_cvCamera;
    QTimer m_timer;

protected slots:
    void captureAndShowVideoFrame();

private slots:
    void on_actionLoadImage_triggered();

    void on_actionSaveImage_triggered();

    void on_actionCameraCapture_toggled(bool toggle);

    void on_actionHarris_toggled(bool arg1);

    void on_thresholdSlider_sliderMoved(int position);

    void on_apertureSpinBox_valueChanged(double arg1);

    void on_blockSpinBox_valueChanged(double arg1);

    void on_actionSift_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    void updateDisplay();
    bool shouldApplyHarrisDetector;
    bool shouldApplyAKAZEDetector;
    int blockSize, apertureSize, threshold;
    double k;
    cv::AKAZE *akazeDetector;
};

#endif // MAINWINDOW_H
