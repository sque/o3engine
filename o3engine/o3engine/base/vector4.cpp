#include "./vector4.hpp"

namespace o3engine
{
	const Vector4 Vector4::ZERO = Vector4(0,0,0,0);
	const Vector4 Vector4::IDENTITY = Vector4(1,1,1,1);
	const Vector4 Vector4::UNIT_X = Vector4(1,0,0,0);
	const Vector4 Vector4::UNIT_Y = Vector4(0,1,0,0);
	const Vector4 Vector4::UNIT_Z = Vector4(0,0,1,0);
	const Vector4 Vector4::UNIT_W = Vector4(0,0,0,1);
	const Vector4 Vector4::NEGATIVE_IDENTITY = Vector4(-1,-1,-1,-1);
	const Vector4 Vector4::NEGATIVE_UNIT_X = Vector4(-1,0,0,0);
	const Vector4 Vector4::NEGATIVE_UNIT_Y = Vector4(0,-1,0,0);
	const Vector4 Vector4::NEGATIVE_UNIT_Z = Vector4(0,0,-1,0);
	const Vector4 Vector4::NEGATIVE_UNIT_W = Vector4(0,0,0,-1);
}
