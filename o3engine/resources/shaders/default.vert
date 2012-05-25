#version 330

#depend "library/scene_parameters.vert"
#depend "library/phong.vert"

void main() {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPositionOs;
	phong_lit();
};