//
// Created by shenglei on 2022/6/25.
//

#ifndef OPENGLDEMO_NDKUTIL_H
#define OPENGLDEMO_NDKUTIL_H

#include <jni.h>
#include <android/asset_manager.h>
#include "AndroidLog.h"

class NDKUtil {
public:
    //初始化ndkutil的相关全局变量
    static void InitNDKUtil(JNIEnv *env);

    //获得程序的context对象
    static jobject GetGlobalContext(JNIEnv *env);

    //获得assetmanager对象
    static AAssetManager *GetAssetManager(JNIEnv *env, jobject context);
};


#endif //OPENGLDEMO_NDKUTIL_H
