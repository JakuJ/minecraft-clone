#include <models/Game.hpp>
#include <glm/gtx/vec_swizzle.hpp>
#include "views/renderers/SkyBoxRenderer.hpp"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#define invsqrt3 0.577350269

SkyBoxRenderer::SkyBoxRenderer() : Renderer("data/shaders/sky.vert", "data/shaders/sky.frag") {
}

void SkyBoxRenderer::bufferData() {
    vertices.bufferData();
    bufferedElements = vertices.size();
}

void SkyBoxRenderer::render() {
    Renderer::render();

    glm::vec4 at = glm::rotate(glm::identity<glm::mat4>(),
                               glm::radians(static_cast<float>(Game::getInstance().player.headPitch)),
                               glm::vec3(1, 0, 0)) * glm::vec4(0, 0, -1, 0);

    auto mv = glm::infinitePerspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f);
    mv *= glm::lookAt(glm::vec3(0.0), glm::xyz(at), glm::vec3(0, 1, 0));

    program.setUniform("mv", mv);
    program.setUniform("cameraPosition", Game::getInstance().player.position);

    fillBuffers();
    bufferData();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, bufferedElements);
    glClear(GL_DEPTH_BUFFER_BIT);  // NOLINT
}

void SkyBoxRenderer::fillBuffers() {
    const float vs[] = {-1, -1, -1,
                        1, -1, -1,
                        1, 1, -1,
                        -1, 1, -1,
                        -1, -1, 1,
                        1, -1, 1,
                        1, 1, 1,
                        -1, 1, 1};

    std::vector<float> verts;
    std::vector<float> cols;

    auto addVert = [&](int ix) {
        verts.push_back(vs[3 * ix]);
        verts.push_back(vs[3 * ix + 1] * invsqrt3);
        verts.push_back(vs[3 * ix + 2]);
    };


    for (int i : {5, 4, 1, 0, 2, 3, 6, 7}) {
        addVert(i);
    }

    vertices.fill(verts);
}
