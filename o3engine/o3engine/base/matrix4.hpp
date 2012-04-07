#ifndef O3ENGINE_MATRIX4_HPP_INCLUDED
#define O3ENGINE_MATRIX4_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector4.hpp"
#include "./matrix3.hpp"
#include "./angle.hpp"

namespace o3engine {
	//! [R3] Class for handling orthogonal matrices 4x4
	/**
	 * @par Class Characteristics
	 * Matrix4 is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 *
	 * @ingroup base_group
	 */
	class Matrix4 {
	private:
		Real m[4][4]; // Matrix 4x4

	public:
		//! Identity matrix
		const static Matrix4 IDENTITY;

		//! Zero matrix
		const static Matrix4 ZERO;

		//! Constructor does <b>NOT</b> initialize values for performance
		Matrix4() = default;

		//! Constructor from C array
		inline Matrix4(const Real * rv) {
			memcpy(m, rv, sizeof(m));
		}

		//! Constructor from Matrix3
		inline Matrix4(const Matrix3 & m3) {
			m[0][0] = m3[0][0];
			m[0][1] = m3[0][1];
			m[0][2] = m3[0][2];
			m[0][3] = 0;

			m[1][0] = m3[1][0];
			m[1][1] = m3[1][1];
			m[1][2] = m3[1][2];
			m[1][3] = 0;

			m[2][0] = m3[2][0];
			m[2][1] = m3[2][1];
			m[2][2] = m3[2][2];
			m[2][3] = 0;

			m[3][0] = 0;
			m[3][1] = 0;
			m[3][2] = 0;
			m[3][3] = 1;
		}


		//! Construct from values
		inline Matrix4(
				Real m00, Real m01, Real m02, Real m03,
				Real m10, Real m11, Real m12, Real m13,
				Real m20, Real m21, Real m22, Real m23,
				Real m30, Real m31, Real m32, Real m33) {
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[0][3] = m03;

			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[1][3] = m13;

			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
			m[2][3] = m23;

			m[3][0] = m30;
			m[3][1] = m31;
			m[3][2] = m32;
			m[3][3] = m33;
		}

		//! Copy constructor
		inline Matrix4(const Matrix4 & r) {
			memcpy(m, r.m, sizeof(m));
		}

		//! Get a specific column in a Vector4 object (no range check)
		inline Vector4 getColumn(int col) const {
			return Vector4(m[0][col], m[1][col], m[2][col], m[3][col]);
		}

		//! Get a specific row in a Vector4 object (no range check)
		inline Vector4 getRow(int row) const {
			return Vector4(m[row][0], m[row][1], m[row][2], m[row][4]);
		}

		//! Set a specific column by a Vector4 object
		inline Matrix4 & setColumn(int col, const Vector4 & rv) {
			m[0][col] = rv.x;
			m[1][col] = rv.y;
			m[2][col] = rv.z;
			m[3][col] = rv.z;
			return *this;
		}

		//! Set a specific row by a Vector4 object
		inline Matrix4 & setRow(int row, const Vector4 & rv) {
			m[row][0] = rv.x;
			m[row][1] = rv.y;
			m[row][2] = rv.z;
			m[row][3] = rv.z;
			return *this;
		}

		//! @name Operators (textual or algebraically)
		//! @{

		//! Check for equality
		inline bool operator==(const Matrix4 & r) const {
			return memcmp(m, r.m, sizeof(m)) == 0;
		}

		//! Check if are different
		inline bool operator!=(const Matrix4 & r) const {
			return !operator==(r);
		}

		//! Self-Substract matrix
		inline Matrix4 & operator-=(const Matrix4 & r) {
			m[0][0] -= r.m[0][0];
			m[0][1] -= r.m[0][1];
			m[0][2] -= r.m[0][2];
			m[0][3] -= r.m[0][3];

			m[1][0] -= r.m[1][0];
			m[1][1] -= r.m[1][1];
			m[1][2] -= r.m[1][2];
			m[1][3] -= r.m[1][3];

			m[2][0] -= r.m[2][0];
			m[2][1] -= r.m[2][1];
			m[2][2] -= r.m[2][2];
			m[2][3] -= r.m[2][3];

			m[3][0] -= r.m[3][0];
			m[3][1] -= r.m[3][1];
			m[3][2] -= r.m[3][2];
			m[3][3] -= r.m[3][3];
			return *this;
		}

		//! Member access, allows use of construct mat[r][c] (no range check)
		inline const Real* operator[](size_t iRow) const {
			return (Real*) m[iRow];
		}

		//! Member access, allows use of construct mat[r][c] (no range check)
		inline Real* operator[](size_t iRow) {
			return (Real*) m[iRow];
		}

		//! Substract matrix
		inline Matrix4 operator-(const Matrix4 & r) const {
			Matrix4 tmp_m4(*this);
			tmp_m4 -= r;
			return tmp_m4;
		}

		//! Self-Add matrix
		inline Matrix4 & operator+=(const Matrix4 & r) {
			m[0][0] += r.m[0][0];
			m[0][1] += r.m[0][1];
			m[0][2] += r.m[0][2];
			m[0][3] += r.m[0][3];

			m[1][0] += r.m[1][0];
			m[1][1] += r.m[1][1];
			m[1][2] += r.m[1][2];
			m[1][3] += r.m[1][3];

			m[2][0] += r.m[2][0];
			m[2][1] += r.m[2][1];
			m[2][2] += r.m[2][2];
			m[2][3] += r.m[2][3];

			m[3][0] += r.m[3][0];
			m[3][1] += r.m[3][1];
			m[3][2] += r.m[3][2];
			m[3][3] += r.m[3][3];
			return *this;
		}

		//! Add matrix
		inline Matrix4 operator+(const Matrix4 & r) const {
			Matrix4 tmp_m4(*this);
			tmp_m4 += r;
			return tmp_m4;
		}

		//! Multiply matrix with another matrix
		Matrix4 operator*(const Matrix4 & r) const;

		//! Multiply matrix with a vector and result is vector [3x3 * 3x1 = 3x1]
		inline Vector4 operator*(const Vector4 & v4) const {
			return Vector4(
					m[0][0] * v4.x + m[0][1] * v4.y + m[0][2] * v4.z + m[0][3] * v4.w,
					m[1][0] * v4.x + m[1][1] * v4.y + m[1][2] * v4.z + m[1][3] * v4.w,
					m[2][0] * v4.x + m[2][1] * v4.y + m[2][2] * v4.z + m[2][3] * v4.w,
					m[3][0] * v4.x + m[3][1] * v4.y + m[3][2] * v4.z + m[3][3] * v4.w);
		}

		//!@}

		//! Get transpose matrix
		inline Matrix4 transpose() const {
			return Matrix4(
					m[0][0], m[1][0], m[2][0], m[3][0],
					m[0][1], m[1][1], m[2][1], m[3][1],
					m[0][2], m[1][2], m[2][2], m[3][2],
					m[0][3], m[1][3], m[2][3], m[3][3]);
		}

		//! Get the inverse matrix
		Matrix4 inverse() const;

		//! Set the translation transformation
		void setTranslation(Vector3 & v) {
			m[3][0] = v.x;
			m[3][1] = v.y;
			m[3][2] = v.z;
			m[3][3] = 1;
		}
	};

	//! Create a prespective projection matrix
	Matrix4 perspective(Angle fovy, Real aspect, Real znear, Real zfar);

	//! Create an orthographic projection matrix
	Matrix4 ortho(Real left, Real right, Real bottom, Real top, Real near, Real far);
}

#endif
