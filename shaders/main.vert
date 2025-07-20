#version 430 core

layout (location = 0) in vec2 in_position;
layout (location = 1) in int in_is_circle;
layout (location = 2) in vec2 in_circle_center;

uniform mat4 projection;

out flat int is_circle;
out flat vec2 circle_center;
out flat float radius;

out vec2 position;

void main() {
    gl_Position = projection * vec4(in_position, 0.0, 1.0);
    is_circle = in_is_circle;
    circle_center = in_circle_center;
    radius = abs(circle_center.x - in_position.x);

    position = in_position;
}
