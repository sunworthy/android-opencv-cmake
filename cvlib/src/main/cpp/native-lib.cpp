#include <jni.h>
#include <string>
#include <syslog.h>
#include <android/bitmap.h>
#include "cv-lib.h"

#define TYPE_BLUR     0
#define TYPE_GAUSSIAN_BLUR 1
#define TYPE_MEDIAN_BLUR 2
#define TYPE_BILATERAL_FILTER 3
#define TYPE_DILATE 4
#define TYPE_ERODE 5
#define TYPE_MORPHO_LOGYEX 6
#define TYPE_CONVERT_SCALEABS 7
#define TYPE_SOBEL 8
#define TYPE_LAPLACIAN 9
#define TYPE_SCHAR 10
#define TYPE_CANNY 11

std::string getClassName(JNIEnv *env, jclass clazz) {
    jclass jls = env->FindClass("java/lang/Class");
    jmethodID mid_getName = env->GetMethodID(jls, "getName", "()Ljava/lang/String;");
    auto strObj = (jstring) env->CallObjectMethod(clazz, mid_getName);
    const char *localName = env->GetStringUTFChars(strObj, nullptr);
    std::string class_name = localName;
    env->ReleaseStringUTFChars(strObj, localName);
    return class_name;
}

int bitmapToMat(JNIEnv *env, jobject obj_bitmap, cv::Mat &matrix) {
    void *pixels;                                            // Save picture pixel data
    AndroidBitmapInfo info;                                   // Save picture parameters
    if (AndroidBitmap_getInfo(env, obj_bitmap, &info) < 0) {
        syslog(LOG_INFO, "error retrieving bitmap meta data");
        return -1;
    }
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        syslog(LOG_INFO, "expecting RGBA_8888 format");
        return -1;
    }
    if (AndroidBitmap_lockPixels(env, obj_bitmap, (void **) &pixels) < 0) {
        syslog(LOG_INFO, "unable to lock bitmap pixels");
        return -1;
    }
    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        cv::Mat tmp((int) info.height, (int) info.width, CV_8UC4, pixels);
        tmp.copyTo(matrix);
    } else {
        cv::Mat tmp((int) info.height, (int) info.width, CV_8UC2, pixels);
        cv::cvtColor(tmp, matrix, cv::COLOR_BGR5652RGB);
    }
    //convert RGB to BGR
    cv::cvtColor(matrix, matrix, cv::COLOR_RGB2BGR);
    AndroidBitmap_unlockPixels(env, obj_bitmap);
    return 0;
}

