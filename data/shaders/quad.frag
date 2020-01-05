#version 330 core

out vec4 FragColor;

in vec2 fTexCoord;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform sampler2D cubes;

void main()
{
    vec4 texColor = texture(cubes, fTexCoord);
    FragColor = texColor;
}
