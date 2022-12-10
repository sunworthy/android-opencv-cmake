cmake_minimum_required(VERSION 3.18.1)

project("cv_lib4")
set(PROJECT_NAME cv_lib4)
# opencv-android sdk
set(OpenCV_DIR "/mnt/app/local/opencv/openCV-android-sdk4/sdk/native/jni")
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

add_library(
        ${PROJECT_NAME}
        SHARED
        native-lib.cpp cv-lib.h cv-lib.cpp)

find_library(log-lib log)

target_link_libraries(
        ${PROJECT_NAME}
        ${log-lib}
        ${OpenCV_LIBS}
        jnigraphics)


