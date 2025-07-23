#include "window.hpp"
#include "graphics.hpp"

int main() {
    Window window(1920, 1080, "Bezier Curves");
    if (!window.is_okay) {
        return -1;
    }

    graphics::init(1920.0f, 1080.0f);

    while (window.is_open()) {
        graphics::begin();

        graphics::draw_circle(100.0, 100.0, 50.0);

        graphics::end();
        window.update();
    }

    graphics::deinit();
}
