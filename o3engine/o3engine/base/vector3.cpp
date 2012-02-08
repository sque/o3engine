#include "./vector3.hpp"

namespace o3engine
{
	const Vector3 Vector3::ZERO = Vector3(0, 0, 0);
	const Vector3 Vector3::IDENTITY = Vector3(1, 1, 1);
	const Vector3 Vector3::UNIT_X = Vector3(1, 0, 0);
	const Vector3 Vector3::UNIT_Y = Vector3(0, 1, 0);
	const Vector3 Vector3::UNIT_Z = Vector3(0, 0, 1);
    const Vector3 Vector3::NEGATIVE_IDENTITY = Vector3(-1, -1, -1);
	const Vector3 Vector3::NEGATIVE_UNIT_X = Vector3(-1, 0, 0);
	const Vector3 Vector3::NEGATIVE_UNIT_Y = Vector3(0, -1, 0);
	const Vector3 Vector3::NEGATIVE_UNIT_Z = Vector3(0, 0, -1);

}
