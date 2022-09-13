#version 460 core

#include "../include.glsl"

layout (location = 0) in vec3 vPos;

layout (std140, binding = 0) uniform CameraData
{
    mat4 view;
    mat4 projection;
    vec3 viewPos;
    vec4 otherDat;
} Camera;

void main()
{
    gl_Position = Camera.projection * Camera.view * vec4(vPos, 1.0);
}