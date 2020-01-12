#version 410 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aOffset;
layout (location = 3) in vec3 aTypeInfo;

uniform mat4 playerMVP;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;

mat3 rotateAxis(float x, float y, float times)
{
    float s = min(times, 2.0 - times);
    float oc = abs(times);
    float c = 1.0 - oc;

    return mat3(oc * x * x + c, oc * x * y, y * s,
                oc * x * y, oc * y * y + c, - x * s,
                - y * s, x * s, c);
}

void main()
{
    float type = aTypeInfo.z;

    float isX = 1 - step(2, type);
    float isY = 1 - isX;

    float minus = 1 - (step(1, type) - step(5, type));
    float rots = 1 + ((step(2, type) - step(4, type)) * (-2 * step(3, type) + 1));

    mat3 rotMat = rotateAxis(isX, isY, (-2 * minus + 1) * rots);

    fTexCoord = aTexCoord + aTypeInfo.xy;
    fPosition = rotMat * aPosition + aOffset;
    fNormal = rotMat * vec3(0, 0, -1);
    gl_Position = playerMVP * vec4(fPosition, 1.0);
}
