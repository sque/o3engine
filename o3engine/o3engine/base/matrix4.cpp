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
	Matrix4 Matrix4::inverse() const{

		Real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
		Real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
		Real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
		Real m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

		Real v0 = m20 * m31 - m21 * m30;
		Real v1 = m20 * m32 - m22 * m30;
		Real v2 = m20 * m33 - m23 * m30;
		Real v3 = m21 * m32 - m22 * m31;
		Real v4 = m21 * m33 - m23 * m31;
		Real v5 = m22 * m33 - m23 * m32;

		Real t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
		Real t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
		Real t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
		Real t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

		Real invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

		Real d00 = t00 * invDet;
		Real d10 = t10 * invDet;
		Real d20 = t20 * invDet;
		Real d30 = t30 * invDet;

		Real d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Real d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Real d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Real d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m10 * m31 - m11 * m30;
		v1 = m10 * m32 - m12 * m30;
		v2 = m10 * m33 - m13 * m30;
		v3 = m11 * m32 - m12 * m31;
		v4 = m11 * m33 - m13 * m31;
		v5 = m12 * m33 - m13 * m32;

		Real d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Real d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Real d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Real d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		v0 = m21 * m10 - m20 * m11;
		v1 = m22 * m10 - m20 * m12;
		v2 = m23 * m10 - m20 * m13;
		v3 = m22 * m11 - m21 * m12;
		v4 = m23 * m11 - m21 * m13;
		v5 = m23 * m12 - m22 * m13;

		Real d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
		Real d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
		Real d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
		Real d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

		return Matrix4(
			d00, d01, d02, d03,
			d10, d11, d12, d13,
			d20, d21, d22, d23,
			d30, d31, d32, d33);
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

	Matrix4 perspective(Angle fovy, Real aspect, Real znear, Real zfar) {
		Real f = 1/tan(fovy.getRadian() / 2);
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
