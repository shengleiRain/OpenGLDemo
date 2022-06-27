//
// Created by shenglei on 2022/6/27.
//

#ifndef OPENGLDEMO_BASESAMPLE_H
#define OPENGLDEMO_BASESAMPLE_H

#include "GLProgram.h"
#include "CoreImage.h"
#include <vector>

class BaseSample {
protected:
    GLProgram *program = nullptr;

    int width{};
    int height{};

    virtual const char *vertexShaderName() const = 0;

    virtual const char *fragShaderName() const = 0;

    std::vector<GLuint> textureIds;

public:
    virtual ~BaseSample();

    virtual void init();

    virtual void setImageData(const ImageSharedPtr &imageSharedPtr);

    virtual void draw() const = 0;

    virtual void setViewSize(int width, int height);
};


#endif //OPENGLDEMO_BASESAMPLE_H
