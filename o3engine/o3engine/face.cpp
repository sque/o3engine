#include "./face.hpp"

namespace o3engine
{
	// Default constructor
	Face::Face()
	{
		normals[0] = normals[1] = normals[2] = Vector3::UNIT_Y;
	}

	Face::Face(const Vector3 & _p1, const Vector3 & _p2, const Vector3 & _p3,
		const Vector3 & _n1, const Vector3 & _n2, const Vector3 & _n3)
	{
		points[0] = _p1;
		points[1] = _p2;
		points[2] = _p3;
		normals[0] = _n1;
		normals[1] = _n2;
		normals[2] = _n3;
	}

	// Constructor with points and one normal for all vertexes
	Face::Face(const Vector3 & _p1, const Vector3 & _p2, const Vector3 & _p3, const Vector3 & n)
	{
		points[0] = _p1;
		points[1] = _p2;
		points[2] = _p3;
		normals[0] = normals[1] = normals[2] = n;
	}

	// Copy operator
	Face & Face::operator=(const Face & r)
	{
		// Copy points
		points[0] = r.points[0];
		points[1] = r.points[1];
		points[2] = r.points[2];

		// Copy light normals
		normals[0] = r.normals[0];
		normals[1] = r.normals[1];
		normals[2] = r.normals[2];

		// Copy textcoords
		textcords[0] = r.textcords[0];
		textcords[1] = r.textcords[1];
		textcords[2] = r.textcords[2];
		return * this;
	}


	Real Face::calcSphericalSize() const
	{   Real size = 0;
		Real vLength;   // Legth of vector

		size = points[0].length();

		if ((vLength = points[1].length()) > size)
			size = vLength;

		if ((vLength = points[2].length()) > size)
			size = vLength;

		return size;
	}
}
