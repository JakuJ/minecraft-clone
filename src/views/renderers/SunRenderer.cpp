#include <models/Game.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "views/renderers/SunRenderer.hpp"

SunRenderer::SunRenderer() : Renderer("data/shaders/sun.vert", "data/shaders/sun.frag") {
    fillBuffers();
    bufferData();
}

void SunRenderer::bufferData() {
    vertices.bufferData();
    bufferedElements = vertices.size();
}

void SunRenderer::render() {
    Renderer::render();

    auto mvp = glm::infinitePerspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f);
    mvp *= glm::lookAt(glm::vec3(0, 0, 0), Game::getInstance().player.getFront(), glm::vec3(0, 1, 0));

    program.setUniform("mvp", mvp);

    glDrawArrays(GL_TRIANGLE_FAN, 0, bufferedElements);
    glClear(GL_DEPTH_BUFFER_BIT);  // NOLINT
}

void SunRenderer::fillBuffers() {
    const float vs[] = {0, 5, -5,
                        0, -5, -5,
                        0, -5, 5,
                        0, 5, 5};

    std::vector<float> verts;

    auto addVert = [&](int ix) {
        verts.push_back(vs[3 * ix]);
        verts.push_back(vs[3 * ix + 1]);
        verts.push_back(vs[3 * ix + 2]);
    };

    for (int i : {3, 2, 1, 0}) {
        addVert(i);
    }

    vertices.fill(verts);
}
