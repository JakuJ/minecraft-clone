#version 330 core

out vec4 FragColor;

uniform float time;

void main()
{
    FragColor = vec4(clamp(sin(time), 0.0, 1.0), 0.5, 0.2, 1.0);
}
