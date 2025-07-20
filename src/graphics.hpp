#pragma once

struct Vertex {
    glm::vec2 position;
    int is_circle;
    glm::vec2 center;
};

namespace graphics {
bool init(uint32_t screen_width, uint32_t screen_height);

void begin();

void draw_rectangle(float x, float y, float width, float height);

void draw_circle(float x, float y, float radius);

void end();

void deinit();
}
