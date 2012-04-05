#include "./submesh.hpp"
#include <limits>
#include <sstream>
#include <stddef.h>
#include <limits>

namespace o3engine
{
	SubMeshRenderer::SubMeshRenderer(SubMesh & sm) :
		m_submesh(sm),
		mp_vao(nullptr),
		mp_vbo(nullptr),
		mp_ebo(nullptr){
	}

	//! Destroy the render
	SubMeshRenderer::~SubMeshRenderer() {
		if (mp_ebo)
			delete mp_ebo;
		if (mp_vbo)
			delete mp_vbo;
		if (mp_vao)
			delete mp_vao;
	}

	void SubMeshRenderer::uploadToGPU() {
		if (!mp_vbo) {
			mp_vbo = new ogl::buffer(ogl::buffer_type::ARRAY);
			mp_vbo->define_data(sizeof(Vertex) * m_submesh.vertices().size(), &m_submesh.vertices()[0], ogl::buffer_usage_pattern::STATIC_DRAW);
		}
		if (!mp_vao) {
			mp_vao = new ogl::vertex_array();
			mp_vao->get_attrib(0).set_pointerf(*mp_vbo, 3, ogl::attribf_data_type::DOUBLE, sizeof(Vertex), 0);
			mp_vao->get_attrib(0).enable();
			if (m_submesh.attributes().has_flag(VertexAttributes::normal)) {
				mp_vao->get_attrib(1).set_pointerf(*mp_vbo, 3, ogl::attribf_data_type::DOUBLE, sizeof(Vertex), offsetof(Vertex, normal));
				mp_vao->get_attrib(1).enable();
			}
			if (m_submesh.attributes().has_flag(VertexAttributes::tangent_bitangent)) {
				mp_vao->get_attrib(10).set_pointerf(*mp_vbo, 3, ogl::attribf_data_type::DOUBLE, sizeof(Vertex), offsetof(Vertex, tangent));
				mp_vao->get_attrib(10).enable();

				mp_vao->get_attrib(11).set_pointerf(*mp_vbo, 3, ogl::attribf_data_type::DOUBLE, sizeof(Vertex), offsetof(Vertex, bitangent));
				mp_vao->get_attrib(11).enable();
			}
		}

		if (!mp_ebo) {
			mp_ebo = new ogl::buffer(ogl::buffer_type::ELEMENT_ARRAY);
			size_t total_indices = m_submesh.indices().size();
			size_t type_size;
			void * pindices = nullptr;
			if (total_indices <= numeric_limits<std::uint8_t>::max()) {
				m_elements_type = ogl::elements_type::UNSIGNED_BYTE;
				type_size = sizeof(GLubyte);
				pindices = malloc(type_size * total_indices);
				for(size_t i = 0; i < total_indices; i++) {
					reinterpret_cast<GLubyte *>(pindices)[i] = m_submesh.indices()[i];
				}
			} else if (total_indices <= numeric_limits<std::uint16_t>::max()) {
				m_elements_type = ogl::elements_type::UNSIGNED_SHORT;
				type_size = sizeof(GLushort);
				pindices = malloc(type_size * total_indices);
				for(size_t i = 0; i < total_indices; i++) {
					reinterpret_cast<GLushort *>(pindices)[i] = m_submesh.indices()[i];
				}
			} else if (total_indices <= numeric_limits<std::uint32_t>::max()) {
				m_elements_type = ogl::elements_type::UNSIGNED_INT;
				type_size = sizeof(GLuint);
				pindices = malloc(type_size * total_indices);
				for(size_t i = 0; i < total_indices; i++) {
					reinterpret_cast<GLuint *>(pindices)[i] = m_submesh.indices()[i];
				}
			}

			mp_ebo->define_data(total_indices * type_size, pindices, ogl::buffer_usage_pattern::STATIC_DRAW);
			free(pindices);
		}
	}

	//! Draw mesh
	void SubMeshRenderer::draw() {
		if (mp_ebo)
			// Indexed based
			mp_vao->draw_elements(ogl::primitive_type::TRIANGLES, m_submesh.totalElements(), *mp_ebo, m_elements_type);
		else
			// Raw rendering
			mp_vao->draw(ogl::primitive_type::TRIANGLES, 0, m_submesh.totalElements());
	}

	void boundary_sphere(const SubMesh & sm, Real & radius) {
		radius = 0;
		for(auto vertex : sm.vertices()) {
			Real v_sq_pos = vertex.position.squaredLength();
			if (v_sq_pos > radius)
				radius = v_sq_pos;
		}
		radius = sqrt(radius);
	}

	//! Calculate boundary box
	void boundary_box(const SubMesh & sm, Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max) {
		x_min = y_min = z_min = std::numeric_limits<Real>::max();
		x_max = y_max = z_max = std::numeric_limits<Real>::min();

		for(auto vertex : sm.vertices()) {
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

	std::string info(const SubMesh & sm) {
		std::ostringstream ss;

		ss << "SubMesh{ Attributes:";
		if (sm.attributes().has_flag(VertexAttributes::position))
			ss << "position,";
		if (sm.attributes().has_flag(VertexAttributes::normal))
			ss << "normal,";
		if (sm.attributes().has_flag(VertexAttributes::tex_coords_0))
			ss << "tex_coords[1],";
		if (sm.attributes().has_flag(VertexAttributes::tangent_bitangent))
			ss << "tangent_bitangent,";
		ss << " Vertices:" << sm.totalVertices() << ", Elements:" << sm.totalElements() << " }";
		return ss.str();
	}
}
