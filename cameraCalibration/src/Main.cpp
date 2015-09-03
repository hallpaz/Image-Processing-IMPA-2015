#include <CameraCalibrator.h>
#include <ImageCapturer.h>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv){
    char key;
    if( argc > 1 ){
        int nrframes = stoi(argv[1]);
        ImageCapturer capturer(nrframes);
        capturer.beginCapture();

        cout << "Images captured.\n Take a minute to adjust configuration.json file before calibrations" << endl;
        cout << "Press any key and hit ENTER to continue" << endl;
        cin >> key;
    }

    CameraCalibrator calibrador;

    calibrador.runCalibration();

    calibrador.displayResults();

    return 0;

}
