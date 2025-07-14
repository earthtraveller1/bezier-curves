#include "window.hpp"

int main() {
    Window window(1920, 1080, "Bezier Curves");
    if (!window.is_okay) {
        return -1;
    }

    while (window.is_open()) {
        window.update();
    }
}
