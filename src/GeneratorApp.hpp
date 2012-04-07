/*
 * app.hpp
 *
 *  Created on: Feb 8, 2012
 *      Author: sque
 */

#ifndef APP_HPP_
#define APP_HPP_

#include <o3engine/o3engine.hpp>
#include <o3engine/genericscene.hpp>
#include <o3engine/orthocamera.hpp>
#include <o3engine/perspectivecamera.hpp>
#include <o3engine/primitiveshapes.hpp>
#include <o3engine/renderline/textureoutput.hpp>
#include <o3engine/renderline/viewportoutput.hpp>
#include <o3engine/mesh.hpp>
#include <iostream>
#include <fstream>
#include <boost/format.hpp>

using namespace std;
using namespace o3engine;


class FrameProcessor: public FrameListener, public KeyboardListener, public MouseListener {
public:
	int count;
	GenericScene * pscene;
	RenderLine::TextureOutput * pouttex;
	FrameProcessor() {
		count = 0;
	}

	virtual void onRenderInterval(Real secs) {
		count++;
		if (count % 100 == 0) {
			cout << boost::format("FPS: %f.")
				% O3Engine::getSingleton().getFps() << endl;

		}
		pscene->getRootNode().getChildPtr("model")->rotate(Quaternion(Vector3::UNIT_Y, Radian(M_PI * secs)));

	}

	//! Raised when a keyboard key is released
	inline virtual void onKeyboardButtonReleased(E_KB_VIRTUALKEYS vt_key) {
		Image img;
		switch (vt_key) {
		case KB_VTKEY_ESC:
			exit(0);
			break;
		case KB_VTKEY_UP:
			pscene->getRootNode().getChildPtr("model")->rotate(Quaternion(Vector3::UNIT_X, Degree(10)));
			break;
		case KB_VTKEY_DOWN:
			pscene->getRootNode().getChildPtr("model")->rotate(Quaternion(Vector3::NEGATIVE_UNIT_X, Degree(10)));
			break;
		case KB_VTKEY_LEFT:
			pscene->getRootNode().getChildPtr("model")->rotate(Quaternion(Vector3::NEGATIVE_UNIT_Y, Degree(10)));
			break;
		case KB_VTKEY_RIGHT:
			pscene->getRootNode().getChildPtr("model")->rotate(Quaternion(Vector3::UNIT_Y, Degree(10)));
			break;
		case KB_VTKEY_SPACE:
			if (O3Engine::getSingleton().isFrameListenersPaused()) {
				O3Engine::getSingleton().unpauseFrameListeners();
			} else {
				O3Engine::getSingleton().pauseFrameListeners();
			}
			return;
			img = TextureManager::getObject("00_rtt").downloadImage();
			cout << boost::format("Got image %1%x%2%") % img.getWidth() % img.getHeight() << endl;
			img.saveImageAsPNG("test.png");
			break;
		default:
			std::cout << "Pressed a key!" << vt_key << std::endl;
			break;
		}
	}

	virtual void onMouseMove(const MouseEvent & e) {
		std::cout << "Moved mouse! " << e.m_rel_x << " " << e.m_rel_y << std::endl;

		if (e.ms_mouse_state.isAnyButtonDown()) {
			pscene->getRootNode().getChildPtr("camera-base")->yaw(Degree(e.m_rel_x));
		}
	}

	//! Raised when a button was released
	virtual void onMouseButtonReleased(const MouseEvent & e) {
		if (e.m_trigger_button == E_MS_BUTTONS::MS_BUTTON_WHEELUP) {
			pscene->getRootNode().getChildPtr("camera-base")->getChildPtr("camera")->translate(Vector3(0,0,-1));
		} else if (e.m_trigger_button == E_MS_BUTTONS::MS_BUTTON_WHEELDOWN) {
			pscene->getRootNode().getChildPtr("camera-base")->getChildPtr("camera")->translate(Vector3(0,0, 1));
		}
	}

};

struct MyCube : public Mesh {

	MyCube(const std::string & name) :
		Mesh(name){

		SubMesh sm(VertexAttributes::position);
		Vertex vx;
		memset(&vx, 0 , sizeof(Vertex));
		vx.position = Vector3(0, 0, 0);
		sm.vertices().push_back(vx);
		vx.position = Vector3(1, 0, 0);
		sm.vertices().push_back(vx);
		vx.position = Vector3(1, 1, 0);
		sm.vertices().push_back(vx);

		sm.indices() = {0, 1, 2};
		submeshes().push_back(sm);
	}
};

class GeneratorApp {
public :
	O3Engine m_engine;
	GeneratorApp() {
		// Start engine
		m_engine.init(0, NULL);
	}

	void start() {
		//pcache_manager = new ResourceCacheManager();

		// Set up window
		o3engine::Window wnd_main(800, 600);
		wnd_main.setTitle("hy672 Project");
		wnd_main.setBackColor(Color(0.7, 0.72, 0.80));

		/*o3engine::Window wnd_bc(640, 480);
		wnd_bc.setTitle("Ortho");
		wnd_bc.setBackColor(Color(0.8, 0.8, 0.8, 1));*/

		//OffScreen off_scrn(320, 240);
		//RenderLine::TextureOutput * pouttex = new RenderLine::TextureOutput(off_scrn, true);
		RenderLine::ViewportOutput * pmainout = new RenderLine::ViewportOutput(wnd_main, 800, 600, 0, 0);
		//RenderLine::ViewportOutput * pbcout = new RenderLine::ViewportOutput(wnd_bc, 800, 600, 0, 0);
		Camera * perscam = new PerspectiveCamera(Degree(45), 1, 0.1, 1000);
		//OrthoCamera * orthcam = new OrthoCamera(4, 3, 0, 1000);

		Mesh * spacecrap = new Mesh("spacecrap");
		//spacecrap->uploadToGPU();
		spacecrap->importFromFile("house.dae");
		std::cout << info(*spacecrap) << std::endl;

		pmainout->attachNode(perscam);
		//pbcout->attachNode(orthcam);

		FrameProcessor fp;
		fp.enableFrameListening();
		/*wnd_bc.getInputProcessor().attachKeyboardListener(fp);
		wnd_bc.getInputProcessor().startCapturing();*/
		wnd_main.getInputProcessor().attachKeyboardListener(fp);
		wnd_main.getInputProcessor().attachMouseListener(fp);
		wnd_main.getInputProcessor().startCapturing();

		GenericScene sm;
		fp.pscene =  &sm;
		//fp.pouttex = pouttex;
		sm.setFarCutOffState(false);
		sm.setSceneClipped(false);
		sm.setAmbientLight(Color::BLACK);

		sm.getRootNode().createChild("model")->attachObject(spacecrap);
		sm.getRootNode().createChild("camera-base")->createChild("camera", Vector3(0, 0, 10))->attachCamera(perscam);
		//sm.getRootNode().getChildPtr("camera")->createChild("2ndview")->attachCamera(orthcam);
		sm.getRootNode().getChildPtr("camera-base")->getChildPtr("camera")->setLight(*new Light());

		//m_engine.getPlatformManager().disableVSync();
		m_engine.getPlatformManager().enableVSync();
		m_engine.startRendering();
//		while(1) {
//			sm.getRootNode().getChildPtr("model")->rotate(Quaternion(Vector3::UNIT_Y, Degree(30)));
//			m_engine.renderOneFrame();
//			sleep(1);
//		}
	}

};

#endif /* APP_HPP_ */
