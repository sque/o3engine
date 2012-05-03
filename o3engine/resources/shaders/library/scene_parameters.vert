#version 330
#ifndef SCENE_PARAMS_GLSLH_INCLUDED
#define SCENE_PARAMS_GLSLH_INCLUDED

layout(std140) uniform SceneMatrices {
	mat4 ProjectionMatrix;
	mat4 ViewMatrix;
	mat4 ProjectionViewMatrix;
	vec4 CameraPositionWs;
};

#endif