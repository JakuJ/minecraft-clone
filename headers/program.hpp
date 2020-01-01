#pragma once

#include <string>
#include "glad/glad.h"

// A simple context manager for the shader program
class Program
{
    static unsigned int loadShader(const std::string& path, int type);

private:
    unsigned int vertexShader;
    unsigned int fragmentShader;

public:
    unsigned int id;
    
    void use() const;
    
    void setUniform(const std::string &name, float value) const;
    void setUniform(const std::string &name, bool value) const;
    void setUniform(const std::string &name, int value) const;
    
    Program();
};