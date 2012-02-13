#ifndef O3ENGINE_MATRIX3_HPP_INCLUDED
#define O3ENGINE_MATRIX3_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector3.hpp"

namespace o3engine {
	//! [R3] Class for handling orthogonal matrices 3x3
	/**
	 * @par Class Characteristics
	 * Matrix3 is @ref copyable_page, @ref noninherit_page and follows the @ref sfn_page
	 *
	 * @ingroup base_group
	 */
	class Matrix3 {
	private:
		Real m[3][3]; // Matrix 3x3

	public:
		//! Identity matrix 3x3
		const static Matrix3 IDENTITY;
		//! Zero matrix 3x3
		const static Matrix3 ZERO;

		//! Constructor does <b>NOT</b> initialize values for performance
		inline Matrix3() {
		}

		//! Constructor from C array
		inline Matrix3(const Real * rv) {
			memcpy(m, rv, sizeof(Real) * 9);
		}

		//! Construct from values
		inline Matrix3(Real m00, Real m01, Real m02, Real m10, Real m11, Real m12,
				Real m20, Real m21, Real m22) {
			m[0][0] = m00;
			m[0][1] = m01;
			m[0][2] = m02;
			m[1][0] = m10;
			m[1][1] = m11;
			m[1][2] = m12;
			m[2][0] = m20;
			m[2][1] = m21;
			m[2][2] = m22;
		}

		//! Copy constructor
		inline Matrix3(const Matrix3 & r) {
			memcpy(m, r.m, sizeof(Real) * 9);
		}

		//! Get a specific column in a Vector3 object (no range check)
		inline Vector3 getColumn(int col) const {
			return Vector3(m[0][col], m[1][col], m[2][col]);
		}

		//! Get a specific row in a Vector3 object (no range check)
		inline Vector3 getRow(int row) const {
			return Vector3(m[row][0], m[row][1], m[row][2]);
		}

		//! Set a specific column by a Vector3 object
		inline Matrix3 & setColumn(int col, const Vector3 & rv) {
			m[0][col] = rv.x;
			m[1][col] = rv.y;
			m[2][col] = rv.z;
			return *this;
		}

		//! Set a specific row by a Vector3 object
		inline Matrix3 & setRow(int row, const Vector3 & rv) {
			m[row][0] = rv.x;
			m[row][1] = rv.y;
			m[row][2] = rv.z;
			return *this;
		}

		//! @name Operators (textual or algebraically)
		//! @{

		//! Check for equality
		inline bool operator==(const Matrix3 & r) const {
			return memcmp(m, r.m, sizeof(Real) * 9) == 0;
		}

		//! Check if are different
		inline bool operator!=(const Matrix3 & r) const {
			return !operator==(r);
		}

		//! Self-Substract matrix
		inline Matrix3 & operator-=(const Matrix3 & r) {
			m[0][0] -= r.m[0][0];
			m[0][1] -= r.m[0][1];
			m[0][2] -= r.m[0][2];
			m[1][0] -= r.m[1][0];
			m[1][1] -= r.m[1][1];
			m[1][2] -= r.m[1][2];
			m[2][0] -= r.m[2][0];
			m[2][1] -= r.m[2][1];
			m[2][2] -= r.m[2][2];
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
		inline Matrix3 operator-(const Matrix3 & r) const {
			Matrix3 tmp_m3(*this);
			tmp_m3 -= r;
			return tmp_m3;
		}

		//! Self-Add matrix
		inline Matrix3 & operator+=(const Matrix3 & r) {
			m[0][0] += r.m[0][0];
			m[0][1] += r.m[0][1];
			m[0][2] += r.m[0][2];
			m[1][0] += r.m[1][0];
			m[1][1] += r.m[1][1];
			m[1][2] += r.m[1][2];
			m[2][0] += r.m[2][0];
			m[2][1] += r.m[2][1];
			m[2][2] += r.m[2][2];
			return *this;
		}

		//! Add matrix
		inline Matrix3 operator+(const Matrix3 & r) const {
			Matrix3 tmp_m3(*this);
			tmp_m3 += r;
			return tmp_m3;
		}

		//! Multiply matrix with another matrix
		Matrix3 operator*(const Matrix3 & r) const;

		//! Multiply matrix with a vector and result is vector [3x3 * 3x1 = 3x1]
		inline Vector3 operator*(const Vector3 & v3) const {
			return Vector3(m[0][0] * v3.x + m[0][1] * v3.y + m[0][2] * v3.z,
					m[1][0] * v3.x + m[1][1] * v3.y + m[1][2] * v3.z,
					m[2][0] * v3.x + m[2][1] * v3.y + m[2][2] * v3.z);
		}

		//!@}

		//! Get transpose matrix
		inline Matrix3 transpose() const {
			return Matrix3(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1],
					m[0][2], m[1][2], m[2][2]);
		}

		//! Get the inverse matrix
		bool inverse(Matrix3 & inverted, Real fTolerance = 1e-06);
	};
}

#endif
