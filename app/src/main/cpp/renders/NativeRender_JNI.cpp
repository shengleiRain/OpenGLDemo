//
// Created by shenglei on 2022/6/26.
//
#include <jni.h>
#include "AndroidLog.h"
#include "NativeRenderContext.h"
#include "ImageUtil.h"


extern "C"
JNIEXPORT void JNICALL
Java_com_sl_java_opengl_rendering_cnative_NativeRender_nativeOnInit(JNIEnv *env, jobject thiz) {

}
extern "C"
JNIEXPORT void JNICALL
Java_com_sl_java_opengl_rendering_cnative_NativeRender_nativeOnUnInit(JNIEnv *env, jobject thiz) {
    // TODO: implement nativeOnUnInit()
}
extern "C"
JNIEXPORT void JNICALL
Java_com_sl_java_opengl_rendering_cnative_NativeRender_nativeOnSurfaceCreated(JNIEnv *env,
                                                                              jobject thiz) {
    NativeRenderContext::onSurfaceCreated();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_sl_java_opengl_rendering_cnative_NativeRender_nativeOnSurfaceChanged(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jint width,
                                                                              jint height) {
    NativeRenderContext::onSurfaceChanged(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_sl_java_opengl_rendering_cnative_NativeRender_nativeOnDrawFrame(JNIEnv *env,
                                                                         jobject thiz) {
    NativeRenderContext::onDrawFrame();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_sl_java_opengl_rendering_cnative_NativeRender_nativeSetBitmap(JNIEnv *env, jobject thiz,
                                                                       jobject bitmap) {
    void* pixelAddr = nullptr;
    AndroidBitmap_lockPixels(env, bitmap, &pixelAddr);

    AndroidBitmapInfo bitmapInfo;
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);

    ImageSharedPtr imageSharedPtr = ImageUtil::convertBitmap2Image(pixelAddr, bitmapInfo);
    NativeRenderContext::setBitmap(imageSharedPtr);
    AndroidBitmap_unlockPixels(env, bitmap);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sl_java_opengl_rendering_cnative_NativeRender_nativeMoveCamera(JNIEnv *env, jobject thiz,
                                                                        jint direction) {
    NativeRenderContext::moveCamera(direction);
}