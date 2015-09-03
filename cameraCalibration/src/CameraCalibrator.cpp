#include <CameraCalibrator.h>

#include <iostream>
#include <sstream>
#include <time.h>

#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <json.hpp>
#include <fstream>

using namespace std;
using namespace cv;
using json = nlohmann::json;


CameraCalibrator::CameraCalibrator(){
    // board data initialization
    status = NOT_CALIBRATED;

    std::ifstream file("configuration.json");
    std::string str;
    std::string file_contents;
    while (std::getline(file, str))
    {
      file_contents += str;
      file_contents.push_back('\n');
    }
    json js = json::parse(file_contents);

    for (json::iterator it = js["images"].begin(); it != js["images"].end(); ++it) {
        filelist.push_back(*it);
    }

    boardSize = cv::Size(js["board width"], js["board height"]);
    squareSize = js["square size"]; //should be in mm
    sensorDimensionsAvaliable = js["sensor dimensions available"];
    apertureWidth = js["aperture width"]; //only really useful if
    apertureHeight = js["aperture height"]; // sensor Dimensions are available
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

bool CameraCalibrator::runCalibration(){

    computeBoardCornersWorldPosition();
    bool hasFoundCorners = false;
    cv::Mat currentImage;


    for (size_t i = 0; i < filelist.size(); i++) {
        cout << "Reading images " << filelist[i] << endl;
        currentImage = imread(filelist[i]);
        if(currentImage.data == NULL){
            cout << "Problems while reading the image: " << filelist[i] << " Won't continue reading!!!\n" << endl;
            break;
        }
        hasFoundCorners = cv::findChessboardCorners(currentImage, boardSize, imageCorners);
        // If we detected all inner points correctly
        if(imageCorners.size() == boardSize.area()){
            //refine to subpixel position
            cv::Mat grayImage;
            cv::cvtColor(currentImage, grayImage, COLOR_BGR2GRAY);
            cv::cornerSubPix(grayImage, imageCorners, cv::Size(11,11), cv::Size(-1, -1), cv::TermCriteria(cv::TermCriteria::EPS+cv::TermCriteria::COUNT, 30, 0.1));

            addInputPoints(corners, imageCorners);

            successulImages.push_back(filelist[i]);
            success.push_back(i);
        }
    }
    imageSize = imread(filelist[0]).size();

    cout << "Calibrating Camera..." << endl;
    //Execute calibration
    double reprojectionError =
                cv::calibrateCamera(worldPoints, imagePoints, imageSize,
                    cameraMatrix, distortionCoefficients,
                    rotationVectors, translationVectors);
    cout << "Global Reprojection error: " << reprojectionError << endl;

    status = CALIBRATED;
    return true;
}


void CameraCalibrator::displayResults(){
    double fovx, fovy, focalLength, aspectRatio;
    Point2d principalPoint;

    if(status == NOT_CALIBRATED){
        cout << "NOT CALIBRATED YET, MONSTER!!!!" << endl;
        return;
    }

    cv::calibrationMatrixValues(cameraMatrix,imageSize, apertureWidth, apertureHeight,
	                           fovx, fovy, focalLength, principalPoint, aspectRatio);

    json intrinsicParameters;
    stringstream auxstream;
    ofstream myfilestream;

    intrinsicParameters["Text"] = "Camera intrinsic Parameters";
    if(sensorDimensionsAvaliable){
        intrinsicParameters["Disclaimer"] = "Sensor dimensions were given as input. Focal length will be measured in mm.";
    }else{
        intrinsicParameters["Disclaimer"] = "Sensor dimensions not available. Focal length value will be in pixels together with sensor information";
    }

    intrinsicParameters["focalLength"] = focalLength;

    auxstream << principalPoint;
    intrinsicParameters["Principal Point"] = auxstream.str();
    auxstream.str("");

    intrinsicParameters["Computed Parameters"]["fov X"] = fovx;
    intrinsicParameters["Computed Parameters"]["fov Y"] = fovy;
    intrinsicParameters["Computed Parameters"]["Aspect Ratio"] =  aspectRatio;

    cout << "Camera intrinsic Parameters are available at parameters/intrinsic.json"  << endl;
    myfilestream.open("parameters/intrinsic.json");
    myfilestream << intrinsicParameters.dump(4);
    myfilestream.close();

    cout << "Camera Extrinsic Parameters for each image are available at parameters/extrinsic_IMAGE-NUMBER.json"  << endl;
    cout << "Images with projected points plotted are available at reprojected/reprojected_IMAGE-NUMBER.json"  << endl;

    for(int i = 0; i < successulImages.size(); ++i){
        cv::Mat currentImage = cv::imread(successulImages[i]);
        cout << success[i] << endl;
        if(currentImage.data == NULL){
            cout << "DEBUG DEBUG" << endl;
            break;
        }

        json extrinsicParameters;

        extrinsicParameters["Image Number"] = i;
        auxstream << rotationVectors[i];
        extrinsicParameters["Rodrigues Rotation Vector"] = auxstream.str();
        auxstream.str("");

        auxstream << translationVectors[i];
        extrinsicParameters["Translation Vector"] = auxstream.str();
        auxstream.str("");

        double meanError;
        vector<cv::Point2f> reprojectedImageCorners;

        cv::projectPoints(worldPoints[i], rotationVectors[i], translationVectors[i], cameraMatrix, distortionCoefficients, reprojectedImageCorners);

        meanError = cv::norm(imagePoints[i], reprojectedImageCorners, NORM_L2);
        meanError = meanError*meanError/reprojectedImageCorners.size();

        extrinsicParameters["Mean Square Error"] = meanError;

        //cout << extrinsicParameters.dump(4);
        stringstream filename;
        filename << "parameters/extrinsic_" << success[i] << ".json";

        myfilestream.open(filename.str(), ofstream::out);
        myfilestream << extrinsicParameters.dump(4);
        myfilestream.close();
        filename.str("");


        filename << "reprojected/reprojected_" << success[i] << ".jpg";
        cv::drawChessboardCorners(currentImage, boardSize, reprojectedImageCorners, true);
        cv::imwrite(filename.str(), currentImage);
    }
    cout << "DONE. Check the files, please" << endl;

}
