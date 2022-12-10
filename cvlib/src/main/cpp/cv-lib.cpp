#include <android/log.h>
#include <android/log.h>
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "cv-lib.h"
#include <syslog.h>
#include <iostream>

using namespace cv;
using namespace std;

namespace CvLib {

    int ImageProcess::cvBlur(const Mat &image) {
        if (!image.data) {
            cout << "could not open image" << endl;
            return -1;
        }
        cv::blur(image, image, Size(3, 3));
        return 0;
    }

    int ImageProcess::cvGaussianBlur(const Mat &image) {
        if (!image.data) {
            cout << "could not open image" << endl;
            return -1;
        }
        cv::GaussianBlur(image, image, Size(5, 5), 3, 3);
        return 0;
    }

    int ImageProcess::cvMedianBlur(const Mat &image) {
        if (!image.data) {
            cout << "could not open image" << endl;
            return -1;
        }
        cv::medianBlur(image, image, 5);
        return 0;
    }

    int ImageProcess::cvBilateralFilter(const Mat &image) {
        if (!image.data) {
            cout << "could not open image" << endl;
            return -1;
        }
        // d为过滤过程中每个像素邻域的直径范围；
        int d = 50;
        // sigmaColor：颜色空间过滤器的sigma值，这个参数的值越大，表明该像素邻域内有越宽广的颜色会被混合到一起，产生较大的半相等颜色区域。
        int sigmaColor = 50;
        // sigmaSpace：坐标空间中滤波器的sigma值，如果该值较大，则意味着越远的像素将相互影响，从而使更大的区域中足够相似的颜色获取相同的颜色。
        int sigmaSpace = 50;
        cv::bilateralFilter(image, image, d, sigmaColor, sigmaSpace);
        return 0;
    }

    int ImageProcess::cvDilate(const Mat &image) {
        // erodeStruct是用于膨胀操作和腐蚀操作的结构元素，越大则膨胀效果越明显。
        Mat erodeStruct = getStructuringElement(MORPH_RECT, Size(5, 5));
        dilate(image, image, erodeStruct);
        return 0;
    }

    int ImageProcess::cvErode(const Mat &image) {
        // erodeStruct是用于膨胀操作和腐蚀操作的结构元素，越大则腐蚀效果越明显。
        Mat erodeStruct = getStructuringElement(MORPH_RECT, Size(5, 5));
        erode(image, image, erodeStruct);
        return 0;
    }

    int ImageProcess::cvMorphologyEx(const Mat &image) {
        Mat erodeStruct = getStructuringElement(MORPH_RECT, Size(3, 3));
        morphologyEx(image, image, MORPH_GRADIENT, erodeStruct);
        return 0;
    }

    int ImageProcess::cvConvertScaleAbs(const Mat &image) {
        double theta = 1.5;
        double b = 10;
        convertScaleAbs(image, image, theta, b);
        return 0;
    }

    int ImageProcess::cvSobel(const Mat &src) {
        // src为源图，dst为目标图
        cvtColor(src, src, COLOR_RGB2GRAY);
        // 第三个参数为输出图像的深度，可选参数为：CV_8U，CV_16U，CV_16S，CV_32F，CV_64F，其选择结果根据输入图像决定，在不确定的情况下可以使用-1
        // 第四个和第五个参数可以取0或者1，代表x方向和y方向上的差分阶数，0代表该方向不取。
        // 第六个参数为ksize的大小，表示sobel器的大小。
        GaussianBlur(src, src, Size(3, 3), 0.5, 0.5);
        Sobel(src, src, CV_16U, 1, 1, 5);
        convertScaleAbs(src, src);
        return 0;
    }

    int ImageProcess::cvLaplacian(const Mat &src) {
        cv::Laplacian(src, src, CV_16U, 3);
        return 0;
    }

    int ImageProcess::cvScharr(const Mat &src) {
        cvtColor(src, src, COLOR_RGB2GRAY);
        GaussianBlur(src, src, Size(3, 3), 0.5, 0.5);
        // 第三个参数为输出图像的深度，可选参数为：CV_8U，CV_16U，CV_16S，CV_32F，CV_64F，其选择结果根据输入图像决定，在不确定的情况下可以使用-1
        Scharr(src, src, CV_16U, 1, 0);
        convertScaleAbs(src, src);
        return 0;
    }

    int ImageProcess::cvCanny(const Mat &src) {
        cvtColor(src, src, COLOR_RGB2GRAY);
        GaussianBlur(src, src, Size(3, 3), 0.5, 0.5);
        //第三个参数为低阈值，值越大，找到的边缘越少。
        //第四个参数为高阈值，值越大，找到的边缘越少。
        //第五个参数为Canny算子的大小。
        Canny(src, src, 50, 150, 3);
        convertScaleAbs(src, src);
        return 0;
    }
}