#pragma once

#include <string>
#include "glad/glad.h"

struct Texture
{
    unsigned int id;
    Texture(const std::string& name, unsigned int target, bool flip = false);
};

struct CubeTexture
{
    unsigned int id;
    CubeTexture(const std::string& directory, unsigned int target, bool flip = false);
};