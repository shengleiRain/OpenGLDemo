//
// Created by shenglei on 2022/6/26.
//

#ifndef OPENGLDEMO_TRIANGLESAMPLE_H
#define OPENGLDEMO_TRIANGLESAMPLE_H

#include "GLProgram.h"

class TriangleSample {
private:
    GLProgram* program = nullptr;
    static const char* VERTEX_NAME;
    static const char* FRAG_NAME;
    static const char* vShaderStr;
    static const char* fShaderStr;

public:
    TriangleSample();
    ~TriangleSample();
    void init();
    void draw();
};


#endif //OPENGLDEMO_TRIANGLESAMPLE_H
