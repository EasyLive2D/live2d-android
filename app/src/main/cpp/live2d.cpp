#include <jni.h>
#include <string>
#include <CubismFramework.hpp>
#include <LAppAllocator.hpp>
#include <LAppPal.hpp>
#include <Log.hpp>
#include <GLES2/gl2.h>

static LAppAllocator cubismAllocator;
static Csm::CubismFramework::Option cubismOption;

extern "C"
JNIEXPORT void JNICALL
Java_com_arkueid_live2d_Live2D_1v3_init(JNIEnv *env, jclass clazz) {
    cubismOption.LogFunction = LAppPal::PrintLn;
    cubismOption.LoggingLevel = Csm::CubismFramework::Option::LogLevel_Verbose;

    Csm::CubismFramework::CleanUp();
    Csm::CubismFramework::StartUp(&cubismAllocator, &cubismOption);
    Csm::CubismFramework::Initialize();

    JavaVM *jvm;
    env->GetJavaVM(&jvm);
    jmethodID lfb = env->GetStaticMethodID(clazz, "loadFileBytes", "(Ljava/lang/String;)[B");
    LAppPal::Init(jvm, clazz, lfb);

    LAppPal::UpdateTime();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_arkueid_live2d_Live2D_1v3_dispose(JNIEnv *env, jclass clazz) {
    Csm::CubismFramework::Dispose();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_arkueid_live2d_Live2D_1v3_clearBuffer(JNIEnv *env, jclass clazz, jfloat r, jfloat g,
                                               jfloat b, jfloat a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepthf(1.0f);
}