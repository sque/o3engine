#ifndef O3ENGINE_GENERICSCENE_HPP_INCLUDED
#define O3ENGINE_GENERICSCENE_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./genericnode.hpp"
#include "./scenemanager.hpp"
#include "./drawableobject.hpp"

#include <list>

namespace o3engine {

	//! Implementation of a general purpose SceneManager
	/**
	 * GenericScene is a SceneManager with no specific optimization, it is
	 * designed as a general purpose scene manager that uses hierarchical
	 * tree to organize nodes and supports some basic optimization like
	 * position caching, scene clipping and far distance cut off.
	 */
	class GenericScene: public SceneManager {
		friend class GenericNode;
	protected:
		//! Pointer to root node
		GenericNode * mp_root_node;

		//! A list of nodes that have drawable objects
		GenericNode::active_nodes_type m_activenodes;

		//! A counter of render loops
		size_t m_loop_counter;

		//! Max distance of far cut off algorithm
		Real m_farcutoff_distance;

		//! Squared max distance of far cut off algorithm
		Real m_farcutoff_sqdistance;

		//! Cut off far objects
		bool m_enabled_far_cutoff;

		//! Selective render of viewable objects only
		bool m_enabled_clipping;

		//! Ambient light of the scene
		Color m_ambient_light;

		//! A list of nodes that contain lights
		vector<GenericNode *> m_light_nodes;

		//! Register a node as an active node (a node that contains at least one object)
		inline GenericNode::active_nodes_type::iterator registerNodeWithObjects(
				GenericNode * pnode) {
			return m_activenodes.insert(m_activenodes.begin(), pnode);
		}

		//! Unregister a node from active nodes
		inline void unregisterNodeWithObjects(
				GenericNode::active_nodes_type::iterator pit) {
			m_activenodes.erase(pit);
		}

	public:
		//! Constructor
		GenericScene();

		//! Destructor
		virtual ~GenericScene();

		GenericNode::active_nodes_type & getActiveNodes() {
			return m_activenodes;
		}

		//! Get root node of scene by reference
		inline GenericNode & getRootNode() {
			return *mp_root_node;
		}

		//! Set far cut off threshold
		inline void setFarCutOffThresshold(Real distance) {
			m_farcutoff_distance = distance;
			m_farcutoff_sqdistance = m_farcutoff_distance * m_farcutoff_distance;
		}

		//! Get far cut off threshold distance
		inline Real getFarCutOffThreshold() const {
			return m_farcutoff_distance;
		}

		//! Enable/disable far cut off
		inline void setFarCutOffState(bool enabled) {
			m_enabled_far_cutoff = enabled;
		}

		//! Check if far cutoff is enabled
		inline bool isFarCutOffEnabled() const {
			return m_enabled_far_cutoff;
		}

		//! Enable/Disable scene clipping scene clipping
		inline void setSceneClipped(bool enabled) {
			m_enabled_clipping = enabled;
		}

		//! Check if scene clipping is enabled
		inline bool isSceneClipped() const {
			return m_enabled_clipping;
		}

		//! Set the ambient light of the scene
		inline void setAmbientLight(const Color &ambient) {
			m_ambient_light = ambient;
		}

		//! Get the ambient light of the scene
		inline const Color & getAmbientLight() const {
			return m_ambient_light;
		}

		size_t nextLoopCounterToBeChangedUglyFunction();

		template<class Visitor>
		void navigateActiveObjects(Visitor & visitor) {
			for(auto & n: m_activenodes) {
				visitor.visitNode(n);
				for(auto & o : n->getObjects()) {
					visitor.visitObject(n, o);
				}
			}
		}
	};
}
#endif
