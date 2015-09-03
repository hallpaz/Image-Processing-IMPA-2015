#ifndef CAMERA_CALIBRATOR_H
#define CAMERA_CALIBRATOR_H

#include <opencv2/core.hpp>

using namespace std;

enum class ImageSource { FILE, CAMERA  };

class CameraCalibrator{

private:

    enum Status {NOT_CALIBRATED, CALIBRATED };
    //for calibration
    cv::Mat cameraMatrix;
    cv::Mat distortionCoefficients;

    vector< vector<cv::Point3f> > worldPoints;
    vector< vector<cv::Point2f> > imagePoints;
    vector<cv::Mat> rotationVectors;
    vector<cv::Mat> translationVectors;

    double reprojectionError;
    bool status;
    bool sensorDimensionsAvaliable;
    cv::Size imageSize;
    vector<int> success;
    vector<string> successulImages;

    //Configuration
    cv::Size boardSize;
    float squareSize;
    vector<string> filelist;
    double apertureWidth;
    double apertureHeight;

    // temporary data
    vector<cv::Point3f> corners;
    vector<cv::Point2f> imageCorners;

    void addInputPoints(vector<cv::Point3f> worldCorners, vector<cv::Point2f> imageCorners);
    void computeBoardCornersWorldPosition();
    double computeReprojectionError();

public:

    CameraCalibrator();
    bool runCalibration();
    void displayResults();

};

#endif
