#ifndef IMAGE_CAPTURE_H
#define IMAGE_CAPTURE_H


#include <time.h>
#include <iostream>
#include <opencv2/videoio.hpp>


using namespace std;

class ImageCapturer{
private:

    cv::VideoCapture camera;
    double delay;
    double numberOfFrames;
    unsigned int cameraID;
    string sequenceName;

    void takeShot();

public:

    ImageCapturer(double nrFrames, string sequenceName = "images/board", unsigned int cameraID = 0);

    void beginCapture();
};

#endif
