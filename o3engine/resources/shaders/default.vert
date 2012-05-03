#version 330

#depend "library/scene_parameters.vert"
#depend "library/phong.vert"

layout(location=0) in vec4 aPositionOs;

uniform mat4 ModelMatrix;

out float depth;

void main() {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPositionOs;
	phong_lit();
	depth = clamp((gl_Position.z - 5)/15, 0.0, 1.0);
};