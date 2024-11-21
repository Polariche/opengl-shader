#version 330 core
out vec4 color;

uniform vec4 obj_color;
uniform float cur_time;

void main() {
	color = (cos(cur_time)/2+0.5) * obj_color;
}