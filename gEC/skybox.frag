#version 460 core

#extension GL_ARB_bindless_texture : enable

layout(location = 1) uniform uvec2 albedo;

in vec3 TexCoord;

out vec4 FragColor;

void main()
{
    FragColor = vec4(texture(samplerCube(albedo), TexCoord).rgb, 1);
    FragColor.rgb = pow(FragColor.rgb, vec3(1 / 2.2));
}