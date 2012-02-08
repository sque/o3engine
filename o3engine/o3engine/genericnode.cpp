#include "./genericnode.hpp"
#include "./genericscene.hpp"
#include <algorithm>

// #define GENERICNODE_DEBUG_LINES    // Enable this to see debug lines of nodes

namespace o3engine
{
	GenericNode::GenericNode(const string & name, GenericNode * parent, const Vector3 & pos)
		:SceneNode(parent->getMySceneManager()),
		v3_position(pos),
		v3_scale(Vector3::IDENTITY),
		qu_orientation(Quaternion::IDENTITY),
		mName(name),
		pParentNode(parent)
	{
		// Initialize variables
		cCachedGlobalLoop = 0;
		pGenericScene = (GenericScene *) pSceneManager;
	}

	// Constructor for root node
	GenericNode::GenericNode(const string & name, SceneManager * pmanager)
		:SceneNode(pmanager),
		v3_position(Vector3::ZERO),
		v3_scale(Vector3::IDENTITY),
		qu_orientation(Quaternion::IDENTITY),
		mName(name),
		pParentNode(NULL)
	{
		// Initialize variables
		cCachedGlobalLoop = 0;
		pGenericScene = (GenericScene *) pSceneManager;
	}

	GenericNode::~GenericNode()
	{	ChildIterator it;

		// Dettach cameras, lights
		dettachCamera();

		// Remove our-selfs from active nodes list
		if (v_attachedObjects.size() > 0)
			pGenericScene->unregisterNodeWithObjects(ActiveNodes_myiterator);

        // Remove our-selfs from light nodes list
        if (m_light.isEnabled())
            pGenericScene->mv_light_nodes.erase(LightNodes_myiterator);

		// Delete all childs
		while((it = v_childs.begin()) != v_childs.end())
		{
			delete it->second;
			v_childs.erase(it);
		}


	}

	void GenericNode::useme_to_glPosition()
	{
		if (pParentNode)
			pParentNode->useme_to_glPosition();

	#ifdef GENERICNODE_DEBUG_LINES
		glDisable(GL_LIGHTING);
		glColor3(Color::WHITE);
		glBegin(GL_LINES);
			glVertex3f(0,0,0);
			glVertex(v3_position);
		glEnd();
		glTranslate(v3_position);
		glRotate(qu_orientation);
		glColor3(Color(1,0.9,0));
		glBegin(GL_POLYGON);
			glVertex3f(-0.5, 0, -0.5);
			glVertex3f(-0.5, 0, 0.5);
			glVertex3f(0.5, 0, 0.5);
			glVertex3f(0.5, 0, -0.5);
		glEnd();
		glEnable(GL_LIGHTING);
	#else
		glTranslate(v3_position);
		glRotate(qu_orientation);
	#endif

		if (f_scale)
			glScale(v3_scale);
	}

	void GenericNode::useme_to_glInvertPosition()
	{
		glRotate(qu_orientation.conjugate());
		glTranslate(v3_position.opposite());

		if (pParentNode)
			pParentNode->useme_to_glInvertPosition();
	}

	bool GenericNode::deleteChild(const string & child_name)
	{	ChildIterator it;

		if ((it = v_childs.find(child_name)) == v_childs.end())
			return false;

		delete it->second;
		v_childs.erase(it);
		return true;
	}

	bool GenericNode::removeObject(DrawableObject * p_object)
	{	AttachedObjectsIterator it;

		// Erase from main list
		if (v_attachedObjects.end() == (it = find(v_attachedObjects.begin(), v_attachedObjects.end(), p_object)))
			return false;	// Not found

		v_attachedObjects.erase(it);

		// Search in transperant list
		if (v_attachedTransObjects.end() != (it = find(v_attachedTransObjects.begin(), v_attachedTransObjects.end(), p_object)))
			v_attachedTransObjects.erase(it);

		// Remove this from active objects list
		if (v_attachedObjects.size() == 0)
			pGenericScene->unregisterNodeWithObjects(ActiveNodes_myiterator);
		return true;
	}

	void GenericNode::attachObject(DrawableObject * p_object)
	{	if (!p_object)
			return;

		// Add to the list of attached objects
		v_attachedObjects.push_back(p_object);

		if (p_object->hasTransperant())
			v_attachedTransObjects.push_back(p_object);

		// If it is the first attached object, then register as active
		if (v_attachedObjects.size() ==1)
			ActiveNodes_myiterator = ((GenericScene *)pSceneManager)->registerNodeWithObjects(this);
	}

	// Internal implementation of getting global position an orientation
	void GenericNode::_updateCachedGPos_GOrient(unsigned long cur_renderloop)
	{
		// Skip cached
		if (cur_renderloop == cCachedGlobalLoop)
			return;
		else
			cCachedGlobalLoop = cur_renderloop;

		if (pParentNode)
		{
			pParentNode->_updateCachedGPos_GOrient(cur_renderloop);
			qu_gorientation = pParentNode->qu_gorientation * qu_orientation;
			v3_gposition = pParentNode->v3_gposition + (pParentNode->qu_gorientation * v3_position);
		}
		else
		{
			qu_gorientation = qu_orientation;
			v3_gposition = v3_position;
		}
	}

	Quaternion & GenericNode::getGlobalOrientation()
	{	if (cCachedGlobalLoop != pGenericScene->m_loop_counter)
			_updateCachedGPos_GOrient(pGenericScene->m_loop_counter);
		return qu_gorientation;
	}

	Vector3 & GenericNode::getGlobalPosition()
	{	if (cCachedGlobalLoop != pGenericScene->m_loop_counter)
			_updateCachedGPos_GOrient(pGenericScene->m_loop_counter);
		return v3_gposition;
	}

	void GenericNode::drawObjects(bool bSolid)
	{	AttachedObjectsIterator it;

		if (bSolid)
		{
			for(it = v_attachedObjects.begin();it != v_attachedObjects.end();it++)
				(*it)->drawSolidPart();
		}
		else
		{
			for(it = v_attachedTransObjects.begin();it != v_attachedTransObjects.end();it++)
				(*it)->drawTransperantPart();
		}
	}

	void GenericNode::setLight(const Light & light)
    {   // Remove the previous iterator
        if (m_light.isEnabled())
            pGenericScene->mv_light_nodes.erase(LightNodes_myiterator);

        m_light = light;
        if (m_light.isEnabled())
        {

            LightNodes_myiterator = pGenericScene->mv_light_nodes.insert(pGenericScene->mv_light_nodes.begin(), this);
        }
    }
}
