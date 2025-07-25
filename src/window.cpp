#include <glad/glad.h>

#include "window.hpp"

Window::Window() {
    if (!glfwInit()) {
        std::cout << "[ERROR]: Failed to initialize GLFW.\n";
        return;
    }

    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const auto monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* video_mode = glfwGetVideoMode(monitor);

    int width = video_mode->width * 0.80;
    int height = video_mode->height * 0.80;

    std::string_view title = "Bezier Curves";

    m_window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (m_window == nullptr) {
        std::cout << "[ERROR]: Failed to create window.\n";
        return;
    }

    glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(this));

    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        (void)window;
        glViewport(0, 0, width, height);
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
        (void)mods;

        auto m_window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

        if (action == GLFW_PRESS) {
            m_window->m_button_just_pressed[button] = true;
        } else if (action == GLFW_RELEASE) {
            m_window->m_button_just_released[button] = true;
        }
    });

    is_okay = true;
}
