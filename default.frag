#version 460 core

#extension ARB_bindless_texture : enable

uniform uvec2 albedo;

out vec4 FragColor;

void main()
{
    FragColor = vec4(texture(sampler2D(albedo), gl_FragCoord.xy));
}