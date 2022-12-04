#include <cstring>
#include <jni.h>
#include <cinttypes>
#include <android/log.h>
#include <android/log.h>
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "OpenCVLib::", __VA_ARGS__))


using namespace cv;
extern "C"
JNIEXPORT jstring Java_com_joshkryo_lib_OpenCVLib_imageProcess(JNIEnv *env, jclass instance,
                                             jstring _imagePath,jstring _outDir) {

    const char *imgPath = (env)->GetStringUTFChars(_imagePath, 0);
    const char *outputImgDir = (env)->GetStringUTFChars(_outDir, 0);

    cv::Mat src = cv::imread(imgPath);

    LOGI("calculation time: %s" ,imgPath);

    //处理img_input的逻辑..........


    //灰度处理
    Mat gray_image;
    cvtColor(src, gray_image, COLOR_BGR2GRAY );


    //处理之后的图像
    std::ostringstream outputImagePath;
    outputImagePath<<outputImgDir<<"outputImage.jpg";
    cv::imwrite(outputImagePath.str(),gray_image);


    std::ostringstream outputJson;
    outputJson<<"{\n"
              <<"\"outputImagePath\":\""
              <<outputImagePath.str()
              <<"\"}";

    return (env)->NewStringUTF(
            outputJson.str().data());
}
