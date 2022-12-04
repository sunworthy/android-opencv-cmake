//
// Created by wiki on 2022/12/5.
//

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui//highgui.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

namespace OpenCvLib {
    class CppImageProcess {
    public:
        static std::string imageProcess(std::string _path, std::string _outDir);

        static cv::Mat processBitmap(cv::Mat *inputImg, std::string method);
    };
};
