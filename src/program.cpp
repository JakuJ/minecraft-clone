#include <iostream>
#include <fstream>
#include <vector>

#include "program.hpp"

unsigned int initShader(const char *path, int shaderType)
{
    char *source = nullptr;

    // Read shader source file
    std::ifstream file(path);
    if (file.is_open())
    {
        std::string content((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));

        source = &content.front();
        file.close();
    }
    else
    {
        std::cout << "Error reading file " << path << std::endl;
    }

    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    return shader;
}

Program::Program()
{
    this->vertexShader = initShader("shaders/vertex.vs", GL_VERTEX_SHADER);
    this->fragmentShader = initShader("shaders/fragment.fs", GL_FRAGMENT_SHADER);
    this->id = glCreateProgram();

    glAttachShader(this->id, this->vertexShader);
    glAttachShader(this->id, this->fragmentShader);
    glLinkProgram(this->id);

    int success;
    char infoLog[512];
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(this->id, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER_PROGRAM::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }
}

Program::~Program()
{
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
}

void Program::use() const
{
    glUseProgram(this->id);
}

void Program::setFloat(const std::string &name, float value) const
{
    int location = glGetUniformLocation(this->id, &name.front());
    glUniform1f(location, value);
}
