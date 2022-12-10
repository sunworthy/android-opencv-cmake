cmake_minimum_required(VERSION 3.18.1)

project("cv_lib4")
SET(PROJECT_NAME cv_lib4)

#SET(OpenCV_FOUND true )
#FIND_PACKAGE(OpenCV REQUIRED)

add_library(
        ${PROJECT_NAME}
        SHARED
        cv-native-lib.cpp)

find_library(log-lib log)

target_link_libraries(
        ${PROJECT_NAME}
        ${log-lib} )


