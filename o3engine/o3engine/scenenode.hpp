#ifndef SCENENODE_H_INCLUDED
#define SCENENODE_H_INCLUDED

#include "./prereqs.hpp"
#include "./objectmanager.hpp"
#include "./camera.hpp"

namespace o3engine {

//! Abstract node of a scene manager
	class SceneNode {
	protected:
		SceneManager * mp_scene_manager; //! Parent scene manager
		Camera * mp_camera; //! Pointer to camera

		inline SceneNode(SceneManager * _pmanager) :
				mp_scene_manager(_pmanager), mp_camera(NULL) {
		}

	public:
		virtual ~SceneNode() {
		}

		// Remove an object
		virtual bool removeObject(DrawableObject * p_object) = 0;

		// Attach an object
		virtual void attachObject(DrawableObject * p_object) = 0;

		// Get global orientation of node
		virtual Quaternion & getGlobalOrientation() = 0;

		// Get global position of node
		virtual Vector3 & getGlobalPosition() = 0;

		//! Get global transformation matrix
		virtual Matrix4 & getGlobalTransformation() = 0;

		//! Attach an object on this node (By Name)
		/**
		 When a MovableObject is attached on a node, the
		 object will be rendered at the position of node. This
		 attachObject will attach by his name.
		 @param _obj_name The unique name of the object you want to attach.
		 @remarks Node can hold multiple objects at the same time.
		 */
		inline void attachObject(const string & obj_name) {
			attachObject(ObjectManager::getSingletonPtr()->getObjectPtr(obj_name));
		}

		//! Remove an object from this node (By Name)
		/**
		 This will remove an object that is attached on this
		 node.
		 @param _obj_name The name of the object that you want to dettach.
		 @return True if the object has been found and dettached, or False if the object
		 has not been found attached on this node.
		 */
		inline bool removeObject(const string & obj_name) {
			return removeObject(
					ObjectManager::getSingletonPtr()->getObjectPtr(obj_name));
		}

		// Return the scenemanager that this node belongs to
		inline const SceneManager * getMySceneManager() const{
			return mp_scene_manager;
		}

		// Return the scenemanager that this node belongs to
		inline SceneManager * getMySceneManager(){
			return mp_scene_manager;
		}

		// Detach camera
		inline void detachCamera() {
			if (mp_camera)
				mp_camera->mp_scene_node = NULL;
			mp_camera = NULL;
		}

		// Attach a camera
		inline void attachCamera(Camera * pcamera) {
			if (mp_camera)
				mp_camera->mp_scene_node = NULL;
			mp_camera = pcamera;
			if (mp_camera->mp_scene_node)
				mp_camera->mp_scene_node->detachCamera();
			mp_camera->mp_scene_node = this;
		}
	};
}
#endif
