//
// Created by shenglei on 2022/6/27.
//

#ifndef OPENGLDEMO_RECTTEXSAMPLE_H
#define OPENGLDEMO_RECTTEXSAMPLE_H

#include "BaseSample.h"
#include <GLES3/gl3.h>
#include "GLCamera.h"

class RectTexSample : public BaseSample {
private:
    GLuint vao;
    GLuint vbo;
    GLCamera camera;
public:
    void draw() const override;
    void init() override;
    void setImageData(const ImageSharedPtr &imageSharedPtr) override;

    void moveFront();

    void moveBack();
    void moveLeft();
    void moveRight();

protected:
    const char *vertexShaderName() const override;

    const char *fragShaderName() const override;
};


#endif //OPENGLDEMO_RECTTEXSAMPLE_H
