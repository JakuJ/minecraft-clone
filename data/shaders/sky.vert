#version 410 core

layout (location = 4) in vec3 aPosition;

// Common uniforms
uniform mat4 mvp;

out vec3 fPosition;

void main()
{
    fPosition = aPosition;
    gl_Position = mvp * vec4(fPosition, 1.0);
}
