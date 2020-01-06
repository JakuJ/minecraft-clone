#pragma once

#include "views/renderers/RendererT.hpp"
#include <atomic>
#include <functional>
#include <thread>

class AsyncRenderer : public RendererT
{
    std::atomic<bool> dataLoaded;
    std::mutex dataMutex;

public:
    AsyncRenderer(const std::string &vName, const std::string &fName);

    void fillBuffers() final;
    virtual void fillBuffersSync() = 0;
    
    void render() final;
    virtual void renderSync() = 0;
};
