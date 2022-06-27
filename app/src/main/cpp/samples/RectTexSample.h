//
// Created by shenglei on 2022/6/27.
//

#ifndef OPENGLDEMO_RECTTEXSAMPLE_H
#define OPENGLDEMO_RECTTEXSAMPLE_H

#include "BaseSample.h"

class RectTexSample : public BaseSample {
public:
    void draw() const override;

protected:
    const char *vertexShaderName() const override;

    const char *fragShaderName() const override;
};


#endif //OPENGLDEMO_RECTTEXSAMPLE_H
