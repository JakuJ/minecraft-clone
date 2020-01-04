#include "rendering/renderer.hpp"

Renderer::Renderer(const std::string &vPath, const std::string &fPath) : texture("data/textures/blocks.png", GL_TEXTURE0, true), program(vPath, fPath)
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

QuadRenderer::QuadRenderer() : Renderer("data/shaders/quad.vert", "data/shaders/quad.frag") {}

void QuadRenderer::render()
{
    program.use();
    texture.use();

    glDrawElements(GL_TRIANGLES, buffered_size, GL_UNSIGNED_INT, 0);
}

void QuadRenderer::preloadMesh(const QuadMesh &mesh)
{
    buffers.clear();
    buffers.bufferMesh(mesh);
}

void QuadRenderer::bufferMesh()
{
    buffers.bufferData();
    buffered_size = buffers.size();
}

InstanceRenderer::InstanceRenderer() : Renderer("data/shaders/instance.vert", "data/shaders/instance.frag") {}

void InstanceRenderer::render()
{
    program.use();
    texture.use();

    glDrawElementsInstanced(GL_TRIANGLE_STRIP, buffered_size, GL_UNSIGNED_INT, 0, buffered_instances);
}

void InstanceRenderer::preloadMesh(const InstanceMesh &mesh)
{
    buffers.clear();
    buffers.bufferMesh(mesh);
}

void InstanceRenderer::bufferMesh()
{
    buffers.bufferData();
    buffered_size = buffers.size();
    buffered_instances = buffers.instances();
}