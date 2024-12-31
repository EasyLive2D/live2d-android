#pragma once

#include <android/log.h>

#define LOG_TAG "JNI_LOG" // 日志的标记

#define Info(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, ##__VA_ARGS__)
#define Error(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, ##__VA_ARGS__)
