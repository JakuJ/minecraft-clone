#include <iostream>
#include <utility>
#include <vector>
#include "rendering/texture.hpp"
#include "stb/stb_image.h"
#include "glad/glad.h"

Texture::Texture(std::string name, int target) : name(std::move(name)), target(target) {}

void Texture::bind(const Program &program) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    program.setUniform(name, target);
}

Texture2D::Texture2D(const std::string &name, int target, const std::string &path, bool flip)
        : Texture(name, target) {
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
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

void Texture2D::use() const {
    glActiveTexture(target);
    glBindTexture(GL_TEXTURE_2D, id);
}

CubeTexture::CubeTexture(const std::string &name, int target, const std::string &directory, bool flip)
        : Texture(name, target) {

    stbi_set_flip_vertically_on_load(flip);

    std::string side = directory + "/side.png";
    std::string top = directory + "/top.png";
    std::string bottom = directory + "/bottom.png";

    std::vector<std::string> faces{side, side, top, bottom, side, side};

    glGenTextures(1, &id);
    glActiveTexture(target);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    for (size_t i = 0; i < faces.size(); i++) {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0,
                         nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }
}

void CubeTexture::use() const {
    glActiveTexture(target);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}
