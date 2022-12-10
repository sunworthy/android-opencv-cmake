# Android-opencv-cmake

> Android 集成 opencv示例, 使用cmake 文件编译; 使用cmake的好处: studio原生支持, 方便debug c++库

如果直接导入OpenCV的SDK，然后通过opencv的Utils实现bitmap到cv::Mat的转换, 会加载所有so库, 导致最终的apk文件比较大。

如果使用jni直接编译opencv的cpp， 则只打包需求的部分， apk体积比较小

## 环境要求
* Android Studio, ndk, opencv4, c++14

* 在build.gradle中配置cmake参数

```
externalNativeBuild {
     cmake {
         cppFlags '-std=c++14'
     }
}
ndk {
      abiFilters  "armeabi-v7a"   //, "arm64-v8a","armeabi",
}
...
externalNativeBuild {
    cmake {
        path file('src/main/cpp/CMakeLists.txt')
        version '3.18.1'
    }
}

```

* CMakeLists.txt
```txt
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
```

## License
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
