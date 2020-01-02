#version 330 core

out vec4 FragColor;

in vec3 fTexCoord;

uniform samplerCube cubeMap;

void main()
{
    vec4 color = texture(cubeMap, fTexCoord);
    FragColor = vec4(color.xyz, 1.0);
}
