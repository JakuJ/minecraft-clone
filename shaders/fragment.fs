#version 330 core

in vec2 fTexCoord;

out vec4 FragColor;

uniform sampler2D dirt;

void main()
{
    vec3 color = texture(dirt, fTexCoord).xyz;
    FragColor = vec4(color, 1.0);
}
