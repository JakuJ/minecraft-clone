#include "views/renderers/Renderer.hpp"

Renderer::Renderer(const std::string &vName, const std::string &fName)
        : program(vName, fName), bufferedElements(0) {}

void Renderer::bufferData() {
    buffers->bufferData();
}

void Renderer::render() {
    program.use();
}
