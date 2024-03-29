/* O3Engine Version */
#define O3ENGINE_VERSION_MAJOR 0
#define O3ENGINE_VERSION_MINOR 3
#define O3ENGINE_VERSION_REVISION 999

/* Helpful macros */
#define __IMPL_STRINGIFY( x) #x
#define STRINGIFY(x) __IMPL_STRINGIFY(x)
#define __IMPL_CONCAT( a, b) a##b
#define CONCAT( a, b) __IMPL_CONCAT( a, b)

/* DEBUG MACROS */
// #define DEBUG_LOG
// Debug macros
#ifdef DEBUG_LOG
	#define DBG_PRINT_0(x) printf(x)
	#define DBG_PRINT_1(x,a) printf(x,a)
	#define DBG_PRINT_2(x,a,b) printf(x,a,b)
#else
	#define DBG_PRINT_0(x)
	#define DBG_PRINT_1(x,a)
	#define DBG_PRINT_2(x,a,b)
#endif


// System libraries needed
/* For Windows */
#ifdef WIN32
	#include <windows.h>
	#include <stdlib.h>
    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/freeglut.h>
	#define ENGINE_WIN32
#endif
#ifdef linux
    #include <GL/glew.h>
    #include <GL/freeglut.h>
    #define ENGINE_LINUX
#endif
#ifdef __APPLE__
	#include <GL/glew.h>
    #include <GLUT/freeglut.h>
	#define ENGINE_OSX
#endif

// Base System
#include "base/base.hpp"
#include "ogl/ogl.hpp"

// Class prototypes
namespace o3engine {

	class Camera;
	class RenderOutput;
	class ViewportRenderOutput;
	class Timer;
	class TimerSensitive;
	class TreeObject;
	class Skybox;
	class Platform;
	class Surface;
	class Window;
	class OffScreen;

	class Texture;
	class AnimatedTexture;
	class TextureManager;

	class Overlay;

	class MovableObject;
	class ObjectManager;

	class Material;
	class MaterialManager;

	class O3Engine;
	class InputProcessor;
	class MouseListener;
	class KeyboardListener;
	class Mesh;
	class Geometry;

	class SceneManager;
	class SceneNode;

	class GenericScene;
	class GenericNode;

	class Font;
	class FontManager;

    class Light;

	class GuiWindow;
	class GuiRoot;
	class GuiEngine;

	class GuiFrame;
	class GuiButton;

	using namespace std;
}
