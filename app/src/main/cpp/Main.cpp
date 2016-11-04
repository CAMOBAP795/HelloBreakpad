//
// Created by Zach on 2/11/16.
//


#include <jni.h>
#include <string>
#include "android/log.h"

#include "google-breakpad/src/client/linux/handler/exception_handler.h"

#ifdef __cplusplus
extern "C"
{
#endif

bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded) {
    __android_log_print(ANDROID_LOG_INFO, "breakpad", "Dump path: %s\n", descriptor.path());
    return succeeded;
}


jstring Java_com_spiritedrunning_zach_hellobreakpad2_MainActivity_stringFromJNI(JNIEnv *env, jobject /* this */) {
    google_breakpad::MinidumpDescriptor descriptor("/storage/emulated/0/hellobreakpad");
    google_breakpad::ExceptionHandler eh(descriptor, NULL, DumpCallback, NULL, true, -1);

    volatile int *a = (int*)(NULL);
    *a = 1;
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

jint JNI_OnLoad(JavaVM *vm, void * /*reserved*/) {

    __android_log_print(ANDROID_LOG_INFO, "breakpad", "JNI onLoad...");

    return JNI_VERSION_1_4;
}


#ifdef __cplusplus
}
#endif
