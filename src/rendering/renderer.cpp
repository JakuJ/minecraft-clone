#include "rendering/renderer.hpp"

QuadRenderer::QuadRenderer()
    : texture("data/textures/blocks.png", GL_TEXTURE0, true), program("data/shaders/quad.vert", "data/shaders/quad.frag")
{
    // Create a Vertex Array Object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Assign a texture sampler
    program.setUniform("cubes", 0);

    // Set texturing parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void QuadRenderer::render()
{
    program.use();
    texture.use();

    glDrawElements(GL_TRIANGLES, buffered_size, GL_UNSIGNED_INT, 0);
}

void QuadRenderer::setMesh(const Mesh &mesh)
{
    buffers.clear();
    mesh.buffer(buffers);
}

void QuadRenderer::bufferMesh()
{
    buffers.bufferData();
    buffered_size = buffers.size();
}