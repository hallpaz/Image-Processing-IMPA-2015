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
    cv::Mat applyFilter( cv::Mat &cvImage );
    
protected:
    cv::Mat m_cvImage;
    cv::VideoCapture m_cvCamera;
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
