#include <memory>
#include "views/renderers/QuadRenderer.hpp"
#include "models/Game.hpp"
#include "rendering/mesh.hpp"

QuadRenderer::QuadRenderer()
        : AsyncRenderer("data/shaders/quad.vert", "data/shaders/quad.frag"),
          texture("cubes", GL_TEXTURE0, "data/textures/blocks.png", true) {
    texture.bind(program);

    buffers = std::make_unique<IndexedBufferSet>();

    buffers->addVBO(static_cast<VBOProxy *>(new VBO<float, 3>(0)));  // vertices
    buffers->addVBO(static_cast<VBOProxy *>(new VBO<float, 2>(1)));  // texCoords

    fillBuffers();
}

void QuadRenderer::renderSync() {
    texture.use();
    program.setUniform("mvp", Game::getInstance().player.getFPMatrix());
    glDrawElements(GL_TRIANGLES, bufferedElements, GL_UNSIGNED_INT, reinterpret_cast<GLvoid *>(0));
}

void QuadRenderer::fillBuffersSync() {
    Game &game = Game::getInstance();
    auto &pos = game.player.position;

    ChunkSector cs = game.world.tree.getSurrounding(pos[0], pos[2], RENDERING_DISTANCE);
    QuadMesh mesh = cs.getQuadMesh();

    dynamic_cast<VBO<float, 3> *>((*buffers)[0])->append(mesh.vertices);
    dynamic_cast<VBO<float, 2> *>((*buffers)[1])->append(mesh.texCoords);

    static_cast<IndexedBufferSet *>(buffers.get())->ebo.append(mesh.indices); // NOLINT
}

void QuadRenderer::bufferData() {
    Renderer::bufferData();
    bufferedElements = static_cast<IndexedBufferSet *>(buffers.get())->ebo.size(); // NOLINT
}
