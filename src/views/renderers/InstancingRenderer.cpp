#include <utils/Log.hpp>
#include "views/renderers/InstancingRenderer.hpp"
#include "models/Game.hpp"
#include "rendering/mesh.hpp"

InstancingRenderer::InstancingRenderer()
        : AsyncRenderer("data/shaders/instance.vert", "data/shaders/quad.frag"),
          texture("cubes", GL_TEXTURE0, "data/textures/blocks.png", true),
          bufferedInstances(0) {

    texture.bind(program);

    // Initial filling of the buffers
    std::vector<float> verts;
    verts.reserve(2 * 3 * 3);

    const float vs[]{0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0};

    const u_int ixs[]{0, 1, 2, 0, 2, 3};

    auto addVert = [&](u_int ix) {
        verts.push_back(vs[3 * ix] - 0.5);
        verts.push_back(vs[3 * ix + 1] - 0.5);
        verts.push_back(vs[3 * ix + 2] - 0.5);
    };

    for (auto &ix : ixs) {
        addVert(ix);
    }

    vertices.fill(verts);
    vertices.bufferData();
    bufferedElements = vertices.size();

    std::vector<float> coords;
    coords.reserve(2 * 3 * 2);

    const float du = 1.0 / static_cast<float>(Block::FACES);
    const float dv = 1.0 / static_cast<float>(Block::TYPES);

    const float uvs[] = {0, 0, du, 0, du, dv, 0, 0, du, dv, 0, dv};
    coords.insert(coords.end(), uvs, std::end(uvs));

    texCoords.fill(coords);
    texCoords.bufferData();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);

    Log::debug("Instancing renderer created");
}

void InstancingRenderer::renderSync() {
    texture.use();
    program.setUniform("mvp", Game::getInstance().player.getFPMatrix());

    // render to screen
    glClearColor(0.6, 0.8, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // NOLINT
    glDrawArraysInstanced(GL_TRIANGLES, 0, bufferedElements, bufferedInstances);
}

void InstancingRenderer::fillBuffersSync() {
    Game &game = Game::getInstance();
    auto &pos = game.player.position;

    ChunkSector cs = game.world.tree.getSurrounding(pos[0], pos[2], RENDERING_DISTANCE);
    InstanceMesh mesh = cs.getInstanceMesh();

    offsets.fill(mesh.offsets);
    infos.fill(mesh.typeInfos);
    Log::debug("InstancingRenderer buffers filled");
}

void InstancingRenderer::bufferData() {
    offsets.bufferData();
    infos.bufferData();
    bufferedInstances = infos.size();
}
