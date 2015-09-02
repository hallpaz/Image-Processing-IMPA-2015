#include <CameraCalibrator.h>

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <json.hpp>

using namespace std;
using json = nlohmann::json;


CameraCalibrator::CameraCalibrator(){

    // board data initialization
    boardSize = cv::Size(9, 6);
    squareSize = 50; //mm
    imageIndex = 0;
    source = 0;

    status = NOT_CALIBRATED;
    sensorDimensionsAvaliable = false;

    apertureWidth = 1.0; //Should write default value
    apertureHeight = 1.0;

    filelist.push_back("images/board0.jpg");
    filelist.push_back("images/board1.jpg");
    filelist.push_back("images/board2.jpg");
    filelist.push_back("images/board3.jpg");
    filelist.push_back("images/board4.jpg");
    filelist.push_back("images/board5.jpg");
    filelist.push_back("images/board6.jpg");
    filelist.push_back("images/board7.jpg");
    filelist.push_back("images/board8.jpg");

}


void CameraCalibrator::computeBoardCornersWorldPosition(cv::Size boardSize, float squareSize, std::vector<cv::Point3f>& corners){

    for (size_t i = 0; i < boardSize.height; ++i) {
        for (size_t j = 0; j < boardSize.width; ++j) {
            corners.push_back(cv::Point3f(j*squareSize, i*squareSize, 0));
        }
    }
}

void CameraCalibrator::addInputPoints(vector<cv::Point3f> worldCorners, vector<cv::Point2f> imageCorners){
    //3D world points
    worldPoints.push_back(worldCorners);
    //2D image points
    imagePoints.push_back(imageCorners);

}

void CameraCalibrator::computeBoardCornersWorldPosition(){
    for (size_t i = 0; i < boardSize.height; ++i) {
        for (size_t j = 0; j < boardSize.width; ++j) {
            corners.push_back(cv::Point3f(j*squareSize, i*squareSize, 0));
        }
    }
}

cv::Mat CameraCalibrator::getNextImage(){
    switch (source) {
        case 0:
        if(imageIndex < filelist.size()){
            cout << imageIndex << endl;
            return cv::imread(filelist[imageIndex++]);
        }

        else{
            Mat doido;
            return doido;
        }
        case 1:
            //dosomething
            Mat fromCamera;
            return fromCamera;
    }
}

bool CameraCalibrator::runCalibration(){

    computeBoardCornersWorldPosition();
    bool hasFoundCorners = false;
    cv::Mat currentImage = getNextImage();


    namedWindow("DisplayImage", WINDOW_AUTOSIZE);
    imshow("Display Image", currentImage);
    waitKey(10000);

    while( (imagePoints.size() < 9) && imageIndex<=filelist.size()){

        hasFoundCorners = cv::findChessboardCorners(currentImage, boardSize, imageCorners);

        // If we detected all inner points correctly
        if(imageCorners.size() == boardSize.area()){

            //refine to subpixel position
            cv::Mat grayImage;
            cv::cvtColor(currentImage, grayImage, COLOR_BGR2GRAY);
            cv::cornerSubPix(grayImage, imageCorners, cv::Size(11,11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 30, 0.1));

            //Draw image with identified corners
            cv::drawChessboardCorners(currentImage, boardSize, imageCorners, hasFoundCorners);
            imwrite("marked.png", currentImage);

            addInputPoints(corners, imageCorners);
        }
        cout << "Image Points Size " << imagePoints.size() << endl;
        currentImage = getNextImage();
    }

    //Display Image
    /*namedWindow("DisplayImage", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);*/
    currentImage = imread(filelist[0]);
    //Execute calibration
    double reprojectionError =
                cv::calibrateCamera(worldPoints, imagePoints, currentImage.size(),
                    cameraMatrix, distortionCoefficients,
                    rotationVectors, translationVectors);
    cout << "Reprojection error: " << reprojectionError << endl;
}



void CameraCalibrator::displayResults(){
    double fovx, fovy, focalLength, aspectRatio;
    Point2d principalPoint;

    cv::calibrationMatrixValues(cameraMatrix,imageSize,
	    apertureWidth, apertureHeight,
		fovx, fovy, focalLength, principalPoint, aspectRatio);

    stringstream intrinsicText;
    if(sensorDimensionsAvaliable){
        intrinsicText << "Sensor dimensions were given as input. Focal length will be measured in mm." << endl;
    }else{
        intrinsicText << "Sensor dimensions not available. Focal length value will be in pixels together with sensor information" << endl;
    }

    json intrinsicParameters;
    intrinsicParameters["Text"] = "Camera intrinsic Parameters: ";

    intrinsicText << "Camera intrinsic Parameters: " << endl;
    intrinsicText << "Focal Length: " << focalLength << endl;
    intrinsicText << "Principal Point: " << endl;

    intrinsicText << "Computed Parameters:" << endl;
    intrinsicText << "fov X: " << fovx << endl;
    intrinsicText << "fov Y: " << fovy << endl;
    intrinsicText << "Aspect Ratio: " << aspectRatio << endl;


    cout << intrinsicText.str();

    cout << "Camera Extrinsic Parameters for each image: "  << endl;

    vector<string>::iterator imageNameIterator;

    for(int i = 0; i < filelist.size(); ++i){
        stringstream extrinsicText;
        intrinsicText << "Image Number: " << i << endl;

        extrinsicText <<"Rodrigues Rotation Vector" << rotationVectors[i] << endl;
        extrinsicText <<"Translation Vector" << translationVectors[i] << endl;

        double meanError;
        vector<cv::Point2f> reprojectedImageCorners;

        projectPoints(worldPoints[i], rotationVectors[i], translationVectors[i], cameraMatrix, distortionCoefficients, reprojectedImageCorners);

        meanError = norm(imagePoints[i], reprojectedImageCorners, NORM_L2);
        meanError = meanError*meanError/reprojectedImageCorners.size();

        extrinsicText << "Mean Square Error: " << meanError << endl;

        cout << extrinsicText.str();

        Mat currentImage = imread(filelist[i]);
        stringstream filename;
        filename << "reprojected/reprojected_" << i << ".jpg";

        drawChessboardCorners(currentImage, boardSize, reprojectedImageCorners, true);
        imwrite(filename.str(), currentImage);

    }


}
