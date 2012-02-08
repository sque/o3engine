//============================================================================
// Name        : hy672.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <o3engine/o3engine.hpp>
#include <o3engine/simplerenderer.hpp>
using namespace std;
using namespace o3engine;

int main(int argc, char ** argv) {
    //pcache_manager = new ResourceCacheManager();

    // Start engine
    O3Engine m_engine;
    m_engine.init(argc, argv);

    // Set up window
    Platform::getSingleton().setWindowTitle("SpaceChase");
    Platform::getSingleton().setWindowSize(800, 600);

    // Set up renderer
    SimpleRenderer *prenderer_simple;
    m_engine.setRenderer(prenderer_simple = new SimpleRenderer());
}
