#ifndef O3ENGINE_SUBMESH_H_INCLUDED
#define O3ENGINE_SUBMESH_H_INCLUDED

#include "./prereqs.hpp"
#include "./face.hpp"
#include <vector>
#include "./materialmanager.hpp"

namespace o3engine {

	struct Vertex {
		Vector3 position;
		Vector3 normal;
		Vector2 tex_coords[4];
		Vector3 tangent;
		Vector3 bitangent;

		void translate(const Vector3 & trans) {
			position.translate(trans);
		}
	};
	/**************
	 * TODO: Theloume primitive type tou mesh
	 *  kai kapws na ginetai render.
	 */

	//! Base class for defining a rendable geometry
	class SubMesh {
	public:

		//! Type of vertex
		typedef Vertex vertex_type;

		//! Type of vertices container
		typedef std::vector<vertex_type> vertices_container_type;

		//! Constructor
		SubMesh() :
			mp_material(nullptr){
		}

		// Copiable
		SubMesh(const SubMesh & r) = default;
		SubMesh & operator=(const SubMesh & r) = default;

		//! Get all vertices
		const vertices_container_type & vertices() const {
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

		//! Calculate boundary sphere
		/**
		 * @param radius [out] The minimum radius of a sphere that can hold this mesh
		 */
		void calculateBoundarySphere(Real & radius) const;

		//! Calculate boundary box
		void calculateBoundaryBox(Real & x_min, Real & x_max, Real & y_min, Real & y_max, Real & z_min, Real & z_max);

	protected:

		//! Pointer to material
		Material * mp_material;

		//! Vertices container
		vertices_container_type m_vertices;
	};
}

#endif
