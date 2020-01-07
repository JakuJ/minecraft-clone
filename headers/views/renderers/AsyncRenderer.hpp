#pragma once

#include "views/renderers/Renderer.hpp"
#include <atomic>
#include <functional>
#include <mutex>
#include <thread>

class AsyncRenderer : public Renderer
{
    std::atomic<bool> dataLoaded;
    std::mutex dataMutex;

public:
    AsyncRenderer(const std::string &vName, const std::string &fName);

    void fillBuffers() final;
    virtual void fillBuffersSync() = 0;

    virtual void render() final;
    virtual void renderSync() = 0;
};
