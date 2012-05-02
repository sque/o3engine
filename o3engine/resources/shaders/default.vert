#version 420
layout(location=0) in vec4 aPosition;

layout(std140, binding=0) uniform SceneMatrices {
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	mat4 ProjectionViewMatrix;
};

uniform mat4 ModelMatrix;

out float depth;

void main() {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPosition;
	depth = clamp((gl_Position.z - 5)/15, 0.0, 1.0);
});