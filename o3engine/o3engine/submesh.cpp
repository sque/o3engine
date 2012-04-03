#include "./submesh.hpp"
#include <limits>

namespace o3engine
{
	void SubMesh::calculateBoundarySphere(Real & radius) const {
		radius = 0;
		for(auto vertex : m_vertices) {
			Real v_sq_pos = vertex.position.squaredLength();
			if (v_sq_pos > radius)
				radius = v_sq_pos;
		}
		radius = sqrt(radius);
	}

	//! Calculate boundary box
	void SubMesh::calculateBoundaryBox(Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max) {
		x_min = y_min = z_min = std::numeric_limits<Real>::max();
		x_max = y_max = z_max = std::numeric_limits<Real>::min();

		for(auto vertex : m_vertices) {
			if (vertex.position.x < x_min)
				x_min = vertex.position.x;
			if (vertex.position.y < y_min)
				y_min = vertex.position.y;
			if (vertex.position.z < z_min)
				z_min = vertex.position.z;

			if (vertex.position.x > x_max)
				x_max = vertex.position.x;
			if (vertex.position.y > y_max)
				y_max = vertex.position.y;
			if (vertex.position.z > z_max)
				z_max = vertex.position.z;
		}
	}
}
