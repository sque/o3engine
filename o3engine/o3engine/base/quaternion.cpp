#include "./quaternion.hpp"
#include "./math.hpp"

namespace o3engine {
	const Quaternion Quaternion::IDENTITY = Quaternion(1, 0, 0, 0);

	// Normalize quaternion
	Quaternion & Quaternion::normalize() {
		Real magnitute = sqrt(x * x + y * y + z * z + w * w);

		if (magnitute - 1e-08) {
			w /= magnitute;
			x /= magnitute;
			y /= magnitute;
			z /= magnitute;
		}
		return *this;
	}

	// Multiply quaternions
	Quaternion Quaternion::operator*(const Quaternion & r) const {
		Quaternion tmpQuatr;

		tmpQuatr.x = x * r.w + y * r.z - z * r.y + w * r.x;
		tmpQuatr.y = -x * r.z + y * r.w + z * r.x + w * r.y;
		tmpQuatr.z = x * r.y - y * r.x + z * r.w + w * r.z;
		tmpQuatr.w = -x * r.x - y * r.y - z * r.z + w * r.w;
		return tmpQuatr;
	}

	// Convert from Axis Angle
	void Quaternion::fromAxisAngle(const Vector3 &v, const Angle & angle) {
		Real sinAngle;
		Real half_radAngle = angle.getRadian() * 0.5f;

		sinAngle = sin(half_radAngle);

		x = (v.x * sinAngle);
		y = (v.y * sinAngle);
		z = (v.z * sinAngle);
		w = cos(half_radAngle);
	}

	void Quaternion::toAxisAngle(Vector3 & axis, Angle & angle) const {
		Real scale = sqrt(x * x + y * y + z * z);

		if (scale != 0) {
			axis.x = (x / scale);
			axis.y = (y / scale);
			axis.z = (z / scale);
		} else
			axis = Vector3::ZERO;

		// Fault tolerence
		if (w < -1.0f) {
			if ((w + 1e-05) > -1)
				angle = Radian(0);
		} else if (w > 1.0f) {
			if ((w - 1e-05) < 1)
				angle = Radian(0);

		} else
			angle = Radian(acos(w) * 2.0f);
	}

	// Slerp from this orientation to a destination one
	Quaternion Quaternion::slerp(const Quaternion & dst, Real factor) {
		Real fCos = dotProduct(dst);
		Quaternion qu_inner;

		// Do we need to invert rotation?
		if (fCos < 0.0f) {
			fCos = -fCos;
			qu_inner = -dst;
		} else {
			qu_inner = dst;
		}

		if (math::abs(fCos) < 1 - 1e-03) {
			// Standard case (slerp)
			Real fSin = sqrt(1 - (fCos * fCos));
			Real fAngle = atan2(fSin, fCos);
			Real fInvSin = 1.0f / fSin;
			Real fCoeff0 = sin((1.0f - factor) * fAngle) * fInvSin;
			Real fCoeff1 = sin(factor * fAngle) * fInvSin;
			return fCoeff0 * (*this) + fCoeff1 * dst;
		} else {
			// There are two situations:
			// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
			//    interpolation safely.
			// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
			//    are an infinite number of possibilities interpolation. but we haven't
			//    have method to fix this case, so just use linear interpolation here.
			Quaternion t = (1.0f - factor) * (*this) + factor * dst;
			// taking the complement requires renormalisation
			t.normalize();
			return t;
		}
	}

	Vector3 Quaternion::operator*(const Vector3 & rv) const {
		Real vx = rv.x, vy = rv.y, vz = rv.z;
		Quaternion vq;

		// Rotation of a vector
		// The formula to rotate a vector is vout = qu * vin * qu.getConjugate()
		// We simplify this process by omitting multiplications with zero and
		// calculation of W in final result as it is not needed

		// Multiply this with input vector (remove multiplications with zero - vector has no W)
		vq.x = y * vz - z * vy + w * vx;
		vq.y = -x * vz + z * vx + w * vy;
		vq.z = x * vy - y * vx + w * vz;
		vq.w = -x * vx - y * vy - z * vz;

		// Multiply result with conjugate
		return Vector3(vq.x * w + vq.y * -z - vq.z * -y + vq.w * -x,
				-vq.x * -z + vq.y * w + vq.z * -x + vq.w * -y,
				vq.x * -y - vq.y * -x + vq.z * w + vq.w * -z);
	}
}
