#include "views/renderers/QuadRendererT.hpp"
#include "models/Game.hpp"
#include "rendering/mesh.hpp"
#include <memory>

QuadRendererT::QuadRendererT()
    : AsyncRenderer("data/shaders/quad.vert", "data/shaders/quad.frag"), texture("data/textures/blocks.png", GL_TEXTURE0, true)
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
    
    buffers = std::unique_ptr<BufferSet>((BufferSet *)&ibs);

    ibs.addVBO((VBOProxy *)new VBO<float, 3>(0)); // vertices
    ibs.addVBO((VBOProxy *)new VBO<float, 2>(1)); // texCoords

    fillBuffers();
}

void QuadRendererT::renderSync()
{
    program.use();
    texture.use();

    program.setUniform("mvp", Game::getInstance().player.camera->getViewMatrix());

    glDrawElements(GL_TRIANGLES, bufferedElements, GL_UNSIGNED_INT, (GLvoid *)0);
}

void QuadRendererT::fillBuffersSync()
{
    Game &game = Game::getInstance();
    auto pos = game.player.position;

    ChunkSector cs = game.world.tree.getSurrounding(pos[0], pos[2], RENDERING_DISTANCE);
    QuadMesh mesh = cs.getQuadMesh();

    ((VBO<float, 3> *)ibs[0])->append(mesh.vertices);
    ((VBO<float, 2> *)ibs[1])->append(mesh.texCoords);

    ibs.ebo.append(mesh.indices);
}