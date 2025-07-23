#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct WindowDimensions {
    int width;
    int height;
};

class Window {
public:
    bool is_okay = false;

    Window();

    Window(Window&) = delete;
    Window& operator=(Window&) = delete;

    inline bool is_open() const {
        return !glfwWindowShouldClose(m_window);
    }

    inline bool is_button_down(int button) const {
        return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
    }

    inline glm::vec2 get_mouse_pos() const {
        double width, height;
        glfwGetCursorPos(m_window, &width, &height);
        return glm::vec2{width, height};
    }

    inline WindowDimensions get_window_size() const {
        WindowDimensions dims{};
        glfwGetWindowSize(m_window, &dims.width, &dims.height);
        return dims;
    }

    inline void update() const {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    ~Window() {
        glfwDestroyWindow(m_window);
    }

private:
    GLFWwindow* m_window;
};
