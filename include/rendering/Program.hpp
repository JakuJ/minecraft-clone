#pragma once

#include <string>
#include "glm/glm.hpp"

/// A simple context manager for a shader program
class Program {
    static unsigned int loadShader(const std::string &path, int type);

    unsigned int Id;
    unsigned int vertexShader;
    unsigned int fragmentShader;

public:
    void use() const;

    void setUniform(const std::string &name, float value) const;

    void setUniform(const std::string &name, int value) const;

    void setUniform(const std::string &name, const glm::vec3 &value) const;

    void setUniform(const std::string &name, const glm::mat4 &value) const;

    Program(const std::string &, const std::string &);

    Program(const Program &) = delete;

    Program &operator=(const Program &) = delete;
};
