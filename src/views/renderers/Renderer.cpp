#include <models/Game.hpp>
#include <glm/gtx/vec_swizzle.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "views/renderers/Renderer.hpp"

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

Renderer::Renderer(const std::string &vName, const std::string &fName)
        : program(vName, fName), bufferedElements(0) {}

void Renderer::render() {
    program.use();

    auto time = static_cast<float>(glfwGetTime()) / 5.0f;

    program.setUniform("time", time);
    program.setUniform("playerMVP", Game::getInstance().player.getFPMatrix());
    program.setUniform("cameraPosition", Game::getInstance().player.position);
    program.setUniform("underwater", static_cast<int>(Game::getInstance().player.isUnderwater));

    auto rotMatrix = glm::rotate(glm::identity<glm::mat4>(), time, glm::vec3(0, 0, 1));
    program.setUniform("sunPosition", glm::xyz(rotMatrix * glm::vec4(1, 0, 0, 0)));
}
