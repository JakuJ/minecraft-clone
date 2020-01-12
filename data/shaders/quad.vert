#version 410 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

// Common uniforms
uniform mat4 playerMVP;

out vec3 fPosition;
out vec3 fNormal;
out vec2 fTexCoord;

void main()
{
    fTexCoord = aTexCoord;
    fPosition = aPosition;
    fNormal = aNormal;
    gl_Position = playerMVP * vec4(aPosition, 1.0);
}
