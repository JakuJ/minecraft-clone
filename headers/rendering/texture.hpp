#pragma once

#include "rendering/program.hpp"
#include <string>

struct Texture
{
    unsigned int id;
    std::string name;
    int target;

    Texture(const std::string& name, int target);
    virtual ~Texture() {};

    void bind(const Program &);
    
    virtual void use() const = 0;
};

struct Texture2D : public Texture
{
    Texture2D(const std::string &name, int target, const std::string& path, bool flip = false);

    void use() const final;
};

struct CubeTexture : public Texture
{
    CubeTexture(const std::string &name, int target, const std::string &directory, bool flip = false);

    void use() const final;
};