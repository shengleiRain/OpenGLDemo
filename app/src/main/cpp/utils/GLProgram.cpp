//
// Created by shenglei on 2022/6/25.
//

#include <gtc/type_ptr.hpp>
#include "GLProgram.h"

GLProgram::GLProgram(const char *cVertexFilename, const char *cFragFilename) : vertexFilename(cVertexFilename),
                                                                               fragFilename(cFragFilename){
    if (cVertexFilename == nullptr || cFragFilename == nullptr) {
        return;
    }
//    programHandle = GLUtils::createProgram(cVertexFilename, cFragFilename, vertexShaderHandle, fragShaderHandle);
    programHandle = GLUtils::createProgramFromAsset(cVertexFilename, cFragFilename, vertexShaderHandle, fragShaderHandle);
}

void GLProgram::use() const {
    glUseProgram(programHandle);
}

void GLProgram::setInt(const char* uniformName, int value) const {
    auto uniform = glGetUniformLocation(programHandle, uniformName);
    glUniform1i(uniform, value);
}

void GLProgram::setFloat(const char *uniformName, float value) const {
    auto uniform = glGetUniformLocation(programHandle, uniformName);
    glUniform1f(uniform, value);
}

void GLProgram::setMat4(const char *uniformName, const float *values) const {
    auto uniform = glGetUniformLocation(programHandle, uniformName);
    glUniformMatrix4fv(uniform, 1, GL_FALSE, values);
}

void GLProgram::setMat4(const char *uniformName, glm::mat4 value) const {
    auto uniform = glGetUniformLocation(programHandle, uniformName);
    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
}

