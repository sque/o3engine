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
	renderer.cpp
	renderoutput.cpp
	renderoutputtexture.cpp
	renderoutputviewport.cpp
	simplerenderer.cpp
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
	platforms/input_processor.cpp
	platforms/input_processor_impl_glut.cpp
	platforms/keyboard_listener.cpp
	platforms/mouse_listener.cpp
	platforms/platform.cpp
	platforms/platform_impl_glut.cpp
	platforms/timer_posix.cpp
)

