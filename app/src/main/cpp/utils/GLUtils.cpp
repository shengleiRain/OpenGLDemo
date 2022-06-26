//
// Created by shenglei on 2022/6/25.
//

#include "GLUtils.h"

GLuint GLUtils::loadShader(GLenum shaderType, const char *source) {
    GLuint shader;
    shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &source, nullptr);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc((size_t) infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, nullptr, buf);
                    LOGE("GLUtils", "GLUtils::LoadShader Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

GLuint GLUtils::createProgram(const char *vertexSource, const char *fragSource,
                              GLuint &vertexShaderHandle, GLuint &fragShaderHandle) {
    GLuint program = 0;
    vertexShaderHandle = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShaderHandle) {
        return program;
    }
    fragShaderHandle = loadShader(GL_FRAGMENT_SHADER, fragSource);
    if (!fragShaderHandle) {
        return program;
    }

    return createProgram(vertexShaderHandle, fragShaderHandle);

}

GLuint
GLUtils::createProgramFromAsset(const char *vertexSourceFilename, const char *fragSourceFilename,
                                GLuint &vertexShaderHandle, GLuint &fragShaderHandle) {
    GLuint program = 0;
    vertexShaderHandle = loadShaderFromAsset(GL_VERTEX_SHADER, vertexSourceFilename);
    if (!vertexShaderHandle) {
        return program;
    }
    fragShaderHandle = loadShaderFromAsset(GL_FRAGMENT_SHADER, fragSourceFilename);
    if (!fragShaderHandle) {
        return program;
    }
    return createProgram(vertexShaderHandle, fragShaderHandle);
}

GLuint GLUtils::createProgram(GLuint &vertexShaderHandle, GLuint &fragShaderHandle) {
    GLuint program;
    program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShaderHandle);
        checkGLError("glAttachShader");
        glAttachShader(program, fragShaderHandle);
        checkGLError("glAttachShader");

        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        glDetachShader(program, vertexShaderHandle);
        glDeleteShader(vertexShaderHandle);
        vertexShaderHandle = 0;
        glDetachShader(program, fragShaderHandle);
        glDeleteShader(fragShaderHandle);
        fragShaderHandle = 0;
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc((size_t) bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, nullptr, buf);
                    LOGE("GLUtils", "GLUtils::CreateProgram Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

void GLUtils::deleteProgram(GLuint &program) {
    if (program) {
        glUseProgram(0);
        glDeleteProgram(program);
        program = 0;
    }
}

void GLUtils::checkGLError(const char *glOperation) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGE("GLUtils", "GLUtils::CheckGLError GL Operation %s() glError (0x%x)\n", glOperation,
             error);
    }
}

GLuint GLUtils::loadShaderFromAsset(GLenum shaderType, const char *sourceFilename) {
    std::vector<char> ret;
    getBinaryData(sourceFilename, ret);
    return loadShader(shaderType, reinterpret_cast<const char *>(ret.data()));
}



