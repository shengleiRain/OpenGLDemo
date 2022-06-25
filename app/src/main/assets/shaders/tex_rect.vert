#version 300 es
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
//uniform mat4 mvpMatrix;

out vec3 outColor;
out vec2 texCoord;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    outColor = aColor;
    texCoord = vec2(aTexCoord.x, aTexCoord.y);
}
