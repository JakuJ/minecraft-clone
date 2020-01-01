#include <iostream>
#include <vector>
#include "stb/stb_image.h"
#include "texture.hpp"

Texture::Texture(const std::string &path, unsigned int target, bool flip)
{
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(flip);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glGenTextures(1, &id);
        glActiveTexture(target);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

CubeTexture::CubeTexture(const std::string &directory, unsigned int target, bool flip)
{

    stbi_set_flip_vertically_on_load(flip);

    std::string side = directory + "/side.jpg";
    std::string top = directory + "/top.jpg";
    std::string bottom = directory + "/bottom.jpg";

    std::vector<std::string> faces{side, side, top, bottom, side, side};

    glGenTextures(1, &id);
    glActiveTexture(target);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    for (size_t i = 0; i < faces.size(); i++)
    {
        int width, height, nrChannels;
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }

    
}
