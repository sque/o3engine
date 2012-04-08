#include "./genericnode.hpp"
#include "./genericscene.hpp"
#include <algorithm>

namespace o3engine {
	GenericNode::GenericNode(const string & name, GenericNode * parent,
			const Vector3 & pos) :
			SceneNode(parent->getMySceneManager()),
			m_position(pos),
			m_scale(Vector3::IDENTITY),
			m_orientation(Quaternion::IDENTITY),
			m_name(name),
			mp_parent(parent) {
		// Initialize variables
		m_cached_global_loop = 0;
		mp_scene = dynamic_cast<GenericScene *>(mp_scene_manager);
	}

	// Constructor for root node
	GenericNode::GenericNode(const string & name, SceneManager * pmanager) :
			SceneNode(pmanager),
			m_position(Vector3::ZERO),
			m_scale(Vector3::IDENTITY),
			m_orientation(Quaternion::IDENTITY),
			m_name(name),
			mp_parent(nullptr) {
		// Initialize variables
		m_cached_global_loop = 0;
		mp_scene = dynamic_cast<GenericScene *>(mp_scene_manager);
	}

	GenericNode::~GenericNode() {
		children_map_type::iterator it;

		// Dettach cameras, lights
		detachCamera();

		// Remove our-selfs from active nodes list
		if (m_attached_objects.size() > 0)
			mp_scene->unregisterNodeWithObjects(ActiveNodes_myiterator);

		// Remove our-selfs from light nodes list
		if (m_light.isEnabled())
			mp_scene->m_light_nodes.erase(LightNodes_myiterator);

		// Delete all children
		while ((it = m_children.begin()) != m_children.end()) {
			delete it->second;
			m_children.erase(it);
		}

	}

	bool GenericNode::deleteChild(const string & child_name) {
		children_map_type::iterator it;

		if ((it = m_children.find(child_name)) == m_children.end())
			return false;

		delete it->second;
		m_children.erase(it);
		return true;
	}

	bool GenericNode::removeObject(DrawableObject * p_object) {
		attached_objects_type::iterator it;

		// Erase from main list
		if (m_attached_objects.end()
				== (it = find(m_attached_objects.begin(), m_attached_objects.end(),
						p_object)))
			return false; // Not found

		m_attached_objects.erase(it);

		// Remove this from active objects list
		if (m_attached_objects.size() == 0)
			mp_scene->unregisterNodeWithObjects(ActiveNodes_myiterator);
		return true;
	}

	void GenericNode::attachObject(DrawableObject * p_object) {
		if (!p_object)
			return;

		// Add to the list of attached objects
		m_attached_objects.push_back(p_object);

		// If it is the first attached object, then register as active
		if (m_attached_objects.size() == 1)
			ActiveNodes_myiterator = mp_scene->registerNodeWithObjects(this);
	}

	// Internal implementation of getting global position an orientation
	void GenericNode::_updateCachedGPos_GOrient(unsigned long cur_renderloop) {
		// Skip cached
		if (cur_renderloop == m_cached_global_loop)
			return;
		else
			m_cached_global_loop = cur_renderloop;

		if (mp_parent) {
			mp_parent->_updateCachedGPos_GOrient(cur_renderloop);
			m_gorientation = mp_parent->m_gorientation * m_orientation;
			m_gposition = mp_parent->m_gposition
					+ (mp_parent->m_gorientation * m_position);
		} else {
			m_gorientation = m_orientation;
			m_gposition = m_position;
		}
		m_gtransformation = Matrix4::IDENTITY;
		m_gtransformation = m_gorientation.toMatrix();
		m_gtransformation.setTranslation(m_gposition);
	}

	Quaternion & GenericNode::getGlobalOrientation() {
		_updateCachedGPos_GOrient(mp_scene->m_loop_counter);
		return m_gorientation;
	}

	Vector3 & GenericNode::getGlobalPosition() {
		_updateCachedGPos_GOrient(mp_scene->m_loop_counter);
		return m_gposition;
	}

	Matrix4 & GenericNode::getGlobalTransformation() {
		_updateCachedGPos_GOrient(mp_scene->m_loop_counter);
		return m_gtransformation;
	}

	void GenericNode::drawObjects(SceneRendererVisitor * pvisitor) {
		attached_objects_type::iterator it;

		for (auto & obj : m_attached_objects) {
			obj->draw(pvisitor);
		}
	}

	void GenericNode::setLight(const Light & light) { // Remove the previous iterator
		if (m_light.isEnabled())
			mp_scene->m_light_nodes.erase(LightNodes_myiterator);

		m_light = light;
		if (m_light.isEnabled()) {

			LightNodes_myiterator = mp_scene->m_light_nodes.insert(
					mp_scene->m_light_nodes.begin(), this);
		}
	}
}
