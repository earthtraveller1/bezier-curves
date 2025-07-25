#pragma once

struct Vertex {
    glm::vec2 position;
    int is_circle;
    glm::vec2 center;
};

class Window;

namespace graphics {
bool init(const Window& window);

void begin();

void draw_rectangle(float x, float y, float width, float height);

void draw_circle(float x, float y, float radius);

void draw_line(float x1, float y1, float x2, float y2, float line_width);

void end();

void deinit();
}
