#include "./camera.hpp"
#include "./scenemanager.hpp"
#include "./scenenode.hpp"

namespace o3engine {

	Camera::~Camera() {
		if (mp_scene_node)
			mp_scene_node->detachCamera();
	}

	void Camera::render() {

		if (mp_scene_node) {
			mp_scene_node->getMySceneManager()->drawScene(this);
		}
		renderNext();
	}



}
