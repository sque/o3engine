#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED

#include "./prereqs.hpp"

namespace o3engine
{
	//! Generic SceneManager
	class SceneManager
	{
	public:
		virtual ~SceneManager(){}

		virtual void drawScene(Camera * pRenderCamera) = 0;
	};
}
#endif // SCENEMANAGER_H_INCLUDED
