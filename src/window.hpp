#pragma once

#define GLFW_INCLUDE_NONE
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

    inline bool is_button_down(int button) const {
        return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
    }

    inline glm::vec2 get_mouse_pos() const {
        int width, height;
        glfwGetWindowSize(m_window, &width, &height);
        return glm::vec2{width, height};
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
