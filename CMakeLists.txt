cmake_minimum_required(VERSION 2.8)

project(hy672)

# Enable C++!1 support
if(${CMAKE_COMPILER_IS_GNUCC})
add_definitions(-std=gnu++0x)
endif(${CMAKE_COMPILER_IS_GNUCC})

# Depend on o3engine
add_subdirectory(o3engine)

include_directories(${PROJECT_SOURCE_DIR}/o3engine)
add_executable(hy672 src/hy672.cpp)
target_link_libraries(hy672 o3engine boost_filesystem boost_system boost_regex freetype GL GLEW glut assimp freeimage freeimageplus)
