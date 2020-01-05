#version 410 core

#define M_PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aOffset;
layout (location = 3) in vec3 aTypeInfo;

uniform mat4 mvp;

out vec2 fTexCoord;

mat3 rotateAxis(float x, float y, float times)
{
    float s = min(times, 2 - times);
    float c = 1 - abs(times);
    float oc = 1.0 - c;

    return mat3(oc * x * x + c, oc * x * y, y * s,
                oc * x * y, oc * y * y + c, - x * s,
                - y * s, x * s, c);
}

float type = aTypeInfo.z;

void main()
{   
    float isX = 1 - step(2, type);
    float isY = 1 - isX;

    float minus = 1 - (step(1, type) - step(5, type));
    float rots = 1 + ((step(2, type) - step(4, type)) * (-2 * step(3, type) + 1));

    float final_rots = (-2 * minus + 1) * rots;

    vec3 face = rotateAxis(isX, isY, final_rots) * aPosition;

    fTexCoord = aTexCoord + aTypeInfo.xy;
    gl_Position = mvp * vec4(face.xyz + aOffset, 1.0);
}
