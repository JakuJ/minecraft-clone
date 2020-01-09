#pragma once

#include <string>
#include "rendering/program.hpp"

struct Texture {
    unsigned int id{};
    std::string name;
    int target;

    Texture(std::string name, int target);

    virtual ~Texture() = default;

    void bind(const Program &);

    virtual void use() const = 0;
};

struct Texture2D : public Texture {
    Texture2D(const std::string &name, int target, const std::string &path, bool flip = false);

    void use() const final;
};

struct CubeTexture : public Texture {
    CubeTexture(const std::string &name, int target, const std::string &directory, bool flip = false);

    void use() const final;
};
