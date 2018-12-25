# Android-opencv-cmake

> Android 集成 opencv示例, 使用cmake 文件编译; 使用cmake的好处: studio原生支持, 方便debug c++库
    
## 环境要求
* Android studio 2.3.3及以上
* Cmake3.0及以上
* ndk14
* opencv2.4.13 or opencv3.3

## 配置
* 在local.properties 文件中配置opencv sdk 路径

opencv.dir = ${opencv_sdk_dir}
```
ndk.dir=/Users/king/Library/Android/ndk14
sdk.dir=/Users/king/Library/Android/sdk
opencv.dir=/Users/king/Libs/OpenCV2413
```


* 在build.gradle中配置cmake参数

```
externalNativeBuild {
     cmake {
           cppFlags "-std=c++11 -frtti -fexceptions"
           arguments "-DOpenCV_DIR=" + getOpenCVDir().toString()+"/sdk/native/jni", "-DANDROID_ARM_NEON=TRUE"
      }
}
ndk {
      abiFilters  "armeabi-v7a"   //, "arm64-v8a","armeabi",
}
...
def getOpenCVDir() {
    Properties properties = new Properties()
    properties.load(new File(rootDir.absolutePath + "/local.properties").newDataInputStream())
    def externalModuleDir = properties.getProperty('opencv.dir', null)
    if (externalModuleDir == null) {
        throw new GradleException(
                "OpenCV location not found. Define location with opencv.dir in the local.properties file!")
    }
    return externalModuleDir
}

```


## License
Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
