#include "./genericscene.hpp"

namespace o3engine
{
	// Constructor
	GenericScene::GenericScene()
	{
		// Initialize variable
		m_loop_counter = 0;
		m_farcutoff_distance = 1000;
		m_farcutoff_sqdistance = m_farcutoff_distance * m_farcutoff_distance;
		m_enabled_far_cutoff = true;
		m_enabled_clipping = true;
		m_ambient_light = Color(0.2, 0.2, 0.2, 1);

		// Create root node
		mp_root_node = new GenericNode("root", this);
	}

	// Destructor
	GenericScene::~GenericScene()
	{
		// Delete root node
		delete mp_root_node;
	}

	void GenericScene::drawScene(Camera * pRenderCamera)
	{	m_loop_counter++;	// Increase counter
		Real camFovRad = math::degreeToRadian(pRenderCamera->getFovY());
		Real rad90Deg = math::degreeToRadian(90);

		// Iterators
		GenericNode::ActiveNodesIterator it;
		vector<GenericNode*>::iterator transIt;
		vector<GenericNode*>::iterator lightIt;

		// Camera's global position
		Quaternion camera_gorientation_ops = pRenderCamera->getAttachedNode()->getGlobalOrientation().conjugate();
		Vector3 camera_gposition = pRenderCamera->getAttachedNode()->getGlobalPosition();
		GenericNode * pnode;
		Vector3 camera_relpos;

		// Render Lighting
		//! @todo Write a better implementation of lighting
		glEnable(GL_LIGHTING);
        glLightModel(GL_LIGHT_MODEL_AMBIENT, m_ambient_light);
		GLint el = 0;
		for(lightIt = mv_light_nodes.begin();lightIt != mv_light_nodes.end(); lightIt++)
        {   pnode = (*lightIt);
            // Update global positions/orientation
			pnode->_updateCachedGPos_GOrient(m_loop_counter);

			glPushMatrix();
                glTranslate(pnode->v3_gposition);
				glRotate(pnode->qu_gorientation);
                glLight((*lightIt)->getLight(), GL_LIGHT0 + el);
			glPopMatrix();
            el++;
        }

		// Render 1st Pass (Solid Objects)
		mv_trans_nodes.clear();
		for(it = mv_activenodes.begin();it != mv_activenodes.end(); it++)
		{	pnode = *it;

			// Update global positions/orientation
			pnode->_updateCachedGPos_GOrient(m_loop_counter);

			camera_relpos = camera_gorientation_ops * (pnode->v3_gposition - camera_gposition);

			// Scene angle clipping
			if ((m_enabled_clipping) &&
				(	(camera_relpos.z >= 0) || 	// Fast reject behind XY plane
                     ((rad90Deg - math::arcSin(-camera_relpos.normal().z)) > camFovRad) ))	// Reject by camera's angle
				continue;

			// Limit distance clipping
			if ((m_enabled_far_cutoff) && (camera_relpos.squaredLength() > m_farcutoff_sqdistance))
				continue;

			glPushMatrix();
                glTranslate(pnode->v3_gposition);
				glRotate(pnode->qu_gorientation);
				pnode->drawObjects(true);
			glPopMatrix();

			// Add node if needed at 2n pass rendering
			if (pnode->hasTransperantObjects())
				mv_trans_nodes.push_back(pnode);
		}

		// Render 2nd Pass (Transperant objects)
		for(transIt = mv_trans_nodes.begin();transIt != mv_trans_nodes.end();transIt++)
		{	pnode = *transIt;

			glPushMatrix();
				glTranslate(pnode->v3_gposition);
				glRotate(pnode->qu_gorientation);
				pnode->drawObjects(false);
			glPopMatrix();
		}
	}
}
