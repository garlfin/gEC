#version 460 core

#include "../include.glsl"

layout (location = 0) in vec3 vPos;

void main()
{
    gl_Position = Camera.projection * Camera.view * Object.Model[0] * vec4(vPos, 1.0);
}