#include "window.hpp"

Window::Window(uint32_t width, uint32_t height, std::string_view title) {
    if (!glfwInit()) {
        std::cout << "[ERROR]: Failed to initialize GLFW.\n";
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (m_window == nullptr) {
        std::cout << "[ERROR]: Failed to create window.\n";
        return;
    }

    glfwMakeContextCurrent(m_window);

    is_okay = true;
}
