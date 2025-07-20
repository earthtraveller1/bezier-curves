#pragma once

struct Vertex {
    glm::vec2 position;
};

namespace graphics {
bool init();

void begin();

void end();

void deinit();
}
