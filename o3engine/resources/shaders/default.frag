#version 330

#depend "library/phong.frag"

out vec4 outColor;

void main() {
	outColor = phong_lit();
}