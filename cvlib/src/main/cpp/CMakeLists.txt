# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html


cmake_minimum_required(VERSION 3.10.2)

SET(PROJECT_NAME OpenCVLib)
#project("jniapp")

SET(OpenCV_FOUND true )
FIND_PACKAGE(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(
        ${PROJECT_NAME}
        SHARED
        OpenCVLib.cpp)

find_library( # Sets the name of the path variable.
              log-lib
              log )

target_link_libraries(
        ${PROJECT_NAME}
        ${OpenCV_LIBS}
        ${log-lib} )