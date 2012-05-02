#version 330

in float depth;
out vec4 outColor;
void main() {
	outColor = vec4(1, 1, 1, 1)*depth;
}