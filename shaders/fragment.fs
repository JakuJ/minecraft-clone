#version 330 core

in vec3 fColor;
in vec2 fTexCoord;

out vec4 FragColor;

uniform float time;

uniform sampler2D box;
uniform sampler2D face;

void main()
{
    vec3 color = mix(texture(box, fTexCoord).xyz, texture(face, fTexCoord).xyz, 0.2);
    FragColor = vec4(color, 1.0);
}
