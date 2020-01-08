#include "views/renderers/QuadRenderer.hpp"
#include "models/Game.hpp"
#include "rendering/mesh.hpp"
#include <memory>

QuadRenderer::QuadRenderer()
        : AsyncRenderer("data/shaders/quad.vert", "data/shaders/quad.frag"),
          texture("cubes", GL_TEXTURE0, "data/textures/blocks.png", true) {
    texture.bind(program);
    buffers = std::unique_ptr<BufferSet>((BufferSet *) &ibs);

    ibs.addVBO((VBOProxy *) new VBO<float, 3>(0)); // vertices
    ibs.addVBO((VBOProxy *) new VBO<float, 2>(1)); // texCoords

    fillBuffers();
}

void QuadRenderer::renderSync() {
    texture.use();
    program.setUniform("mvp", Game::getInstance().player.getFPMatrix());
    glDrawElements(GL_TRIANGLES, bufferedElements, GL_UNSIGNED_INT, (GLvoid *) 0);
}

void QuadRenderer::fillBuffersSync() {
    Game &game = Game::getInstance();
    auto &pos = game.player.position;

    ChunkSector cs = game.world.tree.getSurrounding(pos[0], pos[2], RENDERING_DISTANCE);
    QuadMesh mesh = cs.getQuadMesh();

    ((VBO<float, 3> *) ibs[0])->append(mesh.vertices);
    ((VBO<float, 2> *) ibs[1])->append(mesh.texCoords);

    ibs.ebo.append(mesh.indices);
}

void QuadRenderer::bufferData() {
    Renderer::bufferData();
    bufferedElements = ibs.ebo.size();
}
