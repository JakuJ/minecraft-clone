#version 410 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 mvp;

out vec2 fTexCoord;
out vec3 fPosition;

void main()
{
    fTexCoord = aTexCoord;
    fPosition = aPosition;
    gl_Position = mvp * vec4(aPosition, 1.0);
}
