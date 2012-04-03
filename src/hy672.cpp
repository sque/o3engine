
#include <iostream>

#include "GeneratorApp.hpp"


int main(int argc, char ** argv) {
	GeneratorApp ap;

	ap.start();
/*
	Matrix3 m1, m2, m3;

	Timer & tm = Platform::getSingleton().getTimer();
	tm.reset();
	float s = tm.getMicrosecondsCPU();
	for(int i =0;i < 200000000;i++) {
		m3 == m1;
	}
	float e = tm.getMicrosecondsCPU();
	std::cout << "Took " << (e-s) << " mircroseconds\n";
	*/
}
