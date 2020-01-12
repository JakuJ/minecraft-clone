#include <models/Game.hpp>
#include "views/renderers/SkyBoxRenderer.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

SkyBoxRenderer::SkyBoxRenderer() : Renderer("data/shaders/sky.vert", "data/shaders/sky.frag") {
    fillBuffers();
    bufferData();
}

void SkyBoxRenderer::bufferData() {
    vertices.bufferData();
    bufferedElements = vertices.size();
}

void SkyBoxRenderer::render() {
    Renderer::render();

    auto mvp = glm::infinitePerspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f);
    mvp *= glm::lookAt(glm::vec3(0), Game::getInstance().player.getFront(), glm::vec3(0, 1, 0));

    program.setUniform("mvp", mvp);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, bufferedElements);
    glClear(GL_DEPTH_BUFFER_BIT);  // NOLINT
}

void SkyBoxRenderer::fillBuffers() {
    const float vs[] = {1.0, 1.0, 1.0,
                        -1.0f, 1.0, 1.0,
                        1.0, 1.0, -1.0f,
                        -1.0f, 1.0, -1.0f,
                        1.0, -1.0f, 1.0,
                        -1.0f, -1.0f, 1.0,
                        -1.0f, -1.0f, -1.0f,
                        1.0, -1.0f, -1.0f};

    std::vector<float> verts;

    auto addVert = [&](int ix) {
        verts.push_back(vs[3 * ix]);
        verts.push_back(vs[3 * ix + 1] * 0.577350269);  // 1 / sqrt(3)
        verts.push_back(vs[3 * ix + 2]);
    };

    for (int i : {3, 2, 6, 7, 4, 2, 0, 3, 1, 6, 5, 4, 1, 0}) {
        addVert(i);
    }

    vertices.fill(verts);
}
