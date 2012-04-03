#ifndef O3ENGINE_CAMERA_HPP_INCLUDED
#define O3ENGINE_CAMERA_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./renderline/node.hpp"

namespace o3engine {

	//! Generic camera handler
	/**
	 * To create a new camera, create an object from this class,
	 * and attach it on node.
	 */
	class Camera:
		public RenderLine::Node{
		friend class SceneNode;
	protected:
		//! Pointer to attached scene node;
		SceneNode * mp_scene_node;

		//! Projection Matrix
		Matrix4 m_proj_matrix;

	public:

		//! Default constructor
		Camera():mp_scene_node(nullptr){}

		virtual ~Camera();

		//! Get attached scene node
		inline SceneNode * getSceneNode() {
			return mp_scene_node;
		}

		//! Get projection matrix
		const Matrix4 & getProjectionMatrix() {
			return m_proj_matrix;
		}

		virtual void render();

	};
}

#endif
