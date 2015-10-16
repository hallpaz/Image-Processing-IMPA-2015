#include "scalespacecomputer.h"

#include <iostream>
#include <cmath>

ScaleSpaceComputer::ScaleSpaceComputer(Mat& srcImg, int numberOfScales)
{
    load(srcImg, numberOfScales);
}

ScaleSpaceComputer::ScaleSpaceComputer(){
    pyramid_loaded = false;
}

void ScaleSpaceComputer::load(Mat &srcImg, int numberOfScales){
    if(pyramid_loaded)
        return;
    this->numberOfScales = numberOfScales;
    Mat srcGrayImg;
    if(srcImg.channels() == 3){
        cv::cvtColor(srcImg, srcGrayImg, CV_BGR2GRAY);
    }else{
        srcGrayImg = srcImg;
    }
    imagesAtScale.push_back(srcGrayImg);
    srcImg = srcGrayImg;
    for(int i = 1; i < numberOfScales; ++i){
        Mat img;
        //descendToScale(srcGrayImg, img, i);
        cv::pyrDown(srcImg, img, Size( srcImg.cols/2, srcImg.rows/2 ));
        imagesAtScale.push_back(img);

        srcImg = img;
    }
    pyramid_loaded = true;
}

void ScaleSpaceComputer::computeAllMagnitude(){
    for(int i = 0; i < numberOfScales; ++i){
        Mat mag;
        gradientMagnitudeMap(mag, i);
        magnitudeAtScale.push_back(mag);
    }
}

bool ScaleSpaceComputer::descendToScale(Mat& srcImg, Mat& dstImg, int scaleFactor){
    if(scaleFactor < 1)
        return false;

    int divideFactor = (2 << (scaleFactor-1) );

    std::cout << srcImg.rows << " x " << srcImg.cols <<" factor: " << divideFactor << std::endl;

    cv::pyrDown(srcImg, dstImg);// cv::Size(srcImg.rows/divideFactor, srcImg.cols/divideFactor));

    std::cout << "hop" << std::endl;

    return true;
}

bool ScaleSpaceComputer::horizontalGradient(Mat& srcImg, Mat& dstImg){
    cv::Sobel(srcImg, dstImg, CV_32FC1, 1, 0, 3);
    return true;
}

bool ScaleSpaceComputer::verticalGradient(Mat& srcImg, Mat& dstImg){
    cv::Sobel(srcImg, dstImg, CV_32FC1, 0, 1, 3);
    return true;
}

bool ScaleSpaceComputer::gradientMagnitudeMap(Mat& dstImg, int scaleFactor){
    Mat gradX, gradY;
    Mat srcImg = imagesAtScale[scaleFactor];
    srcImg = srcImg.clone();

    //horizontalGradient(srcImg, dstImg);
    horizontalGradient(srcImg, gradX);
    verticalGradient(srcImg, gradY);
    cv::magnitude(gradX, gradY, srcImg);
    cv::normalize(srcImg, dstImg, 0, 255, cv::NORM_MINMAX, CV_8UC1);

    return true;
}

bool ScaleSpaceComputer::gradientOrientationMap(Mat& dstImg, int scaleFactor, int magnitudeThreshold){
    Mat gradX, gradY;
    Mat srcImg = imagesAtScale[scaleFactor];
    srcImg = srcImg.clone();
    Mat angleImg;
    horizontalGradient(srcImg, gradX);
    verticalGradient(srcImg, gradY);
    cv::phase(gradX, gradY, angleImg, false);
    drawArrows(angleImg, dstImg, scaleFactor, magnitudeThreshold);
    return true;
}

const cv::Mat& ScaleSpaceComputer::operator [](std::size_t index) const{
    return imagesAtScale[index];
}

bool ScaleSpaceComputer::ready(){
    return pyramid_loaded;
}

const Mat& ScaleSpaceComputer::getMagMap(size_t index){
    if(magnitudeAtScale.empty()){
        computeAllMagnitude();
    }
    return magnitudeAtScale[index];
}

void ScaleSpaceComputer::drawArrows(Mat& angleImg, Mat& dstImg,int scaleFactor, int magnitudeThreshold){

    Mat srcImg = getMagMap(scaleFactor).clone();

    dstImg.setTo(0);                          // clear image - set to black
    float arrowLength = 0.3;
    for(int i=0; i<srcImg.rows; i++){
        for(int j=0; j<srcImg.cols; j++){
            uchar magValue = srcImg.at<uchar>(i,j);
            if(magValue > magnitudeThreshold){
                float angle = angleImg.at<float>(i, j);
                Point start = Point(j, i);
                Point direction = cv::Point(magValue*arrowLength * cos(angle), magValue*arrowLength * sin(angle));
                cv::arrowedLine(dstImg, start, start + direction, cv::Scalar(magValue));

            }
        }
    }
}

void ScaleSpaceComputer::clear(){
    imagesAtScale.clear();
    magnitudeAtScale.clear();
    orientationAtScale.clear();
    pyramid_loaded = false;
}
