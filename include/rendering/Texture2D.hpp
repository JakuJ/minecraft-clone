#pragma once

#include <string>
#include "rendering/Program.hpp"

/// An abstraction over an OpenGL 2D texture object.
class Texture2D {
    unsigned int id{};
    int target;
    std::string name;

public:
    /// Create a new instance of the Texture2D class.
    /// \param name Name of the texture object in the shader.
    /// \param target Texture target.
    /// \param path Path to the image file.
    /// \param flip A flag indicating whether to flip the image on load.
    Texture2D(std::string name, int target, const std::string &path, bool flip = false);

    /// Bind texture to a shader program.
    void bind(const Program &);

    /// Set this texture as active.
    void use() const;
};
