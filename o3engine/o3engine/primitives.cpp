#include "./primitives.hpp"

namespace o3engine {

	// Vertex position normal texcoord
	Vertex vx_build(const Vector3 & position, const Vector3 & normal, const Vector3 & texcoord) {
		Vertex vx;
		vx.position = position;
		vx.normal = normal;
		vx.tex_coords[0] = texcoord;
		return std::move(vx);
	}

	// Vertex position normal texcoord
	Vertex vx_build(const Vector3 & position) {
		Vertex vx;
		vx.position = position;
		vx.normal = vx.position; vx.normal.normalize();
		vx.tex_coords[0] = vx.position; vx.tex_coords[0].normalize();
		return std::move(vx);
	}

	UVSphere::UVSphere(const string & name) :
			PrimitiveObject(name),
			m_radius(0.5),
			m_slices(5),
			m_stacks(5) {
		buildSphere();
		updateGPUObjects();
	}

	UVSphere::UVSphere(const string & name, Real radius , size_t slices, size_t stacks) :
			PrimitiveObject(name),
			m_radius(radius),
			m_slices(slices),
			m_stacks(stacks) {
		buildSphere();
		updateGPUObjects();
	}

	void UVSphere::buildSphere() {
		float pix2 = (2.0f *M_PI);
		float f_step = M_PI/m_stacks;
		float l_step = pix2/m_slices;

		m_vertices.clear();
		m_indices.clear();

		//Allocate space
		size_t total_vertices = (m_stacks -1)*m_slices+2;
		m_vertices.reserve(total_vertices);
		m_vertices.reserve(total_vertices);
		size_t total_trianles = (m_stacks -1)*m_slices*2;
		m_indices.reserve(total_trianles);

		// Up vertex
		m_vertices.push_back(vx_build(Vector3(0, m_radius, 0)));

		// Create middle m_stacks
		for (size_t r = 1; r < m_stacks; r++) {
			float f = f_step * r;
			float pr = sin(f)*m_radius;
			float y = cos(f)* m_radius;
			for(size_t s = 0; s < m_slices; s++) {
				float l = l_step * s;
				m_vertices.push_back(Vector3(cos(l)*pr, y, sin(l)*pr));
			}
		}

		// Down vertex
		m_vertices.push_back(Vector3(0, -m_radius, 0));

		// Create indices

		// Upper cap
		for(size_t s = 0; s < m_slices; s++) {
			int next_right = (s < m_slices -1)?1:1 -m_slices;
			indices_container_type::value_type pn = s+1;
			m_indices.push_back(pn);
			m_indices.push_back(0);
			m_indices.push_back(pn + next_right);
		}

		// Middle
		for(size_t r = 0; r < m_stacks -2; r++) {
			for(size_t s = 0; s < m_slices; s++) {
				unsigned int pn = (r * m_slices) + s +1;
				int next_right = (s < m_slices -1)?1:1 -m_slices;

				m_indices.push_back(pn);
				m_indices.push_back(pn + m_slices + next_right);
				m_indices.push_back(pn + m_slices);

				m_indices.push_back(pn);
				m_indices.push_back(pn + next_right);
				m_indices.push_back(pn + m_slices + next_right);
			}
		}

		// Down cap
		indices_container_type::value_type last_vrt = m_vertices.size()-1;
		for(size_t s = 0; s < m_slices; s++) {
			indices_container_type::value_type pn = ((m_stacks-2)*m_slices) +1 +s;
			int next_right = (s < m_slices -1)?1:1 -m_slices;
			m_indices.push_back(pn);
			m_indices.push_back(pn+next_right);
			m_indices.push_back(last_vrt);
		}
	}

	void Cube::buildCube() {

		m_vertices.clear();
		m_vertices.push_back(vx_build(Vector3(m_size, m_size, m_size)));
		m_vertices.push_back(vx_build(Vector3(m_size, -m_size, m_size)));
		m_vertices.push_back(vx_build(Vector3(-m_size, -m_size, m_size)));
		m_vertices.push_back(vx_build(Vector3(-m_size, m_size, m_size)));
		m_vertices.push_back(vx_build(Vector3(m_size, m_size, -m_size)));
		m_vertices.push_back(vx_build(Vector3(m_size, -m_size, -m_size)));
		m_vertices.push_back(vx_build(Vector3(-m_size, -m_size, -m_size)));
		m_vertices.push_back(vx_build(Vector3(-m_size, m_size, -m_size)));

		m_indices.clear();
		m_indices = { 2, 1, 0,
				3, 2, 0,
				0, 1, 4,
				1, 5, 4,
				2, 3, 6,
				3, 7, 6,
				4, 5, 6,
				4, 6, 7,
				0, 4, 3,
				3, 4, 7,
				1, 2, 5,
				2, 6, 5
		};
	}

	//! Default constructor
	/**
	 * 20 slices and 0.5 x and y radius
	 */
	Disk::Disk(const string & name) :
			PrimitiveObject(name),
			m_slices(20),
			m_xradius(0.5),
			m_yradius(0.5){
		buildDisk();
		updateGPUObjects();
	}

	//! Construct a circle
	Disk::Disk(const string & name, Real radius, size_t slices) :
			PrimitiveObject(name),
			m_slices(slices),
			m_xradius(radius),
			m_yradius(radius){
		buildDisk();
		updateGPUObjects();
	}

	//! Construct an elliptic disk
	Disk::Disk(const string & name, Real xradius, Real yradius, size_t slices) :
			PrimitiveObject(name),
			m_slices(slices),
			m_xradius(xradius),
			m_yradius(yradius){
		buildDisk();
		updateGPUObjects();
	}


	void Disk::buildDisk(){
		Real slice_theta = math::DOUBLE_PI / m_slices;
		Real theta = 0;
		Real x_tex_factor = 0.5 / m_xradius;
		Real y_tex_factor = 0.5 / m_yradius;
		Vector2 TexCordMiddle(0.5, 0.5);

		m_vertices.clear();
		m_indices.clear();

		// Center of disk
		m_vertices.push_back(vx_build(Vector3::ZERO, Vector3::UNIT_Z, Vector3(0.5, 0.5, 0.5)));

		for(size_t i = 0;i < m_slices; i++) {
			m_vertices.push_back(vx_build(Vector3(m_xradius * math::cos(theta), m_xradius * math::sin(theta), 0)));
			Vertex & vx = m_vertices[m_vertices.size() - 1];
			vx.tex_coords[0] = Vector3((m_xradius + vx.position.x) * x_tex_factor,
					1 - ((m_yradius + vx.position.y) * y_tex_factor), 0);
			theta -= slice_theta;

			m_indices.push_back(0);
			m_indices.push_back(i + 1);
			if (i == m_slices - 1) {
				m_indices.push_back(1);	// Closing circle
			} else {
				m_indices.push_back(i + 2);
			}
		}
	}

	//! Build quad
	void Quad::buildQuad() {
		m_vertices.clear();
		m_indices.clear();

		m_vertices.push_back(vx_build(m_points[0], Vector3::UNIT_Z, Vector3(-1, 1, 0)));
		m_vertices.push_back(vx_build(m_points[1], Vector3::UNIT_Z, Vector3(1, 1, 0)));
		m_vertices.push_back(vx_build(m_points[2], Vector3::UNIT_Z, Vector3(1, -1, 0)));
		m_vertices.push_back(vx_build(m_points[3], Vector3::UNIT_Z, Vector3(-1, -1, 0)));

		m_indices = {
			0, 1, 2,
			2, 3, 0
		};
	}
}
