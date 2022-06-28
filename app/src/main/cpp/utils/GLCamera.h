//
// Created by shenglei on 2022/6/28.
//

#ifndef OPENGLDEMO_GLCAMERA_H
#define OPENGLDEMO_GLCAMERA_H

#include <glm.hpp>

class GLCamera {
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float speed = 0.05f;

public:
    GLCamera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
             glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
             glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 getViewMatrix() const;

    void front();

    void back();

    void left();

    void right();
};


#endif //OPENGLDEMO_GLCAMERA_H
