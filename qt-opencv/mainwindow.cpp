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
    current_scale = 0;
    shouldDisplayGradientMap = false;
    shouldDisplayGradientOrientation = false;

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
    cv::Mat dst = currentImage.clone();
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
    currentImage = frame.clone();

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

    currentImage = cv::imread( filename.toStdString().c_str(), CV_LOAD_IMAGE_COLOR );
    if( ! currentImage.data )
        return;

    originalImage = currentImage.clone();
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

void MainWindow::on_actionProcessing_triggered()
{
    if( ! currentImage.data || ui->actionCameraCapture->isChecked() )
        return;

    cv::Mat dst = currentImage.clone();
    if( ui->actionProcessing->isChecked() )
        dst = applyFilter( currentImage );
    cv::cvtColor( dst, dst, CV_BGR2RGB );

    QImage image = QImage( (uchar*)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888 );
    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );

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

void MainWindow::on_actionPyramid_toggled(bool toggled)
{
    if( ! currentImage.data || ui->actionCameraCapture->isChecked() )
        return;
    if(toggled){

        scaleProcesseur.load(currentImage, 4);
        currentImage = scaleProcesseur[current_scale];
        std::cout << "Pyramid toggled on" << std::endl;
    }
    else{
        currentImage = originalImage;
    }
    updateDisplay();
}

void MainWindow::setDisplayImage(cv::Mat& dst){
    QImage image;
    if(dst.channels() == 1){
        image = QImage( (uchar*)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_Grayscale8 );
    }else{
        image = QImage( (uchar*)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888 );
    }
    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );
}


void MainWindow::on_actionGradientMagnitude_toggled(bool toggle)
{
    if(toggle){
        if(shouldDisplayGradientOrientation)
           std::cout << "shouldDisplayGradientOrientation activated too" << std::endl;
    }
    shouldDisplayGradientMap = toggle;
    updateDisplay();
}

void MainWindow::on_scale_0_toggled(bool checked)
{
    if(checked){
        current_scale = 0;
        std::cout << "current scale: " << current_scale << std::endl;
        if(scaleProcesseur.ready()){
            currentImage = scaleProcesseur[current_scale];
            updateDisplay();
        }
    }
}

void MainWindow::on_scale_1_toggled(bool checked)
{
    if(checked){
        current_scale = 1;
        std::cout << "current scale: " << current_scale << std::endl;
        if(scaleProcesseur.ready()){
            currentImage = scaleProcesseur[current_scale];
            updateDisplay();
        }
    }

}

void MainWindow::on_scale_2_toggled(bool checked)
{
    if(checked){
        current_scale = 2;
        std::cout << "current scale: " << current_scale << std::endl;
        if(scaleProcesseur.ready()){
            currentImage = scaleProcesseur[current_scale];
            updateDisplay();
        }
    }
}

void MainWindow::on_scale_3_toggled(bool checked)
{
    if(checked){
        current_scale = 3;
        std::cout << "current scale: " << current_scale << std::endl;
        if(scaleProcesseur.ready()){
            currentImage = scaleProcesseur[current_scale];
            updateDisplay();
        }
    }
}

void MainWindow::updateDisplay(){
    QImage image;
    if(currentImage.channels() == 1){
        if(shouldDisplayGradientMap){
            scaleProcesseur.gradientMagnitudeMap(currentImage, current_scale);
        }
        if(shouldDisplayGradientOrientation){
            scaleProcesseur.gradientOrientationMap(currentImage, current_scale);
        }
        image = QImage( (uchar*)currentImage.data, currentImage.cols, currentImage.rows, currentImage.step, QImage::Format_Grayscale8 );
    }else{
        image = QImage( (uchar*)currentImage.data, currentImage.cols, currentImage.rows, currentImage.step, QImage::Format_RGB888 );
    }
    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );
}
