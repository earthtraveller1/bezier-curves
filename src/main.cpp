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

        graphics::draw_circle(100.0, 100.0, 10.0);
        graphics::draw_circle(150.0, 100.0, 10.0);
        graphics::draw_circle(200.0, 100.0, 10.0);
        graphics::draw_circle(250.0, 100.0, 10.0);
        graphics::draw_circle(300.0, 100.0, 10.0);

        graphics::draw_line(100.0, 100.0, 300.0, 100.0, 5.0);

        graphics::end();
        window.update();
    }

    graphics::deinit();
}
