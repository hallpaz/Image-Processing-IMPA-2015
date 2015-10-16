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
    bool gradientOrientationMap(Mat& dstImg, int scaleFactor, int magnitudeThreshold);
    const cv::Mat& operator[](std::size_t index) const;
    bool ready();
    void computeAllMagnitude();
    const cv::Mat& getMagMap(std::size_t index);
    void clear();

private:
    bool pyramid_loaded;
    int numberOfScales;
    vector<Mat> imagesAtScale;
    vector<Mat> magnitudeAtScale;
    vector<Mat> orientationAtScale;
    bool descendToScale(Mat& srcImg, Mat& dstImg, int scaleFactor);
    bool horizontalGradient(Mat& srcImg, Mat& dstImg);
    bool verticalGradient(Mat& srcImg, Mat& dstImg);
    void inline drawArrows(Mat& angleImg, Mat& dstImg, int scaleFactor, int magnitudeThreshold);
};

#endif // SCALESPACECOMPUTER_H
