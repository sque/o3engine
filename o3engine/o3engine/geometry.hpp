#ifndef O3ENGINE_GEOMETRY_HPP_INCLUDED
#define O3ENGINE_GEOMETRY_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./materialmanager.hpp"
#include "./drawableobject.hpp"
#include "ogl/utils/info.hpp"
#include <vector>
#include <cstdint>

namespace o3engine {

	//! Definition of a generic vertex
	struct Vertex {
		Vector3 position;
		Vector3 normal;
		Vector3 tex_coords[6];
		Vector3 tangent;
		Vector3 bitangent;

		void translate(const Vector3 & trans) {
			position.translate(trans);
		}

		Vertex() = default;

		Vertex(const Vector3 & pos) :
			position(pos){
		}
	};

	//! All available vertex attributes
	enum class VertexAttributes {
		position = 1,
		normal = 2,
		tex_coords_0 = 4,
		tex_coords_1 = 8,
		tex_coords_2 = 16,
		tex_coords_3 = 32,
		tex_coords_4 = 64,
		tex_coords_5 = 128,
		tangent_bitangent = 256,
		all = (tangent_bitangent * 2) -1
	};


	//! GPU Renderer
	struct GeometryRenderer {
		//! Reference to sub mesh
		Geometry & m_geometry;

		//! Vertex array object
		ogl::vertex_array * mp_vao;

		//! Vertex buffer object
		ogl::buffer * mp_vbo;

		//! Element buffer object (indices)
		ogl::buffer * mp_ebo;

		//! Elements type
		ogl::elements_type m_elements_type;

		//! Upload mesh to GPU
		void uploadToGPU();

		//! Draw mesh
		void draw(SceneRendererVisitor * pvisitor);

		//! Construct a new renderer
		GeometryRenderer(Geometry & sm);

		//! Destroy the render
		~GeometryRenderer();

		// Uncopiable
		GeometryRenderer(GeometryRenderer &) = delete;
		GeometryRenderer & operator=(GeometryRenderer &) = delete;
	};

	//! Base class for defining geometry and material
	class Geometry {
	public:

		//! Type of vertex
		typedef Vertex vertex_type;

		//! Type of vertices container
		typedef std::vector<vertex_type> vertices_container_type;

		//! Type of index
		typedef std::uint32_t index_type;

		//! Type of indices container
		typedef std::vector<index_type> indices_container_type;

		//! Type of bitflags
		typedef ogl::utils::bitflags<VertexAttributes> attributesflags_type;

		//! Constructor
		Geometry(attributesflags_type attributes) :
			mp_material(MaterialManager::getSingleton().getDefaultMaterialPtr()),
			m_enabled_attributes(attributes){
		}

		// Copiable
		Geometry(const Geometry &) = default;
		Geometry & operator=(const Geometry &) = default;

		//! Get all vertices
		const vertices_container_type & vertices() const {
			return m_vertices;
		}

		//! Get all vertices
		vertices_container_type & vertices(){
			return m_vertices;
		}

		//! Set material by name
		bool setMaterial(const string & mat);

		//! Set material
		bool setMaterial(const Material * pmaterial);

		//! Get current material (const)
		const Material * getMaterialPtr() const {
			return mp_material;
		}

		//! Translate all vertices
		void translate(const Vector3 & trans) {
			vertices_container_type::iterator it;
			for(auto & vertex : m_vertices) {
				vertex.translate(trans);
			}
		}

		//! Total number of vertices
		size_t totalVertices() const{
			return m_vertices.size();
		}

		//! Total number of elements (triangles/lines/...)
		size_t totalElements() const {
			if (hasIndices())
				return indices().size() / 3;
			return m_vertices.size() /3;
		}

		//! Enabled attributes of this geometry
		const attributesflags_type & attributes() const {
			return m_enabled_attributes;
		}

		//! Check if it has indices
		bool hasIndices() const {
			return m_indices.size();
		}

		//! Get indices and manipulate (if any)
		indices_container_type & indices() {
			return m_indices;
		}

		//! Get indices (if any)
		const indices_container_type & indices() const {
			return m_indices;
		}

	protected:

		//! Pointer to material
		const Material * mp_material;

		//! Vertices container
		vertices_container_type m_vertices;

		//! Indices container
		indices_container_type m_indices;

		//! Primitive type
		ogl::primitive_type m_primitive;

		///! Enabled attributes
		attributesflags_type m_enabled_attributes;
	};

	//! Calculate boundary sphere
	/**
	 * @param radius [out] The minimum radius of a sphere that can hold this mesh
	 */
	void boundary_sphere(const Geometry & sm, Real & radius);

	//! Calculate boundary box
	void boundary_box(const Geometry & sm, Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max);

	//! Get info about this object
	std::string info(const Geometry & sm);

	//! Dump object to output
	std::string dump_object(const Geometry & sm);
}
#endif
