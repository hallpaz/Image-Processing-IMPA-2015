#include "scalespacecomputer.h"

ScaleSpaceComputer::ScaleSpaceComputer(Mat& srcImg, int numberOfScales)
{
    Mat srcGrayImg;
    if(srcImg.channels() == 3){
        cv::cvtColor(srcImg, srcGrayImg, CV_BGR2GRAY);
    }else{
        srcGrayImg = srcImg;
    }
    imagesAtScale.push_back(srcGrayImg);
    for(int i = 1; i < numberOfScales; ++i){
        Mat img;
        descendToScale(srcGrayImg, img, i);
        imagesAtScale.push_back(img);
    }
}

bool ScaleSpaceComputer::descendToScale(Mat& srcImg, Mat& dstImg, int scaleFactor){
    if(scaleFactor < 1)
        return false;
    int divideFactor = 2 << (scaleFactor-1);
    cv::pyrDown(srcImg, dstImg, cv::Size(srcImg.rows/divideFactor, srcImg.cols/divideFactor));

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
    cv::normalize(dstImg, dstImg, 0, 255, CV_8UC1);
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
