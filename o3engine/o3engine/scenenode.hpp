#ifndef SCENENODE_H_INCLUDED
#define SCENENODE_H_INCLUDED

#include "./prereqs.hpp"
#include "./objectmanager.hpp"
#include "./camera.hpp"

namespace o3engine
{
	//! Abstract node of a scene manager
	class SceneNode
	{
	protected:
		SceneManager * pSceneManager;	//! Parent scene manager
		Camera * pCamera;				//! Pointer to camera

		inline SceneNode(SceneManager * _pmanager)
			:pSceneManager(_pmanager),
			pCamera(NULL)
		{}

	public:
		virtual ~SceneNode(){}

		// Set opengl at new position
		virtual void useme_to_glPosition() = 0;

		// Set opengl at inverted new position
		virtual void useme_to_glInvertPosition() = 0;

		// Remove an object
		virtual bool removeObject(DrawableObject * p_object) = 0;

		// Attach an object
		virtual void attachObject(DrawableObject * p_object) = 0;

		// Get global orientation of node
		virtual Quaternion & getGlobalOrientation() = 0;

		// Get global position of node
		virtual Vector3 & getGlobalPosition() = 0;

		//! Attach an object on this node (By Name)
		/**
			When a MovableObject is attached on a node, the
			object will be rendered at the position of node. This
			attachObject will attach by his name.
		@param _obj_name The unique name of the object you want to attach.
		@remarks Node can hold multiple objects at the same time.
		*/
		inline void attachObject(const string & _obj_name)
		{   attachObject(ObjectManager::getSingletonPtr()->getObjectPtr(_obj_name));    }

		//! Remove an object from this node (By Name)
		/**
			This will remove an object that is attached on this
			node.
		@param _obj_name The name of the object that you want to dettach.
		@return True if the object has been found and dettached, or False if the object
			has not been found attached on this node.
		*/
		inline bool removeObject(const string & _obj_name)
		{   return removeObject(ObjectManager::getSingletonPtr()->getObjectPtr(_obj_name)); }

		// Return the scenemanager that this node belongs to
		inline SceneManager * getMySceneManager()
		{	return pSceneManager;	}

		// Dettach camera
		inline void dettachCamera()
		{	if (pCamera)
				pCamera->pAttachedNode = NULL;
			pCamera = NULL;
		}

		// Attach a camera
		inline void attachCamera(Camera * _pcamera)
		{	if (pCamera)
				pCamera->pAttachedNode = NULL;
			pCamera = _pcamera;
			if (pCamera->pAttachedNode)
				pCamera->pAttachedNode->dettachCamera();
			pCamera->pAttachedNode = this;
		}
	};
}
#endif // SCENENODE_H_INCLUDED
