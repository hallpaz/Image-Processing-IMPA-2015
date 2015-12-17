#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


void flowToRGB(const cv::Mat & flowImage, cv::Mat & rgbFlow);
void drawArrows(cv::Mat& flowImage, cv::Mat& dstImg, int magnitudeThreshold);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentImage = firstImage;
    ui->first_image_radio->toggle();
    levels = ui->levels_box->value();
    win_size = ui->win_box->value();
    iterations = ui->iterations_box->value();
    poly_n = ui->polyn_box->value();
    poly_sigma = ui->polysigma_box->value();
    gaussian_flag = 0;
    shouldRecalculate = true;


    m_timer.start(20);
    connect( &m_timer, SIGNAL(timeout()), this, SLOT(captureAndShowVideoFrame()) );
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::updateDisplay(){
    QImage image;
    image = QImage( (uchar*)currentImage.data, currentImage.cols, currentImage.rows, currentImage.step, QImage::Format_RGB888 );
    QPixmap pixmap = QPixmap::fromImage( image );
    ui->imageLabel->setPixmap( pixmap );
}

void MainWindow::on_actionLoadImage_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load an image");
    if( filename.isEmpty() )
        return;

    if(ui->first_image_radio->isChecked()){
        firstImage = cv::imread( filename.toStdString().c_str(), CV_LOAD_IMAGE_COLOR );
        if( ! firstImage.data )
            return;
        cv::cvtColor( firstImage, firstImage, CV_BGR2RGB );
        currentImage = firstImage;

    }
    if(ui->second_image_radio->isChecked()){
        secondImage = cv::imread( filename.toStdString().c_str(), CV_LOAD_IMAGE_COLOR );
        if( ! secondImage.data )
            return;
        cv::cvtColor( secondImage, secondImage, CV_BGR2RGB );
        currentImage = secondImage;

    }
    updateDisplay();

}

void MainWindow::on_actionSaveImage_triggered()
{

    if( ! flowImage.data )
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

}

void MainWindow::calcOpticalFlowColor(){
    flowImage.create(firstImage.rows, firstImage.cols, CV_32FC2);
    currentImage = flowImage.clone();
    cv::Mat first, second;
    cv::cvtColor(firstImage, first, CV_RGB2GRAY);
    cv::cvtColor(secondImage, second, CV_RGB2GRAY);
    cv::calcOpticalFlowFarneback(first, second, flowImage, 0.5, levels, win_size, iterations, poly_n, poly_sigma, gaussian_flag);
    flowToRGB(flowImage, currentImage);
    flowImage = currentImage;
    shouldRecalculate = false;
}

void MainWindow::calcOpticalFlowArrows(){
    flowImage.create(firstImage.rows, firstImage.cols, CV_32FC2);
    cv::Mat first, second;
    cv::cvtColor(firstImage, first, CV_RGB2GRAY);
    cv::cvtColor(secondImage, second, CV_RGB2GRAY);
    cv::calcOpticalFlowFarneback(first, second, flowImage, 0.5, levels, win_size, iterations, poly_n, poly_sigma, gaussian_flag);
    currentImage = firstImage.clone();
    drawArrows(flowImage, currentImage, 10);
    flowImage = currentImage;
    shouldRecalculate = false;
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
    }
    else
    {
        if( m_cvCamera.isOpened() )
        {
            if(ui->first_image_radio->isChecked()){
                m_cvCamera >> firstImage;
                cv::cvtColor(firstImage, firstImage, CV_BGR2RGB);
                currentImage = firstImage;
            }
            if(ui->second_image_radio->isChecked()){
                m_cvCamera >> secondImage;
                cv::cvtColor(secondImage, secondImage, CV_BGR2RGB);
                currentImage = secondImage;
            }
            updateDisplay();

            m_cvCamera.release();
        }
        ui->actionLoadImage->setDisabled( false );
        ui->actionSaveImage->setDisabled( false );
    }
}

void MainWindow::on_levels_box_valueChanged(int value)
{
    levels = value;
    shouldRecalculate = true;
}

void MainWindow::on_win_box_valueChanged(int value)
{
    win_size = value;
    shouldRecalculate = true;
}

void MainWindow::on_iterations_box_valueChanged(int value)
{
    iterations = value;
    shouldRecalculate = true;
}

