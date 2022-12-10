#include <jni.h>
#include <string>
#include <syslog.h>

std::string getClassName(JNIEnv *pEnv, jclass pJclass);

extern "C"
__attribute__((unused))
JNIEXPORT jstring JNICALL Java_com_joshkryo_lib_CVLib4_stringFromJNI(
        JNIEnv *env,
        jclass clazz) {
    std::string class_name = getClassName(env, clazz);
    syslog(LOG_INFO, "%s", class_name.c_str());

    std::string hello = "Hello from C++ " + class_name;
    return env->NewStringUTF(hello.c_str());
}

std::string getClassName(JNIEnv *env, jclass clazz) {
    jclass jls = env->FindClass("java/lang/Class");
    jmethodID mid_getName = env->GetMethodID(jls, "getName", "()Ljava/lang/String;");
    auto strObj = (jstring) env->CallObjectMethod(clazz, mid_getName);
    const char *localName = env->GetStringUTFChars(strObj, nullptr);
    std::string class_name = localName;
    env->ReleaseStringUTFChars(strObj, localName);
    return class_name;
}