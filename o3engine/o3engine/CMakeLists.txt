cmake_minimum_required (VERSION 3.0)
include(FindPkgConfig)

# Dependencies
pkg_check_modules(exlibs REQUIRED freetype2 glew assimp)
FIND_PACKAGE(glm REQUIRED)

include_directories(${exlibs_INCLUDE_DIRS}, )

# Enable C++11 support
if(${CMAKE_COMPILER_IS_GNUCC})
    add_definitions(-std=c++11)
endif(${CMAKE_COMPILER_IS_GNUCC})

add_library(o3engine STATIC
./base/matrix4.cpp
./base/image.cpp
./base/angle.cpp
./base/color.cpp
./base/quaternion.cpp
./base/matrix3.cpp
./base/vector3.cpp
./base/math.cpp
./base/vector4.cpp
./base/vector2.cpp
./base/triangle3.cpp
./base/rectangle.cpp
./scenerenderer.cpp
./renderline/viewportoutput.cpp
./renderline/output.cpp
./renderline/textureoutput.cpp
./font.cpp
./texture.cpp
./pugixml/pugixml.cpp
./skybox.cpp
./primitives.cpp
./genericnode.cpp
./o3engine.cpp
./overlay.cpp
./geometry.cpp
./nodmaterial/storage.cpp
./nodmaterial/node.cpp
./nodmaterial/mathnode.cpp
./nodmaterial/nodecontainer.cpp
./nodmaterial/socket.cpp
./nodmaterial/programbuilder.cpp
./nodmaterial/timenode.cpp
./nodmaterial/geometrynode.cpp
./nodmaterial/builder_tools.cpp
./nodmaterial/texturenode.cpp
./nodmaterial/shadingnode.cpp
./billboard.cpp
./texturemanager.cpp
./objectmanager.cpp
./animatedtexture.cpp
./perspectivecamera.cpp
./genericmaterial.cpp
./framelistener.cpp
./nodmaterial.cpp
./light.cpp
./platform/glut/inputprocessor_impl_glut.cpp
./platform/glut/offscreen_impl_glut.cpp
./platform/glut/glut_state.cpp
./platform/glut/platform_impl_glut.cpp
./platform/glut/window_impl_glut.cpp
./platform/timer_win32.cpp
./platform/surface.cpp
./platform/mouselistener.cpp
./platform/platform.cpp
./platform/timer_posix.cpp
./platform/keyboardlistener.cpp
./platform/inputprocessor.cpp
./orthocamera.cpp
./drawableobject.cpp
./ogl/uniform_block.cpp
./ogl/uniform.cpp
./ogl/vertex_array.cpp
./ogl/scissor_test_unit.cpp
./ogl/texture.cpp
./ogl/stencil_test_unit.cpp
./ogl/depth_test_unit.cpp
./ogl/context.cpp
./ogl/blend_unit.cpp
./ogl/buffer.cpp
./ogl/program.cpp
./ogl/texture_unit.cpp
./ogl/face_cull_unit.cpp
./ogl/capabilities_unit.cpp
./ogl/utils/info.cpp
./ogl/frame_buffer.cpp
./ogl/shader.cpp
./ogl/render_buffer.cpp
./mesh.cpp
./camera.cpp
./material.cpp
./gui/guiwindow.cpp
./gui/guisimpleengine.cpp
./gui/guiroot.cpp
./genericscene.cpp
./programmanager.cpp
./timesensitive.cpp
./materialmanager.cpp
./fontmanager.cpp
./string_functions.cpp
        base/platform_prereqs.hpp)
