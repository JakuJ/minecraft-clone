#version 330 core

in vec3 fTexCoord;

out vec4 FragColor;

uniform samplerCube dirt;

void main()
{
    vec3 color = texture(dirt, fTexCoord).xyz;
    FragColor = vec4(color, 1.0);
}
