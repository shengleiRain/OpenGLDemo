//
// Created by shenglei on 2022/6/26.
//

#ifndef OPENGLDEMO_TRIANGLESAMPLE_H
#define OPENGLDEMO_TRIANGLESAMPLE_H

#include "GLProgram.h"
#include "BaseSample.h"

class TriangleSample : public BaseSample{
public:
    TriangleSample();
    ~TriangleSample();
    void draw() const override;
    const char * vertexShaderName() const override;
    const char * fragShaderName() const override;
};


#endif //OPENGLDEMO_TRIANGLESAMPLE_H
