cmake_minimum_required(VERSION 3.18.1)
project("opengl")

add_library(
        opengl
        SHARED
        utils/NDKUtil.cpp
        utils/android_fopen.cpp
        utils/GLUtils.cpp
        utils/GLProgram.cpp
        renders/NativeRender_JNI.cpp
        renders/NativeRenderContext.cpp
        samples/TriangleSample.cpp
        opengl.cpp)

include_directories(utils)
include_directories(renders)
include_directories(samples)


target_link_libraries(
        opengl
        android
        GLESv3
        log)
