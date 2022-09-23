#version 460 core

#include "../include.glsl"

layout (location = 0) in vec3 vPos;

out vec3 TexCoord;

void main()
{
    TexCoord = vPos;
    gl_Position = (Camera.projection * Camera.view * vec4(vPos, 1.0)).xyww;
}