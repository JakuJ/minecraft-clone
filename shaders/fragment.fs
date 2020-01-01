#version 330 core

in vec3 fColor;

out vec4 FragColor;

uniform float time;

void main()
{
    FragColor = vec4(fColor, 1.0);
}
