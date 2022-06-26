//
// Created by shenglei on 2022/6/26.
//

#include "TriangleSample.h"

const char *TriangleSample::VERTEX_NAME = "shaders/rect.vert";
const char *TriangleSample::FRAG_NAME = "shaders/rect.frag";

const char* TriangleSample::vShaderStr =
        "#version 300 es                          \n"
        "layout(location = 0) in vec4 vPosition;  \n"
        "void main()                              \n"
        "{                                        \n"
        "   gl_Position = vPosition;              \n"
        "}                                        \n";

const char* TriangleSample::fShaderStr =
        "#version 300 es                              \n"
        "precision mediump float;                     \n"
        "out vec4 fragColor;                          \n"
        "void main()                                  \n"
        "{                                            \n"
        "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
        "}                                            \n";

TriangleSample::TriangleSample() = default;

TriangleSample::~TriangleSample() {
    if (program) {
        delete program;
        program = nullptr;
    }
}

void TriangleSample::init() {
    program = new GLProgram(VERTEX_NAME, FRAG_NAME);
}

void TriangleSample::draw() {
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


