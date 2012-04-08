#include "./geometry.hpp"
#include <limits>
#include <sstream>
#include <stddef.h>
#include <limits>

namespace o3engine
{
	GeometryRenderer::GeometryRenderer(Geometry & gm) :
		m_geometry(gm),
		mp_vao(nullptr),
		mp_vbo(nullptr),
		mp_ebo(nullptr){
	}

	//! Destroy the render
	GeometryRenderer::~GeometryRenderer() {
		if (mp_ebo)
			delete mp_ebo;
		if (mp_vbo)
			delete mp_vbo;
		if (mp_vao)
			delete mp_vao;
	}

	void GeometryRenderer::uploadToGPU() {
		if (!mp_vbo) {
			mp_vbo = new ogl::buffer(ogl::buffer_type::ARRAY);
			mp_vbo->define_data(sizeof(Vertex) * m_geometry.vertices().size(), &m_geometry.vertices()[0], ogl::buffer_usage_pattern::STATIC_DRAW);
		}

		if (!mp_ebo) {
			mp_ebo = new ogl::buffer(ogl::buffer_type::ELEMENT_ARRAY);
			size_t total_indices = m_geometry.indices().size();
			size_t type_size;
			void * pindices = nullptr;
			if (total_indices <= numeric_limits<std::uint8_t>::max()) {
				m_elements_type = ogl::elements_type::UNSIGNED_BYTE;
				type_size = sizeof(GLubyte);
				pindices = malloc(type_size * total_indices);
				for(size_t i = 0; i < total_indices; i++) {
					reinterpret_cast<GLubyte *>(pindices)[i] = m_geometry.indices()[i];
				}
			} else if (total_indices <= numeric_limits<std::uint16_t>::max()) {
				m_elements_type = ogl::elements_type::UNSIGNED_SHORT;
				type_size = sizeof(GLushort);
				pindices = malloc(type_size * total_indices);
				for(size_t i = 0; i < total_indices; i++) {
					reinterpret_cast<GLushort *>(pindices)[i] = m_geometry.indices()[i];
				}
			} else if (total_indices <= numeric_limits<std::uint32_t>::max()) {
				m_elements_type = ogl::elements_type::UNSIGNED_INT;
				type_size = sizeof(GLuint);
				pindices = malloc(type_size * total_indices);
				for(size_t i = 0; i < total_indices; i++) {
					reinterpret_cast<GLuint *>(pindices)[i] = m_geometry.indices()[i];
				}
			}

			mp_ebo->define_data(total_indices * type_size, pindices, ogl::buffer_usage_pattern::STATIC_DRAW);
			free(pindices);
		}

		if (!mp_vao) {
			mp_vao = new ogl::vertex_array();
			mp_vao->get_attrib(0).set_pointerf(*mp_vbo, 3, ogl::attribf_data_type::DOUBLE, sizeof(Vertex), 0);
			mp_vao->get_attrib(0).enable();
			if (m_geometry.attributes().has_flag(VertexAttributes::normal)) {
				mp_vao->get_attrib(1).set_pointerf(*mp_vbo, 3, ogl::attribf_data_type::DOUBLE, sizeof(Vertex), offsetof(Vertex, normal));
				mp_vao->get_attrib(1).enable();
			}
			if (m_geometry.attributes().has_flag(VertexAttributes::tangent_bitangent)) {
				mp_vao->get_attrib(10).set_pointerf(*mp_vbo, 3, ogl::attribf_data_type::DOUBLE, sizeof(Vertex), offsetof(Vertex, tangent));
				mp_vao->get_attrib(10).enable();

				mp_vao->get_attrib(11).set_pointerf(*mp_vbo, 3, ogl::attribf_data_type::DOUBLE, sizeof(Vertex), offsetof(Vertex, bitangent));
				mp_vao->get_attrib(11).enable();
			}
		}
	}

	//! Set material by name
	bool Geometry::setMaterial(const string & mat) {
		return setMaterial(MaterialManager::getObjectPtr(mat));
	}

	//! Set material
	bool Geometry::setMaterial(const Material * pmaterial) {
		if (!pmaterial) {
			mp_material = MaterialManager::getSingletonPtr()->getDefaultMaterialPtr();
			return false;
		}
		mp_material = pmaterial;
		return true;
	}

	//! Draw mesh
	void GeometryRenderer::draw(SceneRendererVisitor * pvisitor) {
		pvisitor->populateSceneParameters(&const_cast<ogl::program &>(m_geometry.getMaterialPtr()->getProgram()));
		m_geometry.getMaterialPtr()->getProgram().use();
		if (mp_ebo)
			// Indexed based
			mp_vao->draw_elements(ogl::primitive_type::TRIANGLES, m_geometry.indices().size(), *mp_ebo, m_elements_type);
		else
			// Raw rendering
			mp_vao->draw(ogl::primitive_type::TRIANGLES, 0, m_geometry.totalElements());
	}

	void boundary_sphere(const Geometry & gm, Real & radius) {
		radius = 0;
		for(auto vertex : gm.vertices()) {
			Real v_sq_pos = vertex.position.squaredLength();
			if (v_sq_pos > radius)
				radius = v_sq_pos;
		}
		radius = sqrt(radius);
	}

	//! Calculate boundary box
	void boundary_box(const Geometry & gm, Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max) {
		x_min = y_min = z_min = std::numeric_limits<Real>::max();
		x_max = y_max = z_max = std::numeric_limits<Real>::min();

		for(auto vertex : gm.vertices()) {
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

	std::string info(const Geometry & gm) {
		std::ostringstream ss;

		ss << "Geometry{ Attributes:";
		if (gm.attributes().has_flag(VertexAttributes::position))
			ss << "position,";
		if (gm.attributes().has_flag(VertexAttributes::normal))
			ss << "normal,";
		if (gm.attributes().has_flag(VertexAttributes::tex_coords_0))
			ss << "tex_coords[1],";
		if (gm.attributes().has_flag(VertexAttributes::tangent_bitangent))
			ss << "tangent_bitangent,";
		ss << " Vertices:" << gm.totalVertices() << ", Elements:" << gm.totalElements() << " }";
		return ss.str();
	}

	std::string info(const Vector3 & sm) {
		std::ostringstream ss;
		ss << "V3{" << sm.x << ", " << sm.y << ", " << sm.z << "}";
		return ss.str();
	}

	//! Dump object to output
	std::string dump_object(const Geometry & gm) {
		std::ostringstream ss;
		ss << "Vertices :" << std::endl;
		size_t i = 0;
		for(auto & v : gm.vertices()) {
			ss << " [" << i << "]: ";
			if (gm.attributes().has_flag(VertexAttributes::position))
				ss << "P: " << info(v.position) << ", ";
			if (gm.attributes().has_flag(VertexAttributes::normal))
				ss << "N: " << info(v.normal) << ", ";
			if (gm.attributes().has_flag(VertexAttributes::tangent_bitangent)) {
				ss << "T: " << info(v.tangent) << ", ";
				ss << "BT: " << info(v.bitangent)  << ", ";
			}
			ss << endl;
			i++;
		}

		ss << "Indices : ";
		for(auto & ind : gm.indices()) {
			ss << ind << ", ";
		}
		return ss.str();
	}
}
