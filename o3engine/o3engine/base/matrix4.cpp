#include "./matrix4.hpp"
#include "./math.hpp"
#include <stdexcept>

namespace o3engine
{
	// Static values
	const Matrix4 Matrix4::IDENTITY =
		Matrix4(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
	const Matrix4 Matrix4::ZERO =
		Matrix4(0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0,
				0, 0, 0, 0);


	//! Get the inverse matrix
	bool Matrix4::inverse(Matrix4 & inverted, Real fTolerance) {

		throw std::runtime_error("Implementation taken from Matrix3 never tested");
		// Invert a 3x3 using cofactors.  This is about 8 times faster than
		// the Numerical Recipes code which uses Gaussian elimination.

		inverted[0][0] = m[1][1]*m[2][2] -
			m[1][2]*m[2][1];
		inverted[0][1] = m[0][2]*m[2][1] -
			m[0][1]*m[2][2];
		inverted[0][2] = m[0][1]*m[1][2] -
			m[0][2]*m[1][1];
		inverted[1][0] = m[1][2]*m[2][0] -
			m[1][0]*m[2][2];
		inverted[1][1] = m[0][0]*m[2][2] -
			m[0][2]*m[2][0];
		inverted[1][2] = m[0][2]*m[1][0] -
			m[0][0]*m[1][2];
		inverted[2][0] = m[1][0]*m[2][1] -
			m[1][1]*m[2][0];
		inverted[2][1] = m[0][1]*m[2][0] -
			m[0][0]*m[2][1];
		inverted[2][2] = m[0][0]*m[1][1] -
			m[0][1]*m[1][0];

		Real fDet =
			m[0][0]*inverted[0][0] +
			m[0][1]*inverted[1][0]+
			m[0][2]*inverted[2][0];

		if ( math::abs(fDet) <= fTolerance )
			return false;

		Real fInvDet = 1.0/fDet;
		for (size_t iRow = 0; iRow < 3; iRow++)
		{
			for (size_t iCol = 0; iCol < 3; iCol++)
				inverted[iRow][iCol] *= fInvDet;
		}

		return true;
	}

	Matrix4 Matrix4::operator*(const Matrix4 & Rm) const {
		Matrix4 mul;
		mul.m[0][0] = m[0][0] * Rm.m[0][0] + m[0][1] * Rm.m[1][0] + m[0][2] * Rm.m[2][0] + m[0][3] * Rm.m[3][0];
		mul.m[0][1] = m[0][0] * Rm.m[0][1] + m[0][1] * Rm.m[1][1] + m[0][2] * Rm.m[2][1] + m[0][3] * Rm.m[3][1];
		mul.m[0][2] = m[0][0] * Rm.m[0][2] + m[0][1] * Rm.m[1][2] + m[0][2] * Rm.m[2][2] + m[0][3] * Rm.m[3][2];
		mul.m[0][3] = m[0][0] * Rm.m[0][3] + m[0][1] * Rm.m[1][3] + m[0][2] * Rm.m[2][3] + m[0][3] * Rm.m[3][3];

		mul.m[1][0] = m[1][0] * Rm.m[0][0] + m[1][1] * Rm.m[1][0] + m[1][2] * Rm.m[2][0] + m[1][3] * Rm.m[3][0];
		mul.m[1][1] = m[1][0] * Rm.m[0][1] + m[1][1] * Rm.m[1][1] + m[1][2] * Rm.m[2][1] + m[1][3] * Rm.m[3][1];
		mul.m[1][2] = m[1][0] * Rm.m[0][2] + m[1][1] * Rm.m[1][2] + m[1][2] * Rm.m[2][2] + m[1][3] * Rm.m[3][2];
		mul.m[1][3] = m[1][0] * Rm.m[0][3] + m[1][1] * Rm.m[1][3] + m[1][2] * Rm.m[2][3] + m[1][3] * Rm.m[3][3];

		mul.m[2][0] = m[2][0] * Rm.m[0][0] + m[2][1] * Rm.m[1][0] + m[2][2] * Rm.m[2][0] + m[2][3] * Rm.m[3][0];
		mul.m[2][1] = m[2][0] * Rm.m[0][1] + m[2][1] * Rm.m[1][1] + m[2][2] * Rm.m[2][1] + m[2][3] * Rm.m[3][1];
		mul.m[2][2] = m[2][0] * Rm.m[0][2] + m[2][1] * Rm.m[1][2] + m[2][2] * Rm.m[2][2] + m[2][3] * Rm.m[3][2];
		mul.m[2][3] = m[2][0] * Rm.m[0][3] + m[2][1] * Rm.m[1][3] + m[2][2] * Rm.m[2][3] + m[2][3] * Rm.m[3][3];

		mul.m[3][0] = m[3][0] * Rm.m[0][0] + m[3][1] * Rm.m[1][0] + m[3][2] * Rm.m[2][0] + m[3][3] * Rm.m[3][0];
		mul.m[3][1] = m[3][0] * Rm.m[0][1] + m[3][1] * Rm.m[1][1] + m[3][2] * Rm.m[2][1] + m[3][3] * Rm.m[3][1];
		mul.m[3][2] = m[3][0] * Rm.m[0][2] + m[3][1] * Rm.m[1][2] + m[3][2] * Rm.m[2][2] + m[3][3] * Rm.m[3][2];
		mul.m[3][3] = m[3][0] * Rm.m[0][3] + m[3][1] * Rm.m[1][3] + m[3][2] * Rm.m[2][3] + m[3][3] * Rm.m[3][3];

		return mul;
	}

	Matrix4 perspective(Real fovy, Real aspect, Real znear, Real zfar) {
		Real f = 1/tan(fovy / 2);
		Real dp = znear - zfar;

		return Matrix4(
			f / aspect, 0, 0, 0,
			0, f, 0, 0,
			0, 0, (zfar+znear)/dp, (2*zfar*znear)/dp,
			0, 0,  -1, 0);
	}

	Matrix4 ortho(Real left, Real right, Real bottom, Real top, Real near, Real far) {
		Real width = right -left;
		Real height = top - bottom;
		Real depth = far - near;
		return Matrix4(
			2/width, 0, 0, -((right+left)/width),
			0, 2/height, 0, -((top+bottom)/height),
			0, 0, -2/depth, -((far+near)/depth),
			0, 0, 0, 1
		);
	}
}
