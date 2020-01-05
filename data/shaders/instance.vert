#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aOffset;

uniform mat4 mvp;

out vec2 fTexCoord;

void main()
{
    fTexCoord = vec2(aTexCoord.x, aTexCoord.y + aOffset.w);
    gl_Position = mvp * vec4(aPosition + aOffset.xyz, 1.0);
}
