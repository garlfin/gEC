#version 460 core

layout (location = 0) in vec3 vPos;

layout (std140, binding = 0) uniform CameraData
{
    mat4 view;
    mat4 projection;
    vec3 viewPos;
    vec4 otherDat;
} CameraData;

void main()
{
    gl_Position = CameraData.projection * CameraData.view * vec4(vPos, 1.0);
}