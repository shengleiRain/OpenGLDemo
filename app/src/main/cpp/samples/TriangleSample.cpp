//
// Created by shenglei on 2022/6/26.
//

#include "TriangleSample.h"

TriangleSample::TriangleSample() = default;

TriangleSample::~TriangleSample() {
    delete program;
    program = nullptr;
}

void TriangleSample::draw() const {
    GLfloat vVertices[] = {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
    };
    if (program) {
        program->use();
    }
    // Load the vertex data
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, vVertices );
    glEnableVertexAttribArray (0);

    glDrawArrays (GL_TRIANGLES, 0, 3);
}

const char *TriangleSample::vertexShaderName() const {
    return "shaders/rect.vert";
}

const char *TriangleSample::fragShaderName() const {
    return "shaders/rect.frag";
}


