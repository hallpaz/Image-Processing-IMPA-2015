#include "scalespacecomputer.h"

#include <iostream>

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
    cv::Sobel(srcImg, dstImg, CV_32F, 1, 0, 3);
    return true;
}

bool ScaleSpaceComputer::verticalGradient(Mat& srcImg, Mat& dstImg){
    cv::Sobel(srcImg, dstImg, CV_32F, 0, 1, 3);
    return true;
}

bool ScaleSpaceComputer::gradientMagnitudeMap(Mat& dstImg, int scaleFactor){
    Mat gradX, gradY;
    Mat srcImg = imagesAtScale[scaleFactor].clone();

    horizontalGradient(srcImg, gradX);
    verticalGradient(srcImg, gradY);
    cv::magnitude(gradX, gradY, dstImg);
    cv::normalize(dstImg, dstImg, 0, 255, cv::NORM_L2, CV_8UC1);

    return true;
}

bool ScaleSpaceComputer::gradientOrientationMap(Mat& dstImg, int scaleFactor){
    Mat gradX, gradY;
    Mat srcImg = imagesAtScale[scaleFactor].clone();

    horizontalGradient(srcImg, gradX);
    verticalGradient(srcImg, gradY);
    cv::phase(gradX, gradY, dstImg);
    return true;
}


const cv::Mat& ScaleSpaceComputer::operator [](std::size_t index) const{
    return imagesAtScale[index];
}

bool ScaleSpaceComputer::ready(){
    return pyramid_loaded;
}
