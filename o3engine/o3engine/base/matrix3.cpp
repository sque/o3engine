#include "./matrix3.hpp"
#include "./math.hpp"

namespace o3engine
{
	// Static values
	const Matrix3 Matrix3::IDENTITY =
		Matrix3(1, 0, 0,
				0, 1, 0,
				0, 0, 1);
	const Matrix3 Matrix3::ZERO =
		Matrix3(0, 0, 0,
				0, 0, 0,
				0, 0, 0);


	//! Get the inverse matrix
	bool Matrix3::inverse(Matrix3 & inverted, Real fTolerance)
	{
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

	Matrix3 Matrix3::operator*(const Matrix3 & Rm) const
	{   Matrix3 mul;
		mul.m[0][0] = m[0][0] * Rm.m[0][0] + m[0][1] * Rm.m[1][0] + m[0][2] * Rm.m[2][0];
		mul.m[0][1] = m[0][0] * Rm.m[0][1] + m[0][1] * Rm.m[1][1] + m[0][2] * Rm.m[2][1];
		mul.m[0][2] = m[0][0] * Rm.m[0][2] + m[0][1] * Rm.m[1][2] + m[0][2] * Rm.m[2][2];

		mul.m[1][0] = m[1][0] * Rm.m[0][0] + m[1][1] * Rm.m[1][0] + m[1][2] * Rm.m[2][0];
		mul.m[1][1] = m[1][0] * Rm.m[0][1] + m[1][1] * Rm.m[1][1] + m[1][2] * Rm.m[2][1];
		mul.m[1][2] = m[1][0] * Rm.m[0][2] + m[1][1] * Rm.m[1][2] + m[1][2] * Rm.m[2][2];

		mul.m[2][0] = m[2][0] * Rm.m[0][0] + m[2][1] * Rm.m[1][0] + m[2][2] * Rm.m[2][0];
		mul.m[2][1] = m[2][0] * Rm.m[0][1] + m[2][1] * Rm.m[1][1] + m[2][2] * Rm.m[2][1];
		mul.m[2][2] = m[2][0] * Rm.m[0][2] + m[2][1] * Rm.m[1][2] + m[2][2] * Rm.m[2][2];

		return mul;
	}
}
