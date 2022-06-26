//
// Created by shenglei on 2022/6/25.
//

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
