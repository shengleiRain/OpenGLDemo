//
// Created by shenglei on 2022/6/25.
//

#ifndef OPENGLDEMO_GLPROGRAM_H
#define OPENGLDEMO_GLPROGRAM_H

#include <string>
#include <GLES3/gl3.h>
#include "GLUtils.h"
#include "glm.hpp"

class GLProgram {
private:
    std::string vertexFilename;
    std::string fragFilename;
    GLuint programHandle{};
    GLuint vertexShaderHandle{};
    GLuint fragShaderHandle{};

public:
    GLProgram(const char *cVertexFilename, const char *cFragFilename);

    GLuint getProgramHandle() const {
        return programHandle;
    }

    GLuint getVertexShaderHandle() const {
        return vertexShaderHandle;
    }

    GLuint getFragShaderHandle() const {
        return fragShaderHandle;
    }

    void use() const;

    void setInt(const char *uniformName, int value) const;

    void setFloat(const char *uniformName, float value) const;

    void setMat4(const char *uniformName, const float *values) const;

    void setMat4(const char *uniformName, glm::mat4 value) const;
};


#endif //OPENGLDEMO_GLPROGRAM_H
