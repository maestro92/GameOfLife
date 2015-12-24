
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







    /// r_GUIRectRenderer
    s = new Shader("/EG_GUIShaders/Rect.vs", "/EG_GUIShaders/Rect.fs");
    r_RectRenderer.addShader(s);
    r_RectRenderer.addDataPair(RENDER_PASS1, "u_color", DP_VEC3);


    /// r_TextRenderer
    s = new Shader("/EG_GUIShaders/EG_Text.vs", "/EG_GUIShaders/EG_Text.fs");
    r_textRenderer.addShader(s);
    r_textRenderer.addDataPair(RENDER_PASS1, "u_texture",   DP_INT);
    r_textRenderer.addDataPair(RENDER_PASS1, "u_color",     DP_VEC3);

}





void EG_RendererManager::renderText(GLuint TextureId, GLuint FboTarget, Rect rect)
{
    glViewport(0, 0, m_screenWidth, m_screenHeight);

    r_textRenderer.enableShader(RENDER_PASS1);
    r_textRenderer.setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, TextureId);

    m_texturePipeline.pushMatrix();
        m_texturePipeline.translate(rect.x, rect.y, 0);
        m_texturePipeline.scale(rect.w, rect.h, 1.0);

        r_textRenderer.loadUniformLocations(m_texturePipeline, RENDER_PASS1);
        m_textureQuad.render();
    m_texturePipeline.popMatrix();
    r_textRenderer.disableShader(RENDER_PASS1);
}

