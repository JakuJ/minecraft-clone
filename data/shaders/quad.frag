#version 410 core

#define fogColor vec3(0.662745098, 0.776470588, 0.937254902)
#define renderingDistance 96
#define falloff 0.01

out vec4 FragColor;

in vec2 fTexCoord;
in vec3 fPosition;

uniform vec3 cameraPosition;
uniform sampler2D cubes;

void main()
{
    vec4 texColor = texture(cubes, fTexCoord);
    float distance = length(fPosition - cameraPosition);
    float fromHorizon = max(0.0, distance - renderingDistance);
    float fogLevel = clamp(falloff * fromHorizon, 0.0, 1.0);
    FragColor = vec4(mix(texColor.xyz, fogColor, fogLevel), texColor.w);
}
