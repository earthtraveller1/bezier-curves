#include "window.hpp"
#include "graphics.hpp"

int main() {
    Window window;
    if (!window.is_okay) {
        return -1;
    }

    graphics::init(window);

    while (window.is_open()) {
        graphics::begin();

        graphics::draw_circle(100.0, 100.0, 50.0);

        graphics::end();
        window.update();
    }

    graphics::deinit();
}
