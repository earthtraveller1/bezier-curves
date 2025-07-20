#include "window.hpp"
#include "graphics.hpp"

int main() {
    Window window(1920, 1080, "Bezier Curves");
    if (!window.is_okay) {
        return -1;
    }

    graphics::init();

    while (window.is_open()) {
        graphics::begin();

        graphics::draw_rectangle(-0.5, -0.5, 1.0, 1.0);

        graphics::end();

        window.update();
    }

    graphics::deinit();
}
