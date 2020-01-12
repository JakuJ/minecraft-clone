#version 410 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 aNormal;

// Common uniforms
uniform mat4 playerMVP;

out vec2 fTexCoord;
out vec3 fPosition;

void main()
{
    fTexCoord = aTexCoord;
    fPosition = aPosition;
    gl_Position = playerMVP * vec4(aPosition, 1.0);
}
