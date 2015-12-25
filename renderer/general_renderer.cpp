#include "general_renderer.h"


GeneralRenderer::GeneralRenderer()
{}

GeneralRenderer::~GeneralRenderer()
{}

void GeneralRenderer::loadUniformLocations()
{
    loadUniformLocations(RENDER_PASS1);
}

void GeneralRenderer::loadUniformLocations(int pass)
{
    for ( auto local_it = m_tables[pass].begin(); local_it!= m_tables[pass].end(); ++local_it )
        (local_it->second)->setUniLoc();
}

void GeneralRenderer::loadUniformLocations(pipeline& p)
{
    loadUniformLocations(p, RENDER_PASS1);
}

void GeneralRenderer::loadUniformLocations(pipeline& p, int pass)
{
    loadUniformLocations(pass);
    Renderer::loadUniformLocations(p, pass);
}
