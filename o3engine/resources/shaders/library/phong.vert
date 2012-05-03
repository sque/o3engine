#version 330

#depend "library/scene_parameters.vert"

void phong_lit(void);

//////////////////////////////////////////////////
// MODULE SOURCE
#ifdef COMPILING_MODULE

layout(location=0) in vec4 aPositionOs;

out vec3 vtEyeVecWs;

void phong_lit(void) {
	
	vec4 Pw = vec4(ModelMatrix * aPositionOs);
	vt_EyeVecWs = CameraPositionWs.xyz - Pw.xyz;
	
	/*vt_LightDirWs[0] = light[0].position - Pw.xyz;
	att_factor[0] = get_attenuation(light[0], Pw.xyz);
	vt_LightDirWs[1] = light[1].position - Pw.xyz;	
	att_factor[1] = get_attenuation(light[1], Pw.xyz);*/
}
#endif
/*
layout(location=0) in vec4 aPosition;
layout(location=2) in vec3 texCoord;

out vec3 vt_LightDirWs[MAX_LIGHTS], vt_EyeVecWs;
out float att_factor[MAX_LIGHTS];

uniform mat4 ModelViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform vec3 CameraPositionWs;

float get_attenuation(light_t light, vec3 vtPw) {
	float d = distance(vtPw, light.position);
	return 1/(light.const_att_factor +  (light.lin_att_factor  * d) + (light.quad_att_factor * d * d));
}

void phong_lit(void) {
	
	vec4 Pw = vec4(ModelMatrix * in_Position);
	vt_EyeVecWs = CameraPositionWs.xyz - Pw.xyz;
	
	vt_LightDirWs[0] = light[0].position - Pw.xyz;
	att_factor[0] = get_attenuation(light[0], Pw.xyz);
	vt_LightDirWs[1] = light[1].position - Pw.xyz;	
	att_factor[1] = get_attenuation(light[1], Pw.xyz);
}

*/