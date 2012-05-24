#version 330

#define LIGHT_POSITIONAL 0u
#define LIGHT_DIRECTIONAL 1u
#define LIGHT_SPOT 2u
#define LIGHT_TOTAL_MAX 10u
#extension GL_ARB_shading_language_420pack : enable

struct light_t {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
 	vec3 direction;
	float spot_cutoff;
	uint type;
};

layout(std140, binding = 1) uniform LightsUniform {
	uint TotalLights;
	light_t Lights[LIGHT_TOTAL_MAX];
};