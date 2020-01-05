#version 410 core

#define M_PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aOffset;
layout (location = 3) in vec3 aTypeInfo;

uniform mat4 mvp;

out vec2 fTexCoord;

mat4 rotate(vec3 axis, float times)
{
    float angle = times * 0.5 * M_PI;
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

float type = aTypeInfo.z;

void main()
{   
    float isX = 1 - step(2, type);
    float isY = 1 - isX;

    float minus = 1 - (step(1, type) - step(5, type));
    float rots = 1 + ((step(2, type) - step(4, type)) * (-2 * step(3, type) + 1));

    vec4 face = rotate(vec3(isX, isY, 0), (-2 * minus + 1) * rots) * vec4(aPosition, 1.0);

    fTexCoord = aTexCoord + aTypeInfo.xy;
    gl_Position = mvp * vec4(face.xyz + aOffset, 1.0);
}
