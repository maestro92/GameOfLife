
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

    s = new Shader("EG_GOLUpdate.vs", "EG_GOLUpdate.fs");
    r_GOLUpdate.addShader(s);


    s = new Shader("EG_GOLRender.vs", "EG_GOLRender.fs");
    r_GOLRender.addShader(s);
    r_GOLRender.addDataPair(RENDER_PASS1, "u_texture",    DP_INT);


    /// r_GUIRenderer
    s = new Shader("/EG_GUIShaders/EG_GUI.vs", "/EG_GUIShaders/EG_GUI.fs");
    r_GUIRenderer.addShader(s);



    /// r_textureRenderer
    s = new Shader("EG_TextureRenderer.vs", "EG_TextureRenderer.fs");
    r_textureRenderer.addShader(s);
    r_textureRenderer.addDataPair(RENDER_PASS1, "u_texture",    DP_INT);


    ///r_particleCompositeRenderer
    s = new Shader("/EG_NoiseBasedParticleEffectShaders/EG_CompositeShader.vs",
                   "/EG_NoiseBasedParticleEffectShaders/EG_CompositeShader.fs");
    r_particleCompositeRenderer.addShader(s);
    r_particleCompositeRenderer.addDataPair(RENDER_PASS1, "u_backgroundTexture",    DP_INT);
    r_particleCompositeRenderer.addDataPair(RENDER_PASS1, "u_particlesTexture",     DP_INT);
}






