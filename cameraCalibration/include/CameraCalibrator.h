#ifndef CAMERA_CALIBRATOR_H
#define CAMERA_CALIBRATOR_H

#include <opencv2/core.hpp>

using namespace std;

enum class ImageSource { FILE, CAMERA  };
enum class Pattern { CHESSBOARD };

class CameraCalibrator{

private:
    //for calibration
    //const unsigned int THRESHOLD_OF_POINTS;
    cv::Mat cameraMatrix;
    cv::Mat distortionCoefficients;

    vector< vector<cv::Point3f> > worldPoints;
    vector< vector<cv::Point2f> > imagePoints;
    vector<cv::Mat> rotationVectors;
    vector<cv::Mat> translationVectors;

    double reprojectionError;

    //Configuration
    cv::Size boardSize;
    float squareSize;
    vector<string> filelist;
    unsigned int source;
    unsigned int imageIndex;

    // temporary data?
    vector<cv::Point3f> corners;
    vector<cv::Point2f> imageCorners;
    cv::Size imageSize;

    void addInputPoints(vector<cv::Point3f> worldCorners, vector<cv::Point2f> imageCorners);

    cv::Mat getNextImage();

public:

    CameraCalibrator();

    bool runCalibration();

    void computeBoardCornersWorldPosition();

    void computeBoardCornersWorldPosition(cv::Size boardSize, float squareSize, std::vector<cv::Point3f>& corners);

    double computeReprojectionError();

    void displayIntrinsecParameters();



};


#endif
