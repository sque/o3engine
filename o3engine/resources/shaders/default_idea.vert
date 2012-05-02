#version 420
#include "library/scene_parameters.glslh"
#depend "library/phong.vert"

// Input attributes
layout(location=0) in vec4 aPosition;

uniform mat4 ModelMatrix;

out float depth;

void main() {
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * aPosition;
	depth = clamp((gl_Position.z - 5)/15, 0.0, 1.0);
}