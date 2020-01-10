#include "utils/Log.hpp"
#include "views/renderers/QuadRenderer.hpp"
#include "models/Game.hpp"
#include "rendering/mesh.hpp"

QuadRenderer::QuadRenderer()
        : AsyncRenderer("data/shaders/quad.vert", "data/shaders/quad.frag"),
          texture("cubes", GL_TEXTURE0, "data/textures/blocks.png", true) {

    texture.bind(program);
}

void QuadRenderer::renderSync() {
    texture.use();
    program.setUniform("mvp", Game::getInstance().player.getFPMatrix());

    // render to screen
    glClearColor(0.6, 0.8, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // NOLINT
    glDrawElements(GL_TRIANGLES, bufferedElements, GL_UNSIGNED_INT, reinterpret_cast<GLvoid *>(0));
}

void QuadRenderer::fillBuffersSync() {
    Game &game = Game::getInstance();
    auto &pos = game.player.position;

    ChunkSector cs = game.world.tree.getSurrounding(pos[0], pos[2], RENDERING_DISTANCE);
    QuadMesh mesh = cs.getQuadMesh();

    vertices.fill(mesh.vertices);
    texCoords.fill(mesh.texCoords);
    indices.fill(mesh.indices);

    Log::debug("QuadRenderer buffers filled");
}

void QuadRenderer::bufferData() {
    vertices.bufferData();
    texCoords.bufferData();
    indices.bufferData();
    bufferedElements = indices.size();
}
