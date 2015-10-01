#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //m_timer.start(20);
    //connect( &m_timer, SIGNAL(timeout()), this, SLOT(captureAndShowVideoFrame()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

cv::Mat MainWindow::applyFilter( cv::Mat &cvImage )
{
    //NOTE: Example using blur filtering
    cv::Mat dst = m_cvImage.clone();
#if 1
    const int maxKernelLength = 31;
    for( int i=1; i < maxKernelLength; i += 2 )
    {
        cv::blur( cvImage, dst, cv::Size(i,i) );
    }
#else
    cv::GaussianBlur(cvImage, dst, cv::Size(7,7), 50.5, 50.5);
#endif

    return dst;
}

void MainWindow::captureAndShowVideoFrame()
{
    if( ! m_cvCamera.isOpened() )
        return;

    cv::Mat frame;
    m_cvCamera >> frame;
    m_cvImage = frame.clone();

    if( ui->actionProcessing->isChecked() )
        frame = applyFilter( frame );

    cv::Mat cvRGBImage( frame.rows, frame.cols, frame.type() );
    cv::cvtColor( frame, cvRGBImage, CV_BGR2RGB );

    QImage image = QImage( (uchar*)cvRGBImage.data, cvRGBImage.cols, cvRGBImage.rows, cvRGBImage.step, QImage::Format_RGB888 );
    if( image.isNull() )
        return;

    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );

}

void MainWindow::on_actionLoadImage_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load an image");
    if( filename.isEmpty() )
        return;

    m_cvImage = cv::imread( filename.toStdString().c_str(), CV_LOAD_IMAGE_COLOR );
    if( ! m_cvImage.data )
        return;

    cv::Mat cvRGBImage( m_cvImage.rows, m_cvImage.cols, m_cvImage.type() );
    cv::cvtColor( m_cvImage, cvRGBImage, CV_BGR2RGB );

    QImage image = QImage( (uchar*)cvRGBImage.data, cvRGBImage.cols, cvRGBImage.rows, cvRGBImage.step, QImage::Format_RGB888 );
    if( image.isNull() )
        return;

    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );

}

void MainWindow::on_actionSaveImage_triggered()
{

    if( ! m_cvImage.data )
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

void MainWindow::on_actionProcessing_triggered()
{
    if( ! m_cvImage.data || ui->actionCameraCapture->isChecked() )
        return;

    cv::Mat dst = m_cvImage.clone();
    if( ui->actionProcessing->isChecked() )
        dst = applyFilter( m_cvImage );
    cv::cvtColor( dst, dst, CV_BGR2RGB );

    QImage image = QImage( (uchar*)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888 );
    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );

}

void MainWindow::on_actionReset_triggered()
{
    if( ! m_cvImage.data )
        return;

    cv::Mat cvRGBImage( m_cvImage.rows, m_cvImage.cols, m_cvImage.type() );
    cv::cvtColor( m_cvImage, cvRGBImage, CV_BGR2RGB );

    QImage image = QImage( (uchar*)cvRGBImage.data, cvRGBImage.cols, cvRGBImage.rows, cvRGBImage.step, QImage::Format_RGB888 );
    if( image.isNull() )
        return;

    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );
}

void MainWindow::on_actionCameraCapture_triggered()
{
}

void MainWindow::on_actionCameraCapture_toggled(bool toggle)
{
    if( toggle )
    {
        if( ! m_cvCamera.isOpened() )
        {
            //NOTE: Open the first camera
            m_cvCamera.open(0);
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
        this->on_actionProcessing_triggered();

    }
}
