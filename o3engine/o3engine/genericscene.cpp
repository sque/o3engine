#include "./genericscene.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


namespace o3engine
{
	// Constructor
	GenericScene::GenericScene() {
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
	GenericScene::~GenericScene() {
		delete mp_root_node;
	}


	size_t GenericScene::nextLoopCounterToBeChangedUglyFunction() {
		return m_loop_counter++;	// Increase counter
	}
}
