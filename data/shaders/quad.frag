#version 410 core

#define fogColor vec3(0.462745098, 0.768627451, 0.890196078)
#define skyColor vec3(0.474509804, 0.698039216, 0.952941176)
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
    FragColor = vec4(mix(texColor.xyz, skyColor, fogLevel), texColor.w);
}
