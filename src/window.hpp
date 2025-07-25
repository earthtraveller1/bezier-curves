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

    inline bool is_button_just_pressed(int button) {
        if (m_button_just_pressed[button]) {
            m_button_just_pressed[button] = false;
            return true;
        }

        return false;
    }

    inline bool is_button_just_released(int button) {
        if (m_button_just_released[button]) {
            m_button_just_released[button] = false;
            return true;
        }

        return false;
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

    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> m_button_just_pressed;
    std::array<bool, GLFW_MOUSE_BUTTON_LAST + 1> m_button_just_released;
};
