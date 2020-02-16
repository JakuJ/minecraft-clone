#version 410 core

#define water_color vec3(0.19140625, 0.250980392, 0.701960784)

in vec3 fPosition;
out vec4 FragColor;

// Common uniforms
uniform float time;
uniform vec3 sunPosition;
uniform mat4 mvp;
uniform bool underwater;

uniform vec3 cameraPosition;

const vec3 skyColor = vec3(0.2, 0.4, 0.8);
const vec3 duskColor = vec3(1, 0.3, 0.23);

vec3 getSkyAndSun(vec3 skyBlockCoord, vec3 sunV)
{
    float lightness = max(0.0, 0.5 + sunV.y);

    float atmosphereDensity = pow(1.0 - skyBlockCoord.y, 2.0);
    float scatter = 1.0 - clamp(lightness, 0.0, 1.0);

    vec3 scatterColor = mix(vec3(1.0), duskColor, scatter);

    vec3 skyDusk = mix(skyColor, scatterColor, atmosphereDensity / 1.3);

    // SUN

    float sun = dot(skyBlockCoord, sunV);
    sun = pow(max(0.0, sun), mix(50, 80, lightness));// sun size

    float glow = sun;

    sun = pow(sun, 100.0) * 100;
    sun = clamp(sun, 0.0, 1.0);

    glow = pow(glow, 6.0 * lightness);
    glow = clamp(glow, 0.0, 1.0) * lightness;

    return lightness * skyDusk + scatterColor * (sun + glow);
}

void main()
{
    vec3 sky = getSkyAndSun(normalize(fPosition), sunPosition);

    float a = 0.3;
    vec3 color = underwater ? a * sky + (1 - a) * water_color : sky;

    FragColor = vec4(color, 1.0);
}
