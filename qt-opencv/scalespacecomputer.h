#ifndef SCALESPACECOMPUTER_H
#define SCALESPACECOMPUTER_H

#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

class ScaleSpaceComputer
{
public:
    ScaleSpaceComputer();
    ScaleSpaceComputer(Mat& srcImg, int numberOfScales);
    void load(Mat& srcImg, int numberOfScales);
    bool gradientMagnitudeMap(Mat& dstImg, int scaleFactor);
    bool gradientOrientationMap(Mat& dstImg, int scaleFactor);
    const cv::Mat& operator[](std::size_t index) const;
    bool ready();

private:
    bool pyramid_loaded;
    vector<Mat> imagesAtScale;
    bool descendToScale(Mat& srcImg, Mat& dstImg, int scaleFactor);
    bool horizontalGradient(Mat& srcImg, Mat& dstImg);
    bool verticalGradient(Mat& srcImg, Mat& dstImg);
};

#endif // SCALESPACECOMPUTER_H
