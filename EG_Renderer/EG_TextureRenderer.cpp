#include "EG_TextureRenderer.h"



EG_TextureRenderer::EG_TextureRenderer()
{
}



EG_TextureRenderer::~EG_TextureRenderer()
{
}



void EG_TextureRenderer::init(int nShaders)
{
//    m_quad1.init();
    allocateMemberVariables(nShaders);
    m_shaders[RENDER_PASS1] = new Shader("EG_TextureRendererShader.vs", "EG_TextureRendererShader.fs");

    m_textureUnitUniLoc    = getUniLoc(m_shaders[RENDER_PASS1], "gTexture");
    m_pixelSizeUniLoc      = getUniLoc(m_shaders[RENDER_PASS1], "gPixelSize");


//    initDataPairUniLoc(&m_colorPair,        m_shaders[RENDER_PASS1], "gColor");

    initMemberVariables();


    o_fullScreenQuad.init();
}



void EG_TextureRenderer::init()
{
    Shader* s = new Shader("EG_TextureRenderer.vs", "EG_TextureRenderer.fs");

    addShader(s);
    addDataPair(RENDER_PASS1, "u_texture",        DP_INT);


    m_textureUnitUniLoc    = getUniLoc(m_shaders[RENDER_PASS1], "gTexture");


//    initDataPairUniLoc(&m_colorPair,        m_shaders[RENDER_PASS1], "gColor");

    initMemberVariables();


    o_fullScreenQuad.init();
}


void EG_TextureRenderer::setTextureUnit(unsigned int TextureUnit)
{
    m_texUnit = TextureUnit;
}

void EG_TextureRenderer::setPixelSize(unsigned int Width, unsigned int Height)
{
//    glUniform2f(m_pixelSizeUniLoc, 1.0f/Width, 1.0f/Height);
    m_width = Width;
    m_height = Height;
}



void EG_TextureRenderer::loadUniformLocations(pipeline& p, int pass)
{
    setUniformLocation(m_textureUnitUniLoc, m_texUnit);
    setUniformLocation(m_pixelSizeUniLoc, 1.0f/m_width, 1.0f/m_height);
    EG_Renderer::loadUniformLocations(p, pass);
}


void EG_TextureRenderer::renderFullScreen(GLuint TextureID)
{
    renderFullScreen(TextureID, 0);
}

void EG_TextureRenderer::renderFullScreen(GLuint TextureID, GLuint FboTarget)
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    //render texture to screen
	pipeline m_pipeline;
	m_pipeline.loadIdentity();
	m_pipeline.ortho(0,1,0,1,-1,1);

    glBindFramebuffer(GL_FRAMEBUFFER, FboTarget);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shaders[RENDER_PASS1]->useShader();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TextureID);
        loadUniformLocations(m_pipeline, RENDER_PASS1);
        o_fullScreenQuad.render();

	m_shaders[RENDER_PASS1]->delShader();
    glEnable(GL_DEPTH_TEST);
}


void EG_TextureRenderer::render(GLuint TextureID, GLuint FboTarget, int x, int y)
{


}


