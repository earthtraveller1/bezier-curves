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

    glfwMakeContextCurrent(m_window);

    glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
        (void)window;
        glViewport(0, 0, width, height);
    });

    is_okay = true;
}
