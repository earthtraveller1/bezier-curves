#version 430 core

out vec4 out_color;

in flat int is_circle;
in flat vec2 circle_center;
in flat float radius;

in vec2 position;

void main() {
    out_color = vec4(1.0, 1.0, 0.0, 1.0);

    if (is_circle != 0) {
        if (distance(circle_center, position) > radius) {
            discard;
        }
    }
}
