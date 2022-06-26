//
// Created by shenglei on 2022/6/25.
//

#include "NDKUtil.h"
#include <stdlib.h>
#include <android/asset_manager_jni.h>

static jclass g_activityThread = nullptr;
static jmethodID g_currentActivityThread = nullptr;
static jmethodID g_getApplication = nullptr;
static jclass g_pContextClass = nullptr;
static jmethodID g_getAssets = nullptr;

JavaVM *javaVm = nullptr;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = nullptr;
    jint result = -1;

    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }

    javaVm = vm;

    NDKUtil::InitNDKUtil(env);

    // 返回jni的版本
    return JNI_VERSION_1_4;
}


void NDKUtil::InitNDKUtil(JNIEnv *env) {
    if (nullptr == env) {
        return;
    }

//activity class
    jclass activityThread = env->FindClass("android/app/ActivityThread");
    g_activityThread = (jclass) env->NewGlobalRef(activityThread);
    env->DeleteLocalRef(activityThread);

//
    g_currentActivityThread = env->GetStaticMethodID(g_activityThread,
                                                     "currentActivityThread",
                                                     "()Landroid/app/ActivityThread;");


    g_getApplication = env->GetMethodID(g_activityThread, "getApplication",
                                        "()Landroid/app/Application;");

//全局context类
    jclass pContextClass = env->FindClass("android/app/Application");
    g_pContextClass = (jclass) env->NewGlobalRef(pContextClass);
    env->DeleteLocalRef(pContextClass);

//assets
    g_getAssets = env->GetMethodID(g_pContextClass, "getAssets",
                                   "()Landroid/content/res/AssetManager;");
}

//获得android java程序的Context对象
jobject NDKUtil::GetGlobalContext(JNIEnv *env) {
    if (nullptr == env) {
        return nullptr;
    }

//获取Activity Thread的实例对象
    jclass activityThread = g_activityThread;
    if (nullptr == activityThread) {
        return nullptr;
    }

    jmethodID currentActivityThread = g_currentActivityThread;

    if (nullptr == currentActivityThread) {
        return nullptr;
    }

    jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);
    if (nullptr == at) {
        return nullptr;
    }

//获取Application，也就是全局的Context
    jmethodID getApplication = g_getApplication;
    jobject context = env->CallObjectMethod(at, getApplication);
    env->DeleteLocalRef(at);

    return context;
}

AAssetManager *NDKUtil::GetAssetManager(JNIEnv *env, jobject context) {
    if (nullptr == env || nullptr == context) {
        return nullptr;
    }

    jclass pClass = g_pContextClass;
    if (nullptr == pClass) {
        return nullptr;
    }

//获得getAssets方法
    jmethodID getAssets = g_getAssets;
    if (nullptr == getAssets) {
        return nullptr;
    }

//创建一个AssetManager对象
    return AAssetManager_fromJava(env, env->CallObjectMethod(context, getAssets));
}
