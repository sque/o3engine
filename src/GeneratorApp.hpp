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

		pscene->getRootNode().getChildPtr("model")->rotate(Quaternion(Vector3::UNIT_Y,Radian(M_PI * secs)));

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
		wnd_main.setBackColor(Color::WHITE);

		/*o3engine::Window wnd_bc("bc", 640, 480);
		wnd_bc.setTitle("Backup window");
		wnd_bc.setBackColor(Color::YELLOW);*/

		//OffScreen off_scrn(320, 240);
		//RenderLine::TextureOutput * pouttex = new RenderLine::TextureOutput(off_scrn, true);
		RenderLine::ViewportOutput * pout = new RenderLine::ViewportOutput(wnd_main, 800, 600, 0, 0);
		Camera * pcam = new PerspectiveCamera(60, 4/3, 0, 1000);
		OrthoCamera * pcam2 = new OrthoCamera(4, 3, 0, 1000);

		//pouttex->attachNode(*pcam);
		//pout->setInputCamera(pcam2);
		//pout->enableRendering();
		pout->attachNode(pcam);


		//pout->attachNode(&ap);
		//ap.attachNode(pcam);

		FrameProcessor fp;
		fp.enableFrameListening();
		/*wnd_bc.getInputProcessor().attachKeyboardListener(fp);
		wnd_bc.getInputProcessor().startCapture();*/
		/*wnd_main.getInputProcessor().attachMouseListener(fp);
		wnd_main.getInputProcessor().startCapturing();*/

		GenericScene sm;
		fp.pscene =  &sm;
		//fp.pouttex = pouttex;
		sm.setFarCutOffState(false);
		sm.setSceneClipped(false);
		sm.setAmbientLight(Color::BLACK);


		//Sphere *psphere = new Sphere("test_sphere");
		//psphere->setSlices(20);
		Material * pmat = new Material("mat black");
		//pmat->setShininess(0);
		//pmat->setAmbient(Color::BLACK);
		Cube * pcube = new Cube("test_cube");
		pcube->setMaterial(pmat);
		sm.getRootNode().createChild("model")->attachObject(pcube);
		sm.getRootNode().createChild("camera", Vector3(0, 0, 10))->attachCamera(pcam);
		sm.getRootNode().getChildPtr("camera")->createChild("2ndview")->attachCamera(pcam2);
		sm.getRootNode().getChildPtr("camera")->setLight(*new Light());

		m_engine.getPlatformManager().disableVSync();
		m_engine.startRendering();
//		while(1) {
//			sm.getRootNode().getChildPtr("model")->rotate(Quaternion(Vector3::UNIT_Y, Degree(30)));
//			m_engine.renderOneFrame();
//			sleep(1);
//		}
	}

};

#endif /* APP_HPP_ */
