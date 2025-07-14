#pragma once

#include <GLFW/glfw3.h>

class Window {
public:
    bool is_okay = false;

    Window(uint32_t width, uint32_t height, std::string_view title);

    Window(Window&) = delete;
    Window& operator=(Window&) = delete;

    inline bool is_open() const {
        return !glfwWindowShouldClose(m_window);
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
