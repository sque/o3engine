#ifndef O3ENGINE_GENERICNODE_HPP_INCLUDED
#define O3ENGINE_GENERICNODE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./scenenode.hpp"
#include "./light.hpp"

#include <map>
#include <list>
#include <vector>

namespace o3engine {

	//! Placeholder for SceneRenderState concept
	struct SceneRendererConcept {
		void populateGlobalStateUniforms(ogl::program * program);

		ogl::buffer & getGlobalUniformBuffer();
	};

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
		GenericScene * mp_scene;

		//! Position of node
		Vector3 m_position;

		//! Scale factor of node
		Vector3 m_scale;

		//! Orientation of node
		Quaternion m_orientation;

		//! Name of node
		string m_name;

		//! An array with objects
		attached_objects_type m_attached_objects;

		//! Cached global position
		Vector3 m_gposition;

		//! Cached global orientation
		Quaternion m_gorientation;

		//! Cached global transformation
		Matrix4 m_gtransformation;

		//! At which render loop it was cached
		unsigned long m_cached_global_loop;

		/**@brief Iterator at the list of our selfs in the
		 list of active nodes at our SceneManager	*/
		active_nodes_type::iterator ActiveNodes_myiterator;

		//! Iterator at the list of nodes with active light
		vector<GenericNode *>::iterator LightNodes_myiterator;

		bool m_has_scale;				//!< A flag showing if node has scaling attributes
		GenericNode * mp_parent; 		//!< Pointer to parent node
		children_map_type m_children;	//!< Map with children nodes

		//! Constructor for child nodes
		GenericNode(const string & name, GenericNode * parent, const Vector3 & pos);

		//! Constructor for root node
		GenericNode(const string & name, SceneManager * pmanager);

		//! Hide destructor so that it is not destructable from the public scope
		~GenericNode();

	public:
		//! Internal implementation of calculate global position and orientation
				void _updateCachedGPos_GOrient(unsigned long cur_renderloop);

		using SceneNode::attachObject;

		virtual bool removeObject(DrawableObject * p_object);

		virtual void attachObject(DrawableObject * p_object);

		attached_objects_type & getObjects() {
			return m_attached_objects;
		}

		virtual Quaternion & getGlobalOrientation();

		virtual Vector3 & getGlobalPosition();

		virtual Matrix4 & getGlobalTransformation();

		// Get the parent node of this node
		inline GenericNode * getParentNodePtr() {
			return mp_parent;
		}

		//! Create a child node
		inline GenericNode * createChild(const string & name, const Vector3 & pos =
				Vector3::ZERO) {
			GenericNode * pchild_node = new GenericNode(name, this, pos);
			m_children[name] = pchild_node;
			return pchild_node;
		}

		//! Delete a child node
		bool deleteChild(const string & child_name);

		// Get the name of this node
		inline const string & getName() const {
			return m_name;
		}

		// Get the children of this node
		inline children_map_type & getChildren() {
			return m_children;
		}

		// Get a specific child
		inline GenericNode * getChildPtr(const string & child_name) {
			children_map_type::iterator it = m_children.find(child_name);

			if (it != m_children.end())
				return it->second;
			else
				return nullptr;
		}

		// Translate node
		inline void translate(const Vector3 & trans) {
			m_position += trans;
		}

		// Rotate node
		inline void rotate(const Quaternion & rot) {
			m_orientation *= rot;
		}

		// Yaw node
		inline void yaw(const Angle & angle) {
			m_orientation *= Quaternion(Vector3::NEGATIVE_UNIT_Y, angle);
		}

		// Roll node
		inline void roll(const Angle & angle) {
			m_orientation *= Quaternion(Vector3::UNIT_Z, angle);
		}

		// Pitch node
		inline void pitch(const Angle & angle) {
			m_orientation *= Quaternion(Vector3::NEGATIVE_UNIT_X, angle);
		}

		// Get position of node
		inline const Vector3 & getPosition() const{
			return m_position;
		}

		// Set position of node
		inline Vector3 & setPosition(const Vector3 & pos) {
			return m_position = pos;
		}

		// Get orientation of node
		inline const Quaternion & getOrientation() const{
			return m_orientation;
		}

		// Set orientation of node
		inline Quaternion & setOrientation(const Quaternion & orient) {
			return m_orientation = orient;
		}

		//! Draw all the objects of this node
		void drawObjects(SceneRendererVisitor * pvisitor);

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
