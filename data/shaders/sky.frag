#version 410 core

in vec3 fPosition;
out vec4 FragColor;

// Common uniforms
uniform float time;
uniform vec3 sunPosition;
uniform mat4 mvp;

uniform vec3 cameraPosition;

const vec3 skyColor = vec3(0.2, 0.4, 0.8);
const vec3 duskColor = vec3(1, 0.3, 0.23);
const vec3 nightSkyColor = vec3(0);

vec3 getSky(vec3 skyBlockCoord, vec3 sunV)
{
    float lightness = max(0.0, dot(vec3(0, 1, 0), sunV));

    float atmosphereDensity = pow(1.0 - skyBlockCoord.y, 2.0);
    float scatter = max(0.0, sunV.y);
    scatter = 1.0 - clamp(scatter, 0.0, 1.0);

    vec3 scatterColor = mix(vec3(1.0), duskColor, scatter);

    vec3 skyDusk = mix(skyColor, scatterColor, atmosphereDensity / 1.3);
    return lightness * skyDusk;
}

vec3 getSun(vec3 skyCoords, vec3 cameraSun) {
    float height = max(0.0, cameraSun.y);

    float sun = dot(skyCoords, cameraSun);
    sun = pow(max(0.0, sun), 100.0);

    float glow = sun;

    sun = pow(sun, 100.0) * 100;
    sun = clamp(sun, 0.0, 1.0);

    glow = pow(glow, 6.0 * height);
    glow = clamp(glow, 0.0, 1.0);

    sun *= pow(height * height, 1.0 / 1.65);

    glow *= sqrt(dot(height, height));

    return vec3(1.0, 0.6, 0.05) * (sun + glow);
}

void main()
{
    vec3 uv = normalize(fPosition);

    vec3 sky = getSky(uv, sunPosition);
    vec3 sun = getSun(uv, sunPosition);

    FragColor = vec4(sun + sky, 1.0);
}
