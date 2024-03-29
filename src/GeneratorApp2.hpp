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
#include <o3engine/renderline/textureoutput.hpp>
#include <o3engine/renderline/viewportoutput.hpp>
#include <iostream>
#include <fstream>
#include <boost/format.hpp>
#include "OrthoCamera.hpp"

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

class PostProcessor :
	public RenderLine::TextureOutput {
public:
		PostProcessor(OffScreen & offscreen)
				:TextureOutput(offscreen) {

		}

		void render(){
			TextureOutput::render();
			// Disable not needed things
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_LIGHTING);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho (0, 1, 0, 1, -1.0, 1.0);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			::glBindTexture(GL_TEXTURE_2D, m_gli_texture);
			glColor4(Color::WHITE);
			glBegin(GL_POLYGON);
				glTexCoord2f(0,0); glVertex2f(0, 0);
				glTexCoord2f(0,1); glVertex2f(0, 1);
				glTexCoord2f(1,1); glVertex2f(1, 1);
				glTexCoord2f(1,0); glVertex2f(1, 0);
			glEnd();

			// Renable everything
			glEnable(GL_LIGHTING);
			glEnable(GL_DEPTH_TEST);
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

		OffScreen off_scrn(800, 600);
		PostProcessor postproc(off_scrn);
		RenderLine::ViewportOutput * pout = new RenderLine::ViewportOutput(wnd_main, 800, 600, 0, 0);
		Camera * pcam = new Camera(Vector3::NEGATIVE_UNIT_Z, Vector3::UNIT_Y);
		OrthoCamera * pcam2 = new OrthoCamera(Vector3::NEGATIVE_UNIT_Z, Vector3::UNIT_Y, 4, 3);

		//pouttex->attachNode(*pcam);
		//pout->setInputCamera(pcam2);
		//pout->enableRendering();
		pout->attachNode(&postproc);
		postproc.attachNode(pcam);

		/*std::ifstream fs_vs("test.vs");
		ogl::Shader my_shader(ogl::Shader::shader_type::VERTEX, "test.vs");
		ogl::ShaderProgram prog;
		prog.attach_shader(my_shader);*/

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
