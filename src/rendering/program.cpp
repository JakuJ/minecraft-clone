#include <iostream>
#include <fstream>
#include <vector>
#include "utils/Log.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "rendering/program.hpp"

Program::Program(const std::string &vertPath, const std::string &fragPath) {
    vertexShader = Program::loadShader(vertPath, GL_VERTEX_SHADER);
    fragmentShader = Program::loadShader(fragPath, GL_FRAGMENT_SHADER);
    Id = glCreateProgram();

    glAttachShader(Id, vertexShader);
    glAttachShader(Id, fragmentShader);
    glLinkProgram(Id);

    int success;
    char infoLog[512];
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(Id, 512, nullptr, infoLog);
        Log::error("Shader program failed to link");
        Log::error(infoLog);
        throw std::runtime_error("Shader program exception");
    }

    // No longer needed after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

unsigned int Program::loadShader(const std::string &path, int type) {
    std::string content;
    try {
        // Read shader source file
        std::ifstream file(path);

        content.assign((std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
        file.close();
    }
    catch (std::ifstream::failure &e) {
        Log::error("Shader file read unsuccessfully");
        Log::error(e.what());
        throw std::runtime_error("Shader program exception");
    }

    const char *source = content.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        Log::error("Shader program failed to compile");
        Log::error(infoLog);
        throw std::runtime_error("Shader exception");
    }

    return shader;
}

void Program::use() const {
    glUseProgram(Id);
}

void Program::setUniform(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(Id, name.c_str()), value);
}

void Program::setUniform(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(Id, name.c_str()), value);
}

void Program::setUniform(const std::string &name, const glm::vec3 &value) const {
    auto location = glGetUniformLocation(Id, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Program::setUniform(const std::string &name, const glm::mat4 &value) const {
    auto location = glGetUniformLocation(Id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
