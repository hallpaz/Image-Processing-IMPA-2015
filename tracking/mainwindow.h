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
    void calcOpticalFlowArrows();
    void calcOpticalFlowColor();
    void updateDisplay();
    
protected:
    cv::Mat firstImage, secondImage, flowImage, currentImage;
    unsigned int levels, win_size, iterations, poly_n;
    float poly_sigma;
    int gaussian_flag;
    bool shouldRecalculate;

    cv::VideoCapture m_cvCamera;
    QTimer m_timer;

protected slots:
    void captureAndShowVideoFrame();

private slots:
    void on_actionLoadImage_triggered();

    void on_actionSaveImage_triggered();

    void on_actionProcessing_triggered();

    void on_actionCameraCapture_toggled(bool toggle);

    void on_levels_box_valueChanged(int arg1);

    void on_win_box_valueChanged(int arg1);

    void on_iterations_box_valueChanged(int arg1);

    void on_polyn_box_valueChanged(int arg1);

    void on_polysigma_box_valueChanged(double arg1);

    void on_first_image_radio_toggled(bool checked);

    void on_second_image_radio_toggled(bool checked);

    void on_flow_image_radio_toggled(bool checked);

    void on_gaussian_check_toggled(bool checked);

    void on_flow_arrow_radio_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
