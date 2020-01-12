#version 410 core

#define fogColor vec3(0.662745098, 0.776470588, 0.937254902)
#define renderingDistance 96
#define falloff 0.1

out vec4 FragColor;

in vec2 fTexCoord;
in vec3 fPosition;

// Common uniforms
uniform float time;
uniform vec3 sunPosition;

uniform vec3 cameraPosition;
uniform sampler2D cubes;

void main()
{
    vec4 texColor = texture(cubes, fTexCoord);
    float distance = length(fPosition - cameraPosition);
    float fromHorizon = max(0.0, distance - renderingDistance);
    float fogLevel = clamp(falloff * fromHorizon, 0.0, 1.0);
    vec3 distantFogColor = fogColor * 0.5 * (1 + sin(time));

    vec3 color = mix(texColor.xyz, distantFogColor, fogLevel);
    FragColor = vec4(color, texColor.w);
}
