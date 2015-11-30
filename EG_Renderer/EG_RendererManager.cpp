
#include "EG_RendererManager.h"

EG_RendererManager::EG_RendererManager()
{

}

EG_RendererManager::~EG_RendererManager()
{

}


void EG_RendererManager::init()
{
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


    s = new Shader("EG_GOLRenderInput.vs", "EG_GOLRenderInput.fs");
    r_GOLRenderInput.addShader(s);
    r_GOLRenderInput.addDataPair(RENDER_PASS1, "u_inputTexture",    DP_INT);
    r_GOLRenderInput.addDataPair(RENDER_PASS1, "u_startGridX", DP_FLOAT);
    r_GOLRenderInput.addDataPair(RENDER_PASS1, "u_startGridY", DP_FLOAT);
    r_GOLRenderInput.addDataPair(RENDER_PASS1, "u_endGridX", DP_FLOAT);
    r_GOLRenderInput.addDataPair(RENDER_PASS1, "u_endGridY", DP_FLOAT);


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



    /// r_GUIRenderer
    s = new Shader("/EG_GUIShaders/EG_GUI.vs", "/EG_GUIShaders/EG_GUI.fs");
    r_GUIRenderer.addShader(s);



    /// r_textureRenderer
    s = new Shader("EG_TextureRenderer.vs", "EG_TextureRenderer.fs");
    r_textureRenderer.addShader(s);
    r_textureRenderer.addDataPair(RENDER_PASS1, "u_texture",    DP_INT);

}






