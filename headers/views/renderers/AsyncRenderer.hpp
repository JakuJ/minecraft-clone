#pragma once

#include <atomic>
#include <functional>
#include <string>
#include <mutex>
#include <thread>
#include "views/renderers/Renderer.hpp"

class AsyncRenderer : public Renderer {
    std::atomic<bool> dataLoaded{false};
    std::mutex dataMutex;

public:
    AsyncRenderer(const std::string &vName, const std::string &fName);

    void fillBuffers() final;

    virtual void fillBuffersSync() = 0;

    void render() final;

    virtual void renderSync() = 0;
};
