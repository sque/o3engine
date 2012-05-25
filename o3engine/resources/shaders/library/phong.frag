#version 330

#depend "library/light.vert"

vec4 phong_lit(void);

#ifdef COMPILE_OBJECT

in vec3 vtEyeVecWs;
in vec3 vtLightDirWs[LIGHT_TOTAL_MAX];
in vec3 vtNormalWs;

vec4 compute_light(light_t light, vec3 N, vec3 L, vec3 E, float att_factor, vec4 mat_emission, vec4 mat_ambient, vec4 mat_diffuse, vec4 mat_specular, float mat_shininess) {
	vec4 color = mat_emission + mat_ambient * light.ambient;
	float lambertTerm = dot(N, L);

	if (lambertTerm > 0) {
		color += light.diffuse * mat_diffuse * lambertTerm * att_factor;
				
		vec3 R = reflect(-L, N);
		float spec_factor = pow( max(dot(R, E), 0.0), mat_shininess );
		color += light.specular * mat_specular * spec_factor * att_factor;
	}
	return color;
}

vec4 phong_lit(void) {
	light_t l;
	l.ambient = vec4(0.2, 0.2, 0.2, 1);
	l.diffuse = vec4(0.8, 0.4, 0.4 , 1);
	l.specular = vec4(1, 1, 1, 1);
	vec3 N = normalize(vtNormalWs);
	vec3 E = normalize(vtEyeVecWs);
	vec4 outColor;
	for(uint i = 0u;i < TotalLights;i++) {
		vec3 L = normalize(vtLightDirWs[i]);
		outColor += compute_light(Lights[0], N, L, E, 1, vec4(0,0,0,1), vec4(0.2, 0.2, 0.2, 1), vec4(1, 1, 1, 1), vec4(1, 1, 1, 1), 50);
	}
	return outColor;
}

#endif
