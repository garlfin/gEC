layout (std140, binding = 0) uniform CameraData
{
    mat4 view;
    mat4 projection;
    vec3 viewPos;
    vec4 otherDat;
} Camera;

layout(std140, binding = 1) uniform ObjData
{
    mat4[100] Model;
    vec4[25] Transparency;
} Object;