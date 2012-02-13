#ifndef O3ENGINE_GENERICNODE_HPP_INCLUDED
#define O3ENGINE_GENERICNODE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./scenenode.hpp"
#include "./light.hpp"

#include <map>
#include <list>
#include <vector>

namespace o3engine {
	//! A node representation on the GenericSceneManager
	class GenericNode: public SceneNode {
		friend class GenericScene;
	public:
		// Map of children
		typedef map<string, GenericNode *> children_map_type;

		// List of active nodes (used by generic scene)
		typedef list<GenericNode *> active_nodes_type;

		// List of attached objects
		typedef vector<DrawableObject *> attached_objects_type;

	protected:
		// Characteristics of this node

		//! Data of a light
		Light m_light;

		//! A pointer to our generic scene
		GenericScene * pGenericScene;

		//! Position of node
		Vector3 v3_position;

		//! Scale factor of node
		Vector3 v3_scale;

		//! Orientation of node
		Quaternion qu_orientation;

		//! Name of node
		string mName;

		//! An array with objects
		attached_objects_type v_attachedObjects;

		//! A sub list with transparent objects
		attached_objects_type v_attachedTransObjects;

		//! Cached global position
		Vector3 v3_gposition;

		//! Cached global orientation
		Quaternion qu_gorientation;

		//! At which render loop it was cached
		unsigned long cCachedGlobalLoop;

		/**@brief Iterator at the list of our selfs in the
		 list of active nodes at our SceneManager	*/
		active_nodes_type::iterator ActiveNodes_myiterator;

		//! Iterator at the list of nodes with active light
		vector<GenericNode *>::iterator LightNodes_myiterator;

		bool f_scale; 					//!< A flag showing if node has scaling attributes
		GenericNode * pParentNode; 		//!< Pointer to parent node
		children_map_type v_children;	//!< Map with children nodes

		// Draw all the objects of this node
		void drawObjects(bool bSolid);

		// Check if it has transparent objects
		inline bool hasTransperantObjects() {
			return (v_attachedTransObjects.size() > 0);
		}

		//! Constructor for child nodes
		GenericNode(const string & name, GenericNode * parent, const Vector3 & pos);

		//! Constructor for root node
		GenericNode(const string & name, SceneManager * pmanager);

		//! Hide destructor so that it is not destructable from the public scope
		~GenericNode();

		//! Internal implementation of calculate global position and orientation
		void _updateCachedGPos_GOrient(unsigned long cur_renderloop);

	public:
		using SceneNode::attachObject;

		// Implementation
		virtual void useme_to_glPosition();

		// Implementation
		virtual void useme_to_glInvertPosition();

		// Implementation
		virtual bool removeObject(DrawableObject * p_object);

		// Implementation
		virtual void attachObject(DrawableObject * p_object);

		// Implementation
		virtual Quaternion & getGlobalOrientation();

		// Implementation
		virtual Vector3 & getGlobalPosition();

		// Get the parent node of this node
		inline GenericNode * getParentNodePtr() {
			return pParentNode;
		}

		//! Create a child node
		inline GenericNode * createChild(const string & name, const Vector3 & pos =
				Vector3::ZERO) {
			GenericNode * pchild_node = new GenericNode(name, this, pos);
			v_children[name] = pchild_node;
			return pchild_node;
		}

		//! Delete a child node
		bool deleteChild(const string & child_name);

		// Get the name of this node
		inline const string & getName() const {
			return mName;
		}

		// Get the children of this node
		inline children_map_type & getChildren() {
			return v_children;
		}

		// Get a specific child
		inline GenericNode * getChildPtr(const string & child_name) {
			children_map_type::iterator it = v_children.find(child_name);

			if (it != v_children.end())
				return it->second;
			else
				return NULL;
		}

		// Translate node
		inline void translate(const Vector3 & trans) {
			v3_position += trans;
		}

		// Rotate node
		inline void rotate(const Quaternion & rot) {
			qu_orientation *= rot;
		}

		// Yaw node
		inline void yaw(const Angle & angle) {
			qu_orientation *= Quaternion(Vector3::NEGATIVE_UNIT_Y, angle);
		}

		// Roll node
		inline void roll(const Angle & angle) {
			qu_orientation *= Quaternion(Vector3::UNIT_Z, angle);
		}

		// Pitch node
		inline void pitch(const Angle & angle) {
			qu_orientation *= Quaternion(Vector3::NEGATIVE_UNIT_X, angle);
		}

		// Get position of node
		inline Vector3 & getPosition() {
			return v3_position;
		}

		// Set position of node
		inline Vector3 & setPosition(const Vector3 & pos) {
			return v3_position = pos;
		}

		// Get orientation of node
		inline Quaternion & getOrientation() {
			return qu_orientation;
		}

		// Set orientation of node
		inline Quaternion & setOrientation(const Quaternion & orient) {
			return qu_orientation = orient;
		}

		//! Set a light on this node
		/**
		 To disable light on this node, set a light which is disabled
		 */
		void setLight(const Light & light);

		//! Get the light of this node
		inline const Light & getLight() const {
			return m_light;
		}
	};
}

#endif
