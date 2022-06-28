//
// Created by shenglei on 2022/6/26.
//

#ifndef OPENGLDEMO_NATIVERENDERCONTEXT_H
#define OPENGLDEMO_NATIVERENDERCONTEXT_H

#include <mutex>
#include "AndroidLog.h"
#include <GLES3/gl3.h>
#include "TriangleSample.h"
#include "RectTexSample.h"

class NativeRenderContext {
public:
    static NativeRenderContext* getInstance();

    static void onSurfaceCreated();

    static void onSurfaceChanged(int width, int height);

    static void onDrawFrame();

    static void setBitmap(const ImageSharedPtr& imageSharedPtr);

    static void moveCamera(int direction);
private:
    static NativeRenderContext *sInstance;
    static std::once_flag sOnceFlag;
    static const char* tag;

    static TriangleSample triangleSample;
    static RectTexSample rectTexSample;
};


#endif //OPENGLDEMO_NATIVERENDERCONTEXT_H
