#pragma once

#include <string>
#include "glad/glad.h"
#include "glm/glm.hpp"

// A simple context manager for the shader program
class Program {
    static unsigned int loadShader(const std::string &path, int type);

private:
    unsigned int Id;
    unsigned int vertexShader;
    unsigned int fragmentShader;

public:
    void use() const;

    [[nodiscard]] unsigned int getId() const;

    void setUniform(const std::string &name, float value) const;

    void setUniform(const std::string &name, bool value) const;

    void setUniform(const std::string &name, int value) const;

    void setUniform(const std::string &name, const glm::vec3 &value) const;

    void setUniform(const std::string &name, const glm::mat4 &value) const;

    Program(const std::string &, const std::string &);

    Program(const Program &) = delete;

    Program &operator=(const Program &) = delete;
};
