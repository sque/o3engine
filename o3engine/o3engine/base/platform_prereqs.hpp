#ifndef O3ENGINE_PLATFORM_PREREQS_HPP
#define O3ENGINE_PLATFORM_PREREQS_HPP

// Platform libraries needed
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

#endif //O3ENGINE_PLATFORM_PREREQS_HPP
