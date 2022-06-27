//
// Created by shenglei on 2022/6/27.
//

#ifndef OPENGLDEMO_RECTTEXSAMPLE_H
#define OPENGLDEMO_RECTTEXSAMPLE_H

#include "BaseSample.h"
#include <GLES3/gl3.h>

class RectTexSample : public BaseSample {
private:
    GLuint vao;
    GLuint vbo;
public:
    void draw() const override;
    void init() override;
    void setImageData(const ImageSharedPtr &imageSharedPtr) override;

protected:
    const char *vertexShaderName() const override;

    const char *fragShaderName() const override;
};


#endif //OPENGLDEMO_RECTTEXSAMPLE_H
