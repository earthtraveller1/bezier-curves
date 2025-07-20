#include <cassert>
#include <fstream>

#include <glad/glad.h>

#include "graphics.hpp"
#include "GLFW/glfw3.h"

namespace {
GLuint shader_program;
GLuint vao;
GLuint vbo;
GLuint ebo;

std::optional<GLuint> make_shader(std::string_view path, GLenum type) {
    std::ifstream file(path.data());
    if (!file) {
        std::cerr << "[ERROR]: Cannot open " << path << '\n';
        return {};
    }

    std::string source;

    do {
        std::string line;
        std::getline(file, line);
        source += (line + '\n');
    } while (!file.eof());

    GLuint shader = glCreateShader(type);
    std::array sources{ source.data() };
    glShaderSource(shader, sources.size(), sources.data(), nullptr);
    glCompileShader(shader);

    GLint compile_status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

    if (compile_status == 0) {
        GLint log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        GLchar* log = new GLchar[log_length];
        glGetShaderInfoLog(shader, log_length, nullptr, log);

        std::cerr << "[ERROR]: Failed to compile shader:\n" << log << "\n\n";

        delete[] log;
        glDeleteShader(shader);
        return {};
    }

    return shader;
}
}

bool graphics::init() {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "[EROR]: Failed to load OpenGL functions.\n";
        return false;
    }

    const auto vertex_shader = make_shader("shaders/main.vert", GL_VERTEX_SHADER);
    if (!vertex_shader.has_value()) return false;
    const auto fragment_shader = make_shader("shaders/main.frag", GL_FRAGMENT_SHADER);
    if (!fragment_shader.has_value()) return false;

    shader_program = glCreateProgram(); 
    glAttachShader(shader_program, *vertex_shader);
    glAttachShader(shader_program, *fragment_shader);
    glLinkProgram(shader_program);

    GLint link_status = 0;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);

    if (link_status == 0) {
        GLint log_length = 0;
        glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_length);

        GLchar* log = new GLchar[log_length];
        glGetProgramInfoLog(shader_program, log_length, nullptr, log);

        std::cerr << "[ERROR]: Failed to link shader program:\n" << log << "\n\n";

        delete[] log;
        glDeleteShader(*vertex_shader);
        glDeleteShader(*fragment_shader);
        glDeleteProgram(shader_program);

        return false;
    }

    glDeleteShader(*vertex_shader);
    glDeleteShader(*fragment_shader);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    return true;
}