void MainWindow::on_polyn_box_valueChanged(int value)
{
    poly_n = value;
    shouldRecalculate = true;
}

void MainWindow::on_polysigma_box_valueChanged(double value)
{
    poly_sigma = (float) value;
    shouldRecalculate = true;
}

void MainWindow::on_first_image_radio_toggled(bool checked)
{
    if(checked){
        currentImage = firstImage;
        updateDisplay();
    }
}

void MainWindow::on_second_image_radio_toggled(bool checked)
{
    if(checked){
        currentImage = secondImage;
        updateDisplay();
    }
}



void MainWindow::on_flow_image_radio_toggled(bool checked)
{
    if(checked){
        currentImage = flowImage;
        if(shouldRecalculate){
            calcOpticalFlowColor();
        }
        updateDisplay();
    }
}

void MainWindow::on_flow_arrow_radio_toggled(bool checked)
{
    if(checked){
        currentImage = flowImage;
        if(shouldRecalculate){
            calcOpticalFlowArrows();
        }
        updateDisplay();
    }
}

void MainWindow::on_gaussian_check_toggled(bool checked)
{
    if(checked){
        gaussian_flag = cv::OPTFLOW_FARNEBACK_GAUSSIAN;
    }
    else{
        gaussian_flag = 0;
    }
}

void flowToRGB(const cv::Mat & flowImage, cv::Mat & rgbFlow)
{
    if(flowImage.empty())
        return;
    if( flowImage.depth() != CV_32F)
        std::cout << "ERRO DE TIPO DE IMAGE!!!!" << std::endl;

    cv::Mat orientationImage, magnitudeImage, saturationMap;

    std::vector<cv::Mat> dir_channels;
    split(flowImage, dir_channels);
    //orientation calculated in degrees
    cv::cartToPolar(dir_channels[0], dir_channels[1], magnitudeImage, orientationImage, true);
    cv::normalize(magnitudeImage, saturationMap, 0, 255, cv::NORM_MINMAX, CV_8UC1);

    cv::Mat hsvImage(flowImage.size(), CV_8UC3);
    for (int r = 0; r < hsvImage.rows; r++) {
        uchar* rowptr = hsvImage.ptr(r);
        for (int c = 0; c < hsvImage.cols; c++, rowptr+=3) {
            float hue = orientationImage.at<float>(r, c)/2;
            if (hue < 0.0) {
                std::cout << "negative hue: " << hue << std::endl;
            }
            rowptr[0] = cv::saturate_cast<uchar>((orientationImage.at<float>(r, c)-1)/2);
            if (rowptr[0] > 179) {
                std::cout << "hue invalid: " << rowptr[0] << " and " << hue << " at " << r << "x" << c << std::endl;
            }
            rowptr[1] = cv::saturate_cast<uchar>(saturationMap.at<uchar>(r,c));
            if (rowptr[1] < 5) {
                std::cout << "low saturation: " << (int) rowptr[1] << " and " << magnitudeImage.at<float>(r,c) << " at " << r << "x" << c << std::endl;
            }
            rowptr[2] = 255;
        }
    }

    cv::cvtColor(hsvImage, rgbFlow, CV_HSV2BGR);
}

void drawArrows(cv::Mat&flowImage, cv::Mat& dstImg, int magnitudeThreshold){

    cv::Mat orientationImage, magnitudeMap, magnitudeImage;

    std::vector<cv::Mat> dir_channels;
    split(flowImage, dir_channels);
    //orientation calculated in radians
    cv::cartToPolar(dir_channels[0], dir_channels[1], magnitudeImage, orientationImage, false);
    cv::normalize(magnitudeImage, magnitudeMap, 0, 255, cv::NORM_MINMAX, CV_8UC1);

    float arrowLength = 0.1;
    for(int i=0; i<magnitudeMap.rows; i+=4){
        for(int j=0; j<magnitudeMap.cols; j+=4){
            uchar magValue = magnitudeMap.at<uchar>(i,j);
            if(magValue > magnitudeThreshold){
                float angle = orientationImage.at<float>(i, j);
                cv::Point start = cv::Point(j, i);
                cv::Point direction = cv::Point(magValue*arrowLength * cos(angle), magValue*arrowLength * sin(angle));
                cv::arrowedLine(dstImg, start, start + direction, cv::Scalar(0, magValue, 0));
            }
        }
    }
}
