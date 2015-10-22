#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <iostream>

using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    shouldApplyHarrisDetector = false;
    shouldApplySIFTDetector = false;
    blockSize = 2; ui->blockSpinBox->setValue(blockSize);
    apertureSize = 3; ui->apertureSpinBox->setValue(apertureSize);
    k = 0.04;
    threshold = 200; ui->thresholdSlider->setValue(threshold);
    ui->threshold_value->setText(QString::number(threshold));
    akazeDetector = AKAZE::create();

    m_timer.start(50);
    connect( &m_timer, SIGNAL(timeout()), this, SLOT(captureAndShowVideoFrame()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::applyHarrisCornerDetector()
{
    //NOTE: Example using blur filtering
    if(shouldApplySIFTDetector){
        ui->actionSift->toggle();
    }
    cv::Mat dst;

    cvtColor(currentImage, dst, COLOR_BGR2GRAY );
    cornerHarris( dst, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
    normalize( dst, dst, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    //convertScaleAbs( dst_norm, dst_norm_scaled );
    for( int j = 0; j < dst.rows ; j++ )
       { for( int i = 0; i < dst.cols; i++ )
            {
              if( (int) dst.at<float>(j,i) > threshold )
                {
                 circle( currentImage, Point( i, j ), 5,  Scalar(0, 255, 0), 2, 8, 0 );
                }
            }
       }

    return;
}

void MainWindow::applySIFTDetector()
{
    //cv::SiftFeatureDetector detector;
    Mat dst;
    vector<KeyPoint> keypoints;

    cvtColor(currentImage, dst, COLOR_BGR2GRAY );
    akazeDetector->detect(dst, keypoints);

    // If you would like to draw the detected keypoint just to check
    //Mat outputImage;
    Scalar keypointColor = Scalar(255, 0, 0);     // Blue keypoints.
    //drawKeypoints(currentImage, keypoints, currentImage, keypointColor, DrawMatchesFlags::DEFAULT);
    drawKeypoints(dst, keypoints, currentImage, keypointColor);

}

void MainWindow::captureAndShowVideoFrame()
{
    if( ! m_cvCamera.isOpened() )
        return;

    cv::Mat frame;
    m_cvCamera >> frame;
    cvtColor(frame.clone(), currentImage, CV_BGR2RGB);
    //cout << frame.channels() << endl;

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

    //cv::Mat cvRGBImage( currentImage.rows, currentImage.cols, currentImage.type() );
    cv::cvtColor( currentImage, currentImage, CV_BGR2RGB );
    updateDisplay();

    /*QImage image = QImage( (uchar*)cvRGBImage.data, cvRGBImage.cols, cvRGBImage.rows, cvRGBImage.step, QImage::Format_RGB888 );
    if( image.isNull() )
        return;

    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );*/

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


void MainWindow::on_actionCameraCapture_toggled(bool toggle)
{
    if( toggle )
    {
        if( ! m_cvCamera.isOpened() )
        {
            //NOTE: Open the first camera
            m_cvCamera.open(0);
            m_cvCamera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
            m_cvCamera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
        }
        ui->actionLoadImage->setDisabled( true );
        ui->actionSaveImage->setDisabled( true );
    }
    else
    {
        if( m_cvCamera.isOpened() )
        {
            m_cvCamera.release();
        }
        ui->actionLoadImage->setDisabled( false );
        ui->actionSaveImage->setDisabled( false );
    }
}


void MainWindow::updateDisplay(){
    QImage image;
    if(shouldApplyHarrisDetector){
        applyHarrisCornerDetector();
    }
    if(shouldApplySIFTDetector){
        applySIFTDetector();
    }
    if(currentImage.channels() == 1){
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
    if(shouldApplySIFTDetector){
        ui->actionSift->toggle();
    }
    updateDisplay();
}

void MainWindow::on_thresholdSlider_sliderMoved(int position)
{
    threshold = position;
    QString labelValue = QString::number(position);
    ui->threshold_value->setText(labelValue);
}

void MainWindow::on_apertureSpinBox_valueChanged(double newvalue)
{
    apertureSize = (int) newvalue;
}

void MainWindow::on_blockSpinBox_valueChanged(double newvalue)
{
    blockSize = (int) newvalue;
}

void MainWindow::on_actionSift_toggled(bool toggle)
{
    shouldApplySIFTDetector = toggle;
    if(shouldApplyHarrisDetector){
        ui->actionHarris->toggle();
    }
    updateDisplay();
}
