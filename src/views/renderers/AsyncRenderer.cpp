#include "views/renderers/AsyncRenderer.hpp"

AsyncRenderer::AsyncRenderer(const std::string &vName, const std::string &fName) : Renderer(vName, fName) {}

void AsyncRenderer::fillBuffers()
{
    std::thread thread([this]() {
        std::lock_guard<std::mutex> guard(dataMutex);

        fillBuffersSync();

        dataLoaded = true;
    });

    thread.detach();
}

void AsyncRenderer::render()
{
    Renderer::render();
    
    if (dataLoaded)
    {
        bufferData();
        dataLoaded = false;
    }
    
    renderSync();
}