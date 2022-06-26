//
// Created by shenglei on 2022/6/26.
//

#include "NativeRenderContext.h"

std::once_flag NativeRenderContext::sOnceFlag;
NativeRenderContext *NativeRenderContext::sInstance = nullptr;
const char *NativeRenderContext::tag = "NativeRenderContext";
TriangleSample NativeRenderContext::triangleSample;


NativeRenderContext *NativeRenderContext::getInstance() {
    std::call_once(sOnceFlag, [] {
        sInstance = new NativeRenderContext();
    });
    return sInstance;
}

void NativeRenderContext::onSurfaceCreated() {
    LOGD(tag, "onSurfaceCreated");
    glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

    triangleSample.init();
}

void NativeRenderContext::onSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void NativeRenderContext::onDrawFrame() {
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    triangleSample.draw();
}
