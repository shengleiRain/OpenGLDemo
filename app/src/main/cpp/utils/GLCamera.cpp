//
// Created by shenglei on 2022/6/28.
//

#include <ext/matrix_transform.hpp>
#include "GLCamera.h"

glm::mat4 GLCamera::getViewMatrix() const {
    auto cameraTarget = cameraPos + cameraFront;
    return glm::lookAt(cameraPos, cameraTarget, cameraUp);
}

void GLCamera::front() {
    cameraPos += cameraFront * speed;
}

void GLCamera::back() {
    cameraPos -= cameraFront * speed;
}

void GLCamera::left() {
    cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp) * speed);
}

void GLCamera::right() {
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp) * speed);
}

GLCamera::GLCamera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) : cameraPos(pos),
                                                                   cameraFront(front),
                                                                   cameraUp(up) {

}

