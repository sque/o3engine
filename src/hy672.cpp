
#include <iostream>

#include "GeneratorApp.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/simd_mat4.hpp>

int main(int argc, char ** argv) {
	GeneratorApp ap;

	ap.start();

	Matrix4 m1, m2, m3;
/*
	Timer & tm = Platform::getSingleton().getTimer();
	tm.reset();
	float s = tm.getMicrosecondsCPU();
	for(int i =0;i < 2000000;i++) {
		m3 = m1 * m2;
	}
	float e = tm.getMicrosecondsCPU();
	std::cout << "Took " << (e-s) << " mircroseconds\n";

	glm::mat4 gm3, gm2, gm1;
	s = tm.getMicrosecondsCPU();
	for(int i =0;i < 2000000;i++) {
		gm3 = gm1 * gm2;
	}
	e = tm.getMicrosecondsCPU();
	std::cout << "Took " << (e-s) << " mircroseconds\n";
*/
}
