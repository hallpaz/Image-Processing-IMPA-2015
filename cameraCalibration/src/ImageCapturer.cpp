#include <ImageCapturer.h>

#include <sstream>
#include <time.h>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>

ImageCapturer::ImageCapturer(double nrFrames, string _sequenceName, unsigned int _cameraID){
    numberOfFrames = nrFrames;
    delay = 1000;
    sequenceName = _sequenceName;
    cameraID = _cameraID;

}
ImageCapturer::~ImageCapturer(){

}

void ImageCapturer::beginCapture(){
    camera.open(cameraID);

    if(!camera.isOpened() ){
        cout << "Problem with main camera! Aborting!!!" << endl;
        return;
    }

    cout << "Insert an amount of time (seconds) for delay between consecutive shots\n" << endl;
    cin >> delay;

    cv::Mat currentImage;
    for (size_t i = 0; i < numberOfFrames; i++) {
        cout << "Image number " << i << endl;

        stringstream filename;
        clock_t start_time = time(NULL);
        while(time(NULL) - start_time < delay){
            camera >> currentImage;
            cv::imshow("Image Captured", currentImage);
        }
        filename << sequenceName << i << ".jpg";
        cv::imwrite(filename.str(), currentImage);

        bitwise_not(currentImage, currentImage);
        start_time = clock();
        while( (clock() - start_time) < 500){
            cv::imshow("Image Captured", currentImage);
        }
    }

}
