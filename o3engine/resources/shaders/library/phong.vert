#version 330

#depend "library/scene_parameters.vert"
#depend "library/attributes.vert"
#depend "library/light.vert"

void phong_lit(void);

#ifdef COMPILE_OBJECT

out vec3 vtEyeVecWs;
out vec3 vtLightDirWs[LIGHT_TOTAL_MAX];
out vec3 vtNormalWs;

void phong_lit(void) {
	
	vec4 pWs = vec4(ModelMatrix * aPositionOs);	// Point in World Space
	vtEyeVecWs = CameraPositionWs.xyz - pWs.xyz;
	vtNormalWs = (inverse(transpose(ModelMatrix)) * aNormalOs).xyz;
	for(uint i = 0u;i < TotalLights;i++) {
		vtLightDirWs[i] = Lights[i].position - pWs.xyz;
	}
			
}

#endif
