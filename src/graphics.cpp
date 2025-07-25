#include <cassert>
#include <fstream>

#include <glad/glad.h>

#include "graphics.hpp"
#include "window.hpp"

namespace {
GLuint shader_program;
GLuint vao;
GLuint vbo;
GLuint ebo;

std::vector<Vertex> vertices;
std::vector<uint32_t> elements;

const Window* g_window = nullptr;

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

bool graphics::init(const Window& window) {
    g_window = &window;
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
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_INT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, is_circle)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, center)));
    glEnableVertexAttribArray(2);

    return true;
}

void graphics::begin() {
    vertices.clear();
    elements.clear();
}

void graphics::draw_rectangle(float x, float y, float width, float height) {
    const auto is_circle = false;
    const glm::vec2 circle_center{};
    std::array rect_vertices {
        Vertex { { x, y }, is_circle, circle_center},
        Vertex { { x + width, y }, is_circle, circle_center},
        Vertex { { x + width, y + height }, is_circle, circle_center},
        Vertex { { x, y + height }, is_circle, circle_center},
    };

    std::array<uint32_t, 6> rect_elements {
        0, 1, 2, 0, 3, 2
    };

    vertices.insert(vertices.end(), rect_vertices.begin(), rect_vertices.end());
    elements.insert(elements.end(), rect_elements.begin(), rect_elements.end());
}

void graphics::draw_circle(float x, float y, float radius) {
    const auto width = radius * 2;
    const auto height = radius * 2;
    glm::vec2 circle_center{x + width/2, y + height/2};

    const auto is_circle = true;
    std::array rect_vertices {
        Vertex { { x, y }, is_circle, circle_center},
        Vertex { { x + width, y }, is_circle, circle_center},
        Vertex { { x + width, y + height }, is_circle, circle_center},
        Vertex { { x, y + height }, is_circle, circle_center},
    };

    std::array<uint32_t, 6> rect_elements {
        0, 1, 2, 0, 3, 2
    };

    vertices.insert(vertices.end(), rect_vertices.begin(), rect_vertices.end());
    elements.insert(elements.end(), rect_elements.begin(), rect_elements.end());
}

void graphics::draw_line(float x1, float y1, float x2, float y2, float line_width) {
    // m = y/x
    // y = mx
    // x = m/y
    // y/x = -x_1/y_1
    // y = -x_1
    // x = y_1

    glm::vec2 a{x1, y1};
    glm::vec2 b{x2, y2};

    const auto line_vector = b - a;
    const auto offset_vector = glm::normalize(glm::vec2{line_vector.y, -line_vector.x}) * line_width;

    const auto vert_0 = a + offset_vector;
    const auto vert_1 = a - offset_vector;
    const auto vert_2 = b - offset_vector;
    const auto vert_3 = b + offset_vector;

    bool is_circle = true;
    std::array line_vertices {
        Vertex { vert_0, is_circle, {}},
        Vertex { vert_1, is_circle, {}},
        Vertex { vert_2, is_circle, {}},
        Vertex { vert_3, is_circle, {}},
    };

    std::array<uint32_t, 6> rect_elements {
        0, 1, 2, 0, 3, 2
    };

    vertices.insert(vertices.end(), line_vertices.begin(), line_vertices.end());
    elements.insert(elements.end(), rect_elements.begin(), rect_elements.end());
}

void graphics::end() {
    const auto [screen_width, screen_height] = g_window->get_window_size();
    const auto aspect_ratio = (float)screen_width / (float)screen_height;
    const auto width = 1000.0f;
    const auto height = width / aspect_ratio;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);

    const auto projection = glm::ortho(0.0f, width, height, 0.0f);
    const auto location = glGetUniformLocation(shader_program, "projection");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * elements.size(), elements.data(), GL_DYNAMIC_DRAW);

    glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

void graphics::deinit() {
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteProgram(shader_program);
}
