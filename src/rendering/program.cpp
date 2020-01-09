#include <iostream>
#include <fstream>
#include <vector>
#include <utility/Log.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "rendering/program.hpp"

Program::Program(const std::string &vertPath, const std::string &fragPath) {
    vertexShader = Program::loadShader(vertPath, GL_VERTEX_SHADER);
    fragmentShader = Program::loadShader(fragPath, GL_FRAGMENT_SHADER);
    id = glCreateProgram();

    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
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
    glUseProgram(id);
}

void Program::setUniform(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Program::setUniform(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
}

void Program::setUniform(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Program::setUniform(const std::string &name, const glm::mat4 &value) const {
    auto location = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}
