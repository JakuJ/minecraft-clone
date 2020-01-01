#pragma once

#include <string>
#include "glad/glad.h"

// A simple context manager for the shader program
class Program
{
private:
    unsigned int vertexShader;
    unsigned int fragmentShader;

public:
    unsigned int id;

    void use() const;
    void setFloat(const std::string &name, float value) const;

    Program();
    ~Program();
};