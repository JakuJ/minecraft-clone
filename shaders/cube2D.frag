#version 330 core

out vec4 FragColor;

in vec2 fTexCoord;

uniform sampler2D face;

void main()
{
    vec4 color = texture(face, fTexCoord);
    FragColor = vec4(color.xyz, 1.0);
}
