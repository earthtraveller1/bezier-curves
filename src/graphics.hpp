#pragma once

struct Vertex {
    glm::vec2 position;
};

namespace graphics {
bool init();

void begin();

void draw_rectangle(float x, float y, float width, float height);

void end();

void deinit();
}
