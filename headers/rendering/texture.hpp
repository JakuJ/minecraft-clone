#pragma once

#include <string>
#include "glad/glad.h"

struct Texture
{
    unsigned int id;
    unsigned int target;

    Texture(unsigned int target);

    virtual void use() const = 0;
};

struct Texture2D : public Texture
{
    Texture2D(const std::string &name, unsigned int target, bool flip = false);

    void use() const override;
};

struct CubeTexture : public Texture
{
    CubeTexture(const std::string &directory, unsigned int target, bool flip = false);

    void use() const override;
};