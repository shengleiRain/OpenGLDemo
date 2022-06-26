//
// Created by shenglei on 2022/6/25.
//

#ifndef OPENGLDEMO_GLUTILS_H
#define OPENGLDEMO_GLUTILS_H

#include <GLES3/gl3.h>
#include "AndroidLog.h"
#include "android_fopen.h"

class GLUtils {
public:
    static GLuint loadShaderFromAsset(GLenum shaderType, const char *sourceFilename);

    static GLuint loadShader(GLenum shaderType, const char *source);

    static GLuint
    createProgram(GLuint &vertexShaderHandle,GLuint &fragShaderHandle);

    static GLuint
    createProgram(const char *vertexSource, const char *fragSource, GLuint &vertexShaderHandle,
                  GLuint &fragShaderHandle);

    static GLuint
    createProgramFromAsset(const char *vertexSourceFilename, const char *fragSourceFilename, GLuint &vertexShaderHandle,
                  GLuint &fragShaderHandle);

    static void deleteProgram(GLuint &program);

    static void checkGLError(const char *glOperation);
};


#endif //OPENGLDEMO_GLUTILS_H
