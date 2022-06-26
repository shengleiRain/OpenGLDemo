// From: http://www.50ply.com/blog/2013/01/19/loading-compressed-android-assets-with-file-pointer/

#include "android_fopen.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <android/asset_manager.h>
#include <mutex>
#include "NDKUtil.h"


static int android_read(void *cookie, char *buf, int size)
{
    int nReadBytes = AAsset_read((AAsset *)cookie, buf, size);
    return nReadBytes;
}

static int android_write(void *cookie, const char *buf, int size)
{
    return EACCES; // can't provide write access to the apk
}

static fpos_t android_seek(void *cookie, fpos_t offset, int whence)
{
    return AAsset_seek((AAsset *)cookie, offset, whence);
}

static int android_close(void *cookie)
{
    AAsset_close((AAsset *)cookie);
    return 0;
}

// 单例模式初始化assets
static AAssetManager *android_asset_manager = NULL;
static std::once_flag android_asset_manager_onceFlag;

extern JavaVM* javaVm;

static void androidInitAssetManager()
{
    std::call_once(android_asset_manager_onceFlag, []()
    {
        JavaVM* pJVM = javaVm;

        JNIEnv* env = NULL;
        int getEnvStat = pJVM->GetEnv((void **)&env, JNI_VERSION_1_4);

        //如果当前线程已经detach了，则attach
        if (getEnvStat == JNI_EDETACHED && NULL == env)
        {
            pJVM->AttachCurrentThread(&env, NULL);
        }

        AAssetManager *pAssetMgr = NDKUtil::GetAssetManager(env, NDKUtil::GetGlobalContext(env));

        android_asset_manager = pAssetMgr;

        if (getEnvStat == JNI_EDETACHED)
        {
            pJVM->DetachCurrentThread();
        }
    });
}

FILE *android_fopen(const char *fileName, const char *mode)
{
    if (NULL == fileName || NULL == mode)
    {
        return NULL;
    }

    if (strlen(fileName) <= 0 || strlen(mode) <= 0)
    {
        return NULL;
    }

    //不支持写数据
    if (mode[0] == 'w')
    {
        return NULL;
    }

    //一次初始化assetmanager
    androidInitAssetManager();
    AAsset *asset = AAssetManager_open(android_asset_manager, fileName, 0);
    if (!asset)
    {
        return NULL;
    }

    return funopen(asset, android_read, android_write, android_seek, android_close);
}


void readBinary(FILE* file, std::vector<char>& bytes)
{
    if (!file)
    {
        return;
    }
    fseek(file, 0L, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    bytes.resize(size);
    fread(bytes.data(), 1, size, file);
}

void getBinaryData(const char* fileName, std::vector<char>& bytes)
{
    if (!fileName)
    {
        return;
    }
    FILE* file = android_fopen(fileName, "rb");
    readBinary(file, bytes);
    fclose(file);
}


