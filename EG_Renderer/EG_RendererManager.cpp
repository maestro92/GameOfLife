
#include "EG_RendererManager.h"

EG_RendererManager::EG_RendererManager()
{

}

EG_RendererManager::~EG_RendererManager()
{

}


void EG_RendererManager::init(int screenWidth, int screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    m_texturePipeline.matrixMode(PROJECTION_MATRIX);
    m_texturePipeline.loadIdentity();
    m_texturePipeline.ortho(0, m_screenWidth, 0, m_screenHeight, -1, 1);

    m_texturePipeline.matrixMode(MODEL_MATRIX);
    m_texturePipeline.loadIdentity();

    m_textureQuad.init(1,1);

 //   m_textureQuad.init(-1, 1, -1, 1,
  //                        0.0, 0.0, 1.0);

    Shader* s;

    s = new Shader("EG_GOLUserInput.vs", "EG_GOLUserInput.fs");
    r_GOLUserInput.addShader(s);
    r_GOLUserInput.addDataPair(RENDER_PASS1, "u_boardTexture", DP_INT);
    r_GOLUserInput.addDataPair(RENDER_PASS1, "u_startGridX", DP_FLOAT);
    r_GOLUserInput.addDataPair(RENDER_PASS1, "u_startGridY", DP_FLOAT);
    r_GOLUserInput.addDataPair(RENDER_PASS1, "u_endGridX", DP_FLOAT);
    r_GOLUserInput.addDataPair(RENDER_PASS1, "u_endGridY", DP_FLOAT);
    r_GOLUserInput.addDataPair(RENDER_PASS1, "u_invWidth", DP_FLOAT);
    r_GOLUserInput.addDataPair(RENDER_PASS1, "u_invHeight", DP_FLOAT);
    r_GOLUserInput.addDataPair(RENDER_PASS1, "u_mouseLeftBtnDown", DP_BOOL);

    s = new Shader("EG_GOLUserInputWithPattern.vs", "EG_GOLUserInputWithPattern.fs");
    r_GOLUserInputWithPattern.addShader(s);
    r_GOLUserInputWithPattern.addDataPair(RENDER_PASS1, "u_boardTexture", DP_INT);
    r_GOLUserInputWithPattern.addDataPair(RENDER_PASS1, "u_patternTexture",       DP_INT);
    r_GOLUserInputWithPattern.addDataPair(RENDER_PASS1, "u_patternBottomRightX",  DP_INT);
    r_GOLUserInputWithPattern.addDataPair(RENDER_PASS1, "u_patternBottomRightY",  DP_INT);
    r_GOLUserInputWithPattern.addDataPair(RENDER_PASS1, "u_patternWidth",         DP_INT);
    r_GOLUserInputWithPattern.addDataPair(RENDER_PASS1, "u_patternHeight",        DP_INT);
    r_GOLUserInputWithPattern.addDataPair(RENDER_PASS1, "u_mouseLeftBtnDown",   DP_BOOL);



    s = new Shader("EG_GOLUpdate.vs", "EG_GOLUpdate.fs");
    r_GOLUpdate.addShader(s);
    r_GOLUpdate.addDataPair(RENDER_PASS1, "u_sourceTexture", DP_INT);


    s = new Shader("EG_GOLRenderInputWithPattern.vs", "EG_GOLRenderInputWithPattern.fs");
    r_GOLRenderInputWithPattern.addShader(s);
    r_GOLRenderInputWithPattern.addDataPair(RENDER_PASS1, "u_inputTexture",         DP_INT);
    r_GOLRenderInputWithPattern.addDataPair(RENDER_PASS1, "u_patternTexture",       DP_INT);
    r_GOLRenderInputWithPattern.addDataPair(RENDER_PASS1, "u_patternBottomRightX",  DP_INT);
    r_GOLRenderInputWithPattern.addDataPair(RENDER_PASS1, "u_patternBottomRightY",  DP_INT);
    r_GOLRenderInputWithPattern.addDataPair(RENDER_PASS1, "u_patternWidth",         DP_INT);
    r_GOLRenderInputWithPattern.addDataPair(RENDER_PASS1, "u_patternHeight",        DP_INT);


    s = new Shader("EG_GOLRenderSimulation.vs", "EG_GOLRenderSimulation.fs");
    r_GOLRenderSimluation.addShader(s);
    r_GOLRenderSimluation.addDataPair(RENDER_PASS1, "u_simulationTexture",    DP_INT);


    s = new Shader("EG_GOLRenderIntermediate.vs", "EG_GOLRenderIntermediate.fs");
    r_GOLRenderIntermediate.addShader(s);
    r_GOLRenderIntermediate.addDataPair(RENDER_PASS1, "u_sourceTexture",    DP_INT);
    r_GOLRenderIntermediate.addDataPair(RENDER_PASS1, "u_srcPresentValue",  DP_INT);
    r_GOLRenderIntermediate.addDataPair(RENDER_PASS1, "u_srcEmptyValue",    DP_INT);
    r_GOLRenderIntermediate.addDataPair(RENDER_PASS1, "u_dstPresentValue",  DP_INT);
    r_GOLRenderIntermediate.addDataPair(RENDER_PASS1, "u_dstEmptyValue",    DP_INT);


    /// r_CustomGUIPanelRenderer
    s = new Shader("/EG_GUIShaders/GOL_CustomGUIPanel.vs", "/EG_GUIShaders/GOL_CustomGUIPanel.fs");
    r_CustomGUIPanelRenderer.addShader(s);



    /// r_GUIRenderer
    s = new Shader("/EG_GUIShaders/EG_Rect.vs", "/EG_GUIShaders/EG_Rect.fs");
    r_RectRenderer.addShader(s);
    r_RectRenderer.addDataPair(RENDER_PASS1, "u_color", DP_VEC3);


    /// r_textureRenderer
    s = new Shader("EG_TextureRenderer.vs", "EG_TextureRenderer.fs");
    r_textureRenderer.addShader(s);
    r_textureRenderer.addDataPair(RENDER_PASS1, "u_texture",    DP_INT);

}