bool matToBitmap(JNIEnv *env, cv::Mat &matrix, jobject obj_bitmap) {
    void *pixels;                                            // Save picture pixel data
    AndroidBitmapInfo info;                                   // Save picture parameters
    if (AndroidBitmap_getInfo(env, obj_bitmap, &info) < 0) {
        syslog(LOG_INFO, "error retrieving bitmap meta data");
        return -1;
    }
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888 &&
        info.format != ANDROID_BITMAP_FORMAT_RGB_565) {
        syslog(LOG_INFO, "Only ARGB 8888 and RGB 565 are supported");
        return -1;
    }
    if (AndroidBitmap_lockPixels(env, obj_bitmap, (void **) &pixels) < 0) {
        syslog(LOG_INFO, "unable to lock bitmap pixels");
        return -1;
    }
    if (matrix.dims != 2 || info.height != (uint32_t) matrix.rows ||
        info.width != (uint32_t) matrix.cols) {
        syslog(LOG_INFO, "it must be a 2-dimensional matrix with the same length and width");
        return -1;
    }
    if (matrix.type() != CV_8UC1 && matrix.type() != CV_8UC3 && matrix.type() != CV_8UC4) {
        syslog(LOG_INFO, "it must one of CV_8UC1 CV_8UC3 CV_8UC4");
        return -1;
    }
    if (AndroidBitmap_lockPixels(env, obj_bitmap, &pixels) < 0) {
        syslog(LOG_INFO, "can not lock pixels");
        return -1;
    }

    if (info.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
        cv::Mat tmp((int) info.height, (int) info.width, CV_8UC4, pixels);
        switch (matrix.type()) {
            case CV_8UC1:
                cv::cvtColor(matrix, tmp, cv::COLOR_GRAY2RGBA);
                break;
            case CV_8UC3:
                cv::cvtColor(matrix, tmp, cv::COLOR_RGB2RGBA);
                break;
            case CV_8UC4:
                matrix.copyTo(tmp);
                break;
            default:
                AndroidBitmap_unlockPixels(env, obj_bitmap);
                return false;
        }
    } else {
        cv::Mat tmp((int) info.height, (int) info.width, CV_8UC2, pixels);
        switch (matrix.type()) {
            case CV_8UC1:
                cv::cvtColor(matrix, tmp, cv::COLOR_GRAY2BGR565);
                break;
            case CV_8UC3:
                cv::cvtColor(matrix, tmp, cv::COLOR_RGB2BGR565);
                break;
            case CV_8UC4:
                cv::cvtColor(matrix, tmp, cv::COLOR_RGBA2BGR565);
                break;
            default:
                AndroidBitmap_unlockPixels(env, obj_bitmap);
                return false;
        }
    }
    AndroidBitmap_unlockPixels(env, obj_bitmap);
    return true;
}
//
//std::string jstringToString(JNIEnv *env, jstring jStr) {
//    if (!jStr) {
//        return "";
//    }
//
//    const jclass stringClass = env->GetObjectClass(jStr);
//    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
//    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes,
//                                                                       env->NewStringUTF("UTF-8"));
//
//    size_t length = (size_t) env->GetArrayLength(stringJbytes);
//    jbyte *pBytes = env->GetByteArrayElements(stringJbytes, NULL);
//
//    std::string ret = std::string((char *) pBytes, length);
//    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);
//
////    std::ostringstream outputImagePath;
////    outputImagePath << "" << endl;
////    jstring jstring1 = (env)->NewStringUTF(outputImagePath.str().data());
//
//    env->DeleteLocalRef(stringJbytes);
//    env->DeleteLocalRef(stringClass);
//    return ret;
//}

extern "C"
JNIEXPORT void JNICALL
Java_com_joshkryo_lib_CVLib4_process_1bitmap(JNIEnv *env, jclass clazz, jobject bitmap,
                                             jint j_type, jobject bitmap_out) {
    std::string class_name = getClassName(env, clazz);
    int type = (int) j_type;
    syslog(LOG_INFO, "%s %d", class_name.c_str(), type);

    Mat tmp;
    bitmapToMat(env, bitmap, tmp);

    switch (type) {
        case TYPE_BLUR:
            CvLib::ImageProcess::cvBlur(tmp);
            break;
        case TYPE_GAUSSIAN_BLUR:
            CvLib::ImageProcess::cvGaussianBlur(tmp);
            break;
        case TYPE_MEDIAN_BLUR:
            CvLib::ImageProcess::cvMedianBlur(tmp);
            break;
        case TYPE_BILATERAL_FILTER:
            CvLib::ImageProcess::cvBilateralFilter(tmp);
            break;
        case TYPE_DILATE:
            CvLib::ImageProcess::cvDilate(tmp);
            break;
        case TYPE_ERODE:
            CvLib::ImageProcess::cvErode(tmp);
            break;
        case TYPE_MORPHO_LOGYEX:
            CvLib::ImageProcess::cvMorphologyEx(tmp);
            break;
        case TYPE_CONVERT_SCALEABS:
            CvLib::ImageProcess::cvConvertScaleAbs(tmp);
            break;
        case TYPE_SOBEL:
            CvLib::ImageProcess::cvSobel(tmp);
            break;
        case TYPE_LAPLACIAN:
            CvLib::ImageProcess::cvLaplacian(tmp);
            break;
        case TYPE_SCHAR:
            CvLib::ImageProcess::cvScharr(tmp);
            break;
        case TYPE_CANNY:
            CvLib::ImageProcess::cvCanny(tmp);
            break;
        default:
            // ignore
            break;
    }
    matToBitmap(env, tmp, bitmap_out);
}