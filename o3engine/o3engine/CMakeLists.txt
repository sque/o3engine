include(FindPkgConfig)

pkg_search_module(exlibs REQUIRED freetype2 glew2)

# There must be a better way for include directories
SET(CMAKE_CXX_FLAGS "${exlibs_CFLAGS} ${CMAKE_CXX_FLAGS}")

add_library(o3engine STATIC 
	animatedtexture.cpp
	billboard.cpp
	camera.cpp
	drawableobject.cpp
	face.cpp
	font.cpp
	fontmanager.cpp
	framelistener.cpp
	genericnode.cpp
	genericscene.cpp
	light.cpp
	material.cpp
	materialmanager.cpp
	mesh.cpp
	o3engine.cpp
	objectmanager.cpp
	overlay.cpp
	skinnedobject.cpp
	skybox.cpp
	string_functions.cpp
	submesh.cpp
	texture.cpp
	texturemanager.cpp
	timesensitive.cpp
	base/angle.cpp
	base/color.cpp
	base/image.cpp
	base/math.cpp
	base/matrix3.cpp
	base/quaternion.cpp
	base/rectangle.cpp
	base/triangle3.cpp
	base/vector2.cpp
	base/vector3.cpp
	base/vector4.cpp
	gui/guibutton.hpp
	gui/guiroot.cpp
	gui/guisimpleengine.cpp
	gui/guiwindow.cpp
	tinyxml/tinystr.cpp
	tinyxml/tinyxml.cpp
	tinyxml/tinyxmlerror.cpp
	tinyxml/tinyxmlparser.cpp
	platform/inputprocessor.cpp
	platform/keyboardlistener.cpp
	platform/mouselistener.cpp
	platform/platform.cpp
	platform/surface.cpp
	platform/timer_posix.cpp
	platform/glut/glut_state.cpp
	platform/glut/inputprocessor_impl_glut.cpp
	platform/glut/offscreen_impl_glut.cpp
	platform/glut/platform_impl_glut.cpp
	platform/glut/window_impl_glut.cpp
	renderline/output.cpp
	renderline/textureoutput.cpp
	renderline/viewportoutput.cpp
)
