#include "general_renderer.h"


GeneralRenderer::GeneralRenderer()
{}

GeneralRenderer::~GeneralRenderer()
{}

void GeneralRenderer::init(int nShaders)
{}


void GeneralRenderer::loadUniformLocations()
{
    loadUniformLocations(RENDER_PASS1);
}

void GeneralRenderer::loadUniformLocations(int pass)
{
    for ( auto local_it = tables[pass].begin(); local_it!= tables[pass].end(); ++local_it )
        (local_it->second)->setUniLoc();
}



void GeneralRenderer::loadUniformLocations(pipeline& p)
{
    loadUniformLocations(p, RENDER_PASS1);
}

void GeneralRenderer::loadUniformLocations(pipeline& p, int pass)
{
//    for ( auto local_it = tables[pass].begin(); local_it!= tables[pass].end(); ++local_it )
//        (local_it->second)->setUniLoc();
    loadUniformLocations(pass);
    Renderer::loadUniformLocations(p, pass);
}
