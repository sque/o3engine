#ifndef O3ENGINE_GENERICSCENE_HPP_INCLUDED
#define O3ENGINE_GENERICSCENE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./genericnode.hpp"
#include "./scenemanager.hpp"
#include "./drawableobject.hpp"

#include <list>

namespace o3engine
{
    //! Implementation of a general purpose SceneManager
    /**
        GenericScene is a SceneManager with no specific optimization, it is
        designed as a general purpose scene manager that uses ierarchical
        tree to organize nodes and supports some basic optimization like
        position caching, scene clipping and far distance cut off.
        It has support of lighting using basic openGL lighting features.
    */
	class GenericScene : public SceneManager
	{
	friend class GenericNode;
	protected:
		GenericNode * mp_root_node;                 //!< Pointer to root node
		GenericNode::ActiveNodesT mv_activenodes;   //!< A list of nodes that have drawable objects
		size_t m_loop_counter;				        //!< A counter of render loops
		Real m_farcutoff_distance;				    //!< Max distance of far cut off algorithm
		Real m_farcutoff_sqdistance;				//!< Squared max distance of far cut off algorithm
		bool m_enabled_far_cutoff;					//!< Cut off far objects
		bool m_enabled_clipping;					//!< Selective render of viewable objects only
		Color m_ambient_light;                      //!< Ambient light of the scene

		//! A termporary per/render loop list of transperant objects
		vector<GenericNode *>mv_trans_nodes;

		//! A list of nodes that contain lights
		vector<GenericNode *>mv_light_nodes;

		//! Register a node as an active node (a node that containes at least one object)
		inline GenericNode::ActiveNodesIterator registerNodeWithObjects(GenericNode * pnode)
		{	return mv_activenodes.insert(mv_activenodes.begin(), pnode);	}

		//! Unregister a node from active nodes
		inline void unregisterNodeWithObjects(GenericNode::ActiveNodesIterator pit)
		{	mv_activenodes.erase(pit);	}

	public:
		//! Constructor
		GenericScene();

		//! Destructor
		virtual ~GenericScene();

		//! Get root node of scene by reference
		inline GenericNode & getRootNode()
		{	return * mp_root_node;	}

		//! Set far cut off threshold
		inline void setFarCutOffThresshold(Real distance)
		{	m_farcutoff_distance = distance;
		    m_farcutoff_sqdistance = m_farcutoff_distance * m_farcutoff_distance;
        }

		//! Get far cut off threshold distance
		inline Real getFarCutOffThreshold() const
		{	return m_farcutoff_distance;	}

		//! Enable/disable far cut off
		inline void setFarCutOffState(bool enabled)
		{	m_enabled_far_cutoff = enabled;	}

		//! Check if far cutoff is enabled
		inline bool isFarCutOffEnabled() const
		{	return m_enabled_far_cutoff;	}

		//! Enable/Disable scene clipping scene clipping
		inline void setSceneClipped(bool enabled)
		{	m_enabled_clipping = enabled;	}

		//! Check if scene clipping is enabled
		inline bool isSceneClipped() const
		{	return m_enabled_clipping;	}

		//! Set the ambient light of the scene
		inline void setAmbientLight(const Color &ambient)
		{   m_ambient_light = ambient;  }

		//! Get the ambient light of the scene
		inline const Color & getAmbientLight() const
		{   return m_ambient_light; }

		virtual void drawScene(Camera * pRenderCamera);
	};
}
#endif
