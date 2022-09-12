#version 460 core

#extension ARB_bindless_texture : require

layout(location = 1) uniform uvec2 albedo;

out vec4 FragColor;

void main()
{
    FragColor = vec4(texture(sampler2D(albedo), gl_FragCoord.xy / vec2(1280, 720)).rgb, 1);
    FragColor.rgb = pow(FragColor.rgb, vec3(1 / 2.2));
}