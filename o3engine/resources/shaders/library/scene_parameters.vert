#version 330
#ifndef SCENE_PARAMETERS_VERT_INCLUDED
#define SCENE_PARAMETERS_VERT_INCLUDED

layout(std140) uniform SceneMatrices {
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	mat4 ProjectionViewMatrix;
	vec4 CameraPositionWs;
};

uniform mat4 ModelMatrix;

#endif