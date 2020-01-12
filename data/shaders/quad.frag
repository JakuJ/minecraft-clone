#version 410 core

out vec4 FragColor;

in vec3 fPosition;
in vec3 fNormal;
in vec2 fTexCoord;

// Common uniforms
uniform float time;
uniform vec3 sunPosition;

uniform vec3 cameraPosition;
uniform sampler2D cubes;

void main()
{
    float lightness = clamp(0.0, 1.0, 0.5 + sunPosition.y);

    vec4 texColor = texture(cubes, fTexCoord);

    float ambient = 0.3 + lightness * 0.4;
    float lambertian = 0.3 * lightness * max(0.0, dot(normalize(sunPosition), normalize(fNormal)));

    vec3 color = (ambient + lambertian) * texColor.xyz;

    FragColor = vec4(color, texColor.w);
}
