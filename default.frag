#version 460 core

#extension GL_ARB_bindless_texture : enable

layout(location = 1) uniform uvec2 albedo;

in vec3 FragPos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(texture(sampler2D(albedo), FragPos.zy).rgb, 1);
    FragColor.rgb = pow(FragColor.rgb, vec3(1 / 2.2));
}