#version 330

#depend "library/scene_parameters.vert"
#depend "library/phong.vert"

layout(location=0) in vec4 aPositionOs;

out float depth;

void main() {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPositionOs;
	phong_lit();
};