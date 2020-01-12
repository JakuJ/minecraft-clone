#version 410 core

layout (location = 5) in vec3 aPosition;

// Common uniforms
uniform mat4 mvp;
uniform float time;
uniform vec3 sunPosition;

mat4 rotationZ(in float angle) {
    float s = sin(angle);
    float c = cos(angle);
    return mat4(
    c, -s, 0, 0,
    s, c, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1);
}

void main()
{
    vec4 rotated = rotationZ(-time) * vec4(aPosition, 1.0);
    vec3 pos = rotated.xyz + sunPosition;
    gl_Position = mvp * vec4(pos, 1.0);
}
