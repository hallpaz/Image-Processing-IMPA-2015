#include <ImageCapturer.h>

#include <sstream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>

ImageCapturer::ImageCapturer(double nrFrames, string _sequenceName, unsigned int _cameraID){
    numberOfFrames = nrFrames;
    delay = 1000;
    sequenceName = _sequenceName;
    cameraID = _cameraID;

}

void ImageCapturer::takeShot(){

}

void ImageCapturer::beginCapture(){
    camera.open(cameraID);

    if(!camera.isOpened() ){
        cout << "Problem with main camera! Aborting!!!" << endl;
        return;
    }
    /*string msg =  "Press 'g' to start";
    int baseLine = 0;
    Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
    Point textOrigin(view.cols - 2*textSize.width - 10, view.rows - 2*baseLine - 10);
    putText( view, msg, textOrigin, 1, 1);*/

    cout << "Insert an amount of time (seconds) for delay between consecutive shots\n" << endl;
    cin >> delay;
    //delay = delay;
    cv::Mat currentImage;
    for (size_t i = 0; i < numberOfFrames; i++) {
        cout << "Image number " << i << endl;
        //cv::waitKey(delay);
        stringstream filename;
        clock_t start_time = time(NULL);
        while(time(NULL) - start_time < delay){
            camera >> currentImage;
            cv::imshow("Image Captured", currentImage);
        }
        filename << sequenceName << i << ".jpg";
        cv::imwrite(filename.str(), currentImage);

        bitwise_not(currentImage, currentImage);
        cv::imshow("Image Captured", currentImage);
    }
    camera.close();

}