void EG_RendererManager::renderTextureFullScreen(GLuint TextureId)
{

}


void EG_RendererManager::renderTextureFullScreen(GLuint TextrureId, GLuint FboTarget)
{





}


void EG_RendererManager::renderTexture(GLuint TextureId, int x, int y, int width, int height)
{

}


void EG_RendererManager::renderTexture(GLuint TextureId, GLuint FboTarget, int x, int y, int width, int height)
{
    glViewport(0, 0, m_screenWidth, m_screenHeight);

    r_textureRenderer.enableShader(RENDER_PASS1);
    r_textureRenderer.setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, TextureId);

    m_texturePipeline.pushMatrix();
        m_texturePipeline.translate(x, y, 0);
        m_texturePipeline.scale(width, height, 1.0);

        r_textureRenderer.loadUniformLocations(m_texturePipeline, RENDER_PASS1);
        m_textureQuad.render();
    m_texturePipeline.popMatrix();
    r_textureRenderer.disableShader(RENDER_PASS1);
}


void EG_RendererManager::renderTexture(GLuint TextureId, GLuint FboTarget, EG_Rect rect)
{
    renderTexture(TextureId, FboTarget, rect.x, rect.y, rect.w, rect.h);
}


void EG_RendererManager::renderTextureSingle(GLuint TextureId, int x, int y, int width, int height)
{

}

void EG_RendererManager::renderTextureSingle(GLuint TextureId, GLuint FboTarget, int x, int y, int width, int height)
{
    r_textureRenderer.enableShader();
    r_textureRenderer.setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, TextureId);

    m_texturePipeline.pushMatrix();
        m_texturePipeline.translate(x, y, 0);
        m_texturePipeline.scale(width, height, 1.0);

        r_textureRenderer.loadUniformLocations(m_texturePipeline);
        m_textureQuad.render();
    m_texturePipeline.popMatrix();
    r_textureRenderer.disableShader();
}

void EG_RendererManager::renderTextureSingle(GLuint TextureId, GLuint FboTarget, EG_Rect rect)
{

}



