#version 330

vec4 phong_lit(void);

#ifdef MODULE_MAIN

vec4 phong_lit(void) {
	return vec4(1,0,0,0);
}

#endif