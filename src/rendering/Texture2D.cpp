#include <utility>
#include "glad/glad.h"
#include "utils/Log.hpp"
#include "rendering/Texture2D.hpp"
#include "stb/stb_image.h"

Texture2D::Texture2D(std::string name, int target, const std::string &path, bool flip)
        : name(std::move(name)), target(target) {
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(flip);

    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glGenTextures(1, &id);
        glActiveTexture(target);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE,
                     data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        Log::warn("Failed to load texture: ", path);
    }

    stbi_image_free(data);
}

void Texture2D::bind(const Program &program) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    program.setUniform(name, target);
}

void Texture2D::use() const {
    glActiveTexture(target);
    glBindTexture(GL_TEXTURE_2D, id);
}
