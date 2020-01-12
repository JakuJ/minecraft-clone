#pragma once

#include <views/View.hpp>
#include <controllers/InputController.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

class WindowView : public View {

    GLFWwindow *window;

public:
    WindowView(int, int) noexcept(false);

    ~WindowView() override;

    WindowView(const WindowView &) = delete;

    WindowView &operator=(const WindowView &) = delete;

    WindowView(WindowView &&) = delete;

    WindowView &operator=(WindowView &&) = delete;

    [[nodiscard]] GLFWwindow *getWindow() const;

    void mainLoop(Controller *controller);
};
