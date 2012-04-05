#ifndef O3ENGINE_SUBMESH_H_INCLUDED
#define O3ENGINE_SUBMESH_H_INCLUDED

#include "./prereqs.hpp"
#include "./materialmanager.hpp"
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
	struct SubMeshRenderer {
		//! Reference to sub mesh
		SubMesh & m_submesh;

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
		void draw();

		//! Construct a new renderer
		SubMeshRenderer(SubMesh & sm);

		//! Destroy the render
		~SubMeshRenderer();

		// Uncopiable
		SubMeshRenderer(SubMeshRenderer &) = delete;
		SubMeshRenderer & operator=(SubMeshRenderer &) = delete;
	};

	//! Base class for defining a rendable geometry
	class SubMesh {
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
		SubMesh(attributesflags_type attributes) :
			mp_material(nullptr),
			m_enabled_attributes(attributes){
		}

		// Copiable
		SubMesh(const SubMesh &) = default;
		SubMesh & operator=(const SubMesh &) = default;

		//! Get all vertices
		const vertices_container_type & vertices() const {
			return m_vertices;
		}

		//! Get all vertices
		vertices_container_type & vertices(){
			return m_vertices;
		}

		//! Set material by name
		Material * setMaterial(const string & mat) {
			return mp_material = MaterialManager::getObjectPtr(mat);
		}

		//! Set material
		Material * setMaterial(Material * pmaterial) {
			return mp_material = pmaterial;
		}

		//! Get current material
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

		//! Total number of elemensts (triangles/lines/...)
		size_t totalElements() const {
			if (hasIndices())
				return indices().size() / 3;
			return m_vertices.size() /3;
		}

		//! Enabled attributes of this submesh
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
		Material * mp_material;

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
	void boundary_sphere(const SubMesh & sm, Real & radius);

	//! Calculate boundary box
	void boundary_box(const SubMesh & sm, Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max);

	//! Get info about this object
	std::string info(const SubMesh & sm);
}
#endif
