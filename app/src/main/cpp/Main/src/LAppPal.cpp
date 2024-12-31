/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#include "LAppPal.hpp"
#include <cstdio>
#include <stdarg.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <Model/CubismMoc.hpp>
#include "LAppDefine.hpp"

#include <chrono>
#include <Log.hpp>

#include <filesystem>

using std::endl;
using namespace Csm;
using namespace std;
using namespace LAppDefine;

double LAppPal::s_currentFrame = 0.0;
double LAppPal::s_lastFrame = 0.0;
double LAppPal::s_deltaTime = 0.0;


using namespace Csm;

static JavaVM *g_JVM; // JavaVM is valid for all threads, so just save it globally
static jclass l2dClass;
static jmethodID loadFileBytesID;

JNIEnv *GetEnv() {
    JNIEnv *env = NULL;
    g_JVM->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    return env;
}

void LAppPal::Init(JavaVM* jvm, jclass clazz, jmethodID lfbID) {
    g_JVM = jvm;
    l2dClass = clazz;
    loadFileBytesID = lfbID;
}

csmByte *LAppPal::LoadFileAsBytes(const string filePath, csmSizeInt *outSize) {
    JNIEnv *env = GetEnv();

    // ファイルロード
    jbyteArray obj = (jbyteArray) env->CallStaticObjectMethod(l2dClass,
                                                              loadFileBytesID,
                                                              env->NewStringUTF(filePath.c_str()));

    // ファイルが見つからなかったらnullが返ってくるためチェック
    if (!obj) {
        return NULL;
    }

    *outSize = static_cast<unsigned int>(env->GetArrayLength(obj));

    char *buffer = new char[*outSize];
    env->GetByteArrayRegion(obj, 0, *outSize, reinterpret_cast<jbyte *>(buffer));

    return reinterpret_cast<unsigned char *>(buffer);
}

void LAppPal::ReleaseBytes(csmByte *byteData) {
    delete[] byteData;
}

csmFloat32 LAppPal::GetDeltaTime() {
    return static_cast<csmFloat32>(s_deltaTime);
}

static double systemTime() {
    struct timespec res;
    clock_gettime(CLOCK_MONOTONIC, &res);
    return (res.tv_sec + res.tv_nsec * 1e-9);
}

void LAppPal::UpdateTime() {
    s_currentFrame = systemTime();
    s_deltaTime = s_currentFrame - s_lastFrame;
    s_lastFrame = s_currentFrame;
}

void LAppPal::PrintLn(const Csm::csmChar *message) {
    Info("%s", message);
}





