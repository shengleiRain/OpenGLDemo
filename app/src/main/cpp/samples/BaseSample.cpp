//
// Created by shenglei on 2022/6/27.
//

#include "BaseSample.h"

void BaseSample::init() {
    program = new GLProgram(vertexShaderName(), fragShaderName());
}

BaseSample::~BaseSample() {
    delete program;
    program = nullptr;
}
