#version 330 core
		
layout(location = 0) in vec4 position;

uniform vec4 ourColor;
uniform float offset;

void main() {
	gl_Position = position;
}