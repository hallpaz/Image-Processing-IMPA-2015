#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    shouldApplyHarrisDetector = false;

    m_timer.start(20);
    connect( &m_timer, SIGNAL(timeout()), this, SLOT(captureAndShowVideoFrame()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

cv::Mat MainWindow::applyHarrisCornerDetector( cv::Mat &cvImage )
{
    //NOTE: Example using blur filtering
    cv::Mat dst = currentImage.clone();
    cout << "should be applying Harris Corner Detector" << endl;

    return dst;
}

void MainWindow::captureAndShowVideoFrame()
{
    if( ! m_cvCamera.isOpened() )
        return;

    cv::Mat frame;
    m_cvCamera >> frame;
    currentImage = frame.clone();
    cout << frame.channels() << endl;

    updateDisplay();
}

void MainWindow::on_actionLoadImage_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load an image");
    if( filename.isEmpty() )
        return;

    currentImage = cv::imread( filename.toStdString().c_str(), CV_LOAD_IMAGE_COLOR );
    if( ! currentImage.data )
        return;

    cv::Mat cvRGBImage( currentImage.rows, currentImage.cols, currentImage.type() );
    cv::cvtColor( currentImage, cvRGBImage, CV_BGR2RGB );

    QImage image = QImage( (uchar*)cvRGBImage.data, cvRGBImage.cols, cvRGBImage.rows, cvRGBImage.step, QImage::Format_RGB888 );
    if( image.isNull() )
        return;

    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );

}

void MainWindow::on_actionSaveImage_triggered()
{

    if( ! currentImage.data )
        return;

    QString filename = QFileDialog::getSaveFileName(this, "Save image");
    if( filename.isEmpty() )
        return;

#if 1
    ui->imageLabel->pixmap()->save(filename);
#else
    if( m_cvImage.data )
        cv::imwrite( filename.toStdString(), m_cvImage );
#endif

}

void MainWindow::on_actionReset_triggered()
{
    if( ! currentImage.data )
        return;

    cv::Mat cvRGBImage( currentImage.rows, currentImage.cols, currentImage.type() );
    cv::cvtColor( currentImage, cvRGBImage, CV_BGR2RGB );

    QImage image = QImage( (uchar*)cvRGBImage.data, cvRGBImage.cols, cvRGBImage.rows, cvRGBImage.step, QImage::Format_RGB888 );
    if( image.isNull() )
        return;

    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );
}


void MainWindow::on_actionCameraCapture_toggled(bool toggle)
{
    if( toggle )
    {
        if( ! m_cvCamera.isOpened() )
        {
            //NOTE: Open the first camera
            m_cvCamera.open(CV_CAP_OPENNI_BGR_IMAGE);
        }
        ui->actionLoadImage->setDisabled( true );
        ui->actionSaveImage->setDisabled( true );
        ui->actionReset->setDisabled( true );
    }
    else
    {
        if( m_cvCamera.isOpened() )
        {
            m_cvCamera.release();
        }
        ui->actionLoadImage->setDisabled( false );
        ui->actionSaveImage->setDisabled( false );
        ui->actionReset->setDisabled( false );

    }
}


void MainWindow::updateDisplay(){
    cout << "update display" << endl;
    QImage image;
    if(currentImage.channels() == 1){
        if(shouldApplyHarrisDetector){
            //scaleProcesseur.gradientMagnitudeMap(currentImage, current_scale);
            cout << "Should apply Harris Corner Detector" << endl;
        }
        image = QImage( (uchar*)currentImage.data, currentImage.cols, currentImage.rows, currentImage.step, QImage::Format_Grayscale8 );
    }else{
        image = QImage( (uchar*)currentImage.data, currentImage.cols, currentImage.rows, currentImage.step, QImage::Format_RGB888 );
    }

    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );
}

void MainWindow::on_actionHarris_toggled(bool toggle)
{
    shouldApplyHarrisDetector = toggle;
    updateDisplay();
}
