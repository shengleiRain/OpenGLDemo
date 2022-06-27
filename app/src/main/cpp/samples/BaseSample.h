//
// Created by shenglei on 2022/6/27.
//

#ifndef OPENGLDEMO_BASESAMPLE_H
#define OPENGLDEMO_BASESAMPLE_H

#include "GLProgram.h"

class BaseSample {
protected:
    GLProgram *program = nullptr;

    virtual const char *vertexShaderName() const = 0;

    virtual const char *fragShaderName() const = 0;

public:
    virtual ~BaseSample();

    virtual void init();

    virtual void draw() const = 0;
};


#endif //OPENGLDEMO_BASESAMPLE_H
