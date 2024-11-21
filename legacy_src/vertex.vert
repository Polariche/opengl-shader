#version 330 core
layout(location = 0) in vec2 position;

uniform vec2 camera_position;
uniform float cur_time;

void main() {
	float c = cos(cur_time);
	float s = sin(cur_time);

	gl_Position = vec4(position - camera_position, 0, 1);
	gl_Position = vec4(gl_Position.x * c + gl_Position.y * s,
						gl_Position.x * -s + gl_Position.y * c,
						0, 1);
}