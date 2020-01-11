#version 410 core

layout (location = 4) in vec3 aPosition;

uniform mat4 mv;

out vec3 fPosition;

void main()
{
    fPosition = aPosition;
    gl_Position = mv * vec4(fPosition, 1.0);
}
