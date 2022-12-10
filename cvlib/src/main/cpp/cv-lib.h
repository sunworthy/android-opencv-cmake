//
// Created by wiki on 2022/12/5.
//

#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

namespace CvLib {
    class ImageProcess {
    public:
        /**
         * 均值滤波
         *
         * @param image
         * @return
         */
        static int cvBlur(const Mat &image);

        /**
         * 图像的高斯滤波
         * @param image
         * @return
         */
        static int cvGaussianBlur(const Mat &image);

        /**
         * 中值滤波
         * @param image
         * @return
         */
        static int cvMedianBlur(const Mat &image);

        /**
         * 双边滤波
         * 双边滤波器可以很好的边缘保护，即可以在去噪的同时，保护图像的边缘特性
         *
         * @param image
         * @return 应用结果为（磨皮）：
         */
        static int cvBilateralFilter(const Mat &image);

        /**
         * 膨胀
         * @param image
         * @return
         */
        static int cvDilate(const Mat &image);

        /**
         * 腐蚀
         * @param image
         * @return
         */
        static int cvErode(const Mat &image);

        /**
         * 高级形态学变换
         * morphologyEx用于完成高级形态学变换，所谓高级形态学变换相当于一些比较简单的形态学变换的结合。
         * 常见的高级形态学变换方式如下：
         * 1、开运算：腐蚀->膨胀，其主要作用为去除图像中较小区域
         * 2、闭运算：膨胀->腐蚀，可以去除掉小型黑洞
         * 3、顶帽：原图-开运算，用于突出比原图轮廓周围的区域更明亮的区域，用来分离比临近点亮一些的斑块
         * 4、黑帽：闭运算-原图，用于突出比原图轮廓周围的区域更暗的区域，用来分离比临近点暗一些的斑块
         * 5、形态学梯度：膨胀-腐蚀，对二值图操作可以将团块的边缘突出，用来保留物体的边缘轮廓。
         * 其中，src为源图，dst为目标图，erodeStruct是结构元素，越大则处理的效果越明显，第三个参数为表示使用的高级形态学变换是什么，可选择的参数如下：
         * MORPH_OPEN 开运算
         * MORPH_CLOSE 闭运算
         * MORPH_GRADIENT 形态学梯度
         * MORPH_TOPHAT 顶帽
         * MORPH_BLACKHAT 黑帽
         * MORPH_ERODE 腐蚀
         * MORPH_DILATE 膨胀
         * @param image
         * @return
         */
        static int cvMorphologyEx(const Mat &image);

        /**
         * 图像增强
         * 可以用于快速的图像增强，可以为图片中的每个点进行线性运算
         * @param image
         * @return
         */
        static int cvConvertScaleAbs(const Mat &image);

        /**
         * Sobel算子是像素图像边缘检测中最重要的算子之一，具有非常重要的作用。
         * @param src
         * @return
         */
        static int cvSobel(const Mat &src);
        /**
         * Laplacian算子是像素图像边缘检测中最重要的算子之一，具有非常重要的作用。
         * @param src
         * @return
         */
        static int cvLaplacian(const Mat &src);

        /**
         * Scharr算子也是一种常见的边缘检测算子，与sobel的参数类似，但是仅作用于大小为3的内核，同时。
         * @param src
         * @return
         */
        static int cvScharr(const Mat &src);
        /**
         * Canny算法就是首先对图像选择一定的Gauss滤波器进行平滑滤波，然后采用非极值抑制技术进行处理得到最后的边缘图像。
         * @param src
         * @return
         */
        static int cvCanny(const Mat &src);
    };
};
