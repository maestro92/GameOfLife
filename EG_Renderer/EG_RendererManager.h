#ifndef EG_RENDERER_MANAGER_H_
#define EG_RENDERER_MANAGER_H_

#include "EG_GeneralRenderer.h"

class EG_RendererManager
{
    public:

        EG_RendererManager();
        ~EG_RendererManager();

        EG_GeneralRenderer  r_GOLUpdate;
        EG_GeneralRenderer  r_GOLUserInput;
        EG_GeneralRenderer  r_GOLRenderInput;
        EG_GeneralRenderer  r_GOLRenderIntermediate;
        EG_GeneralRenderer  r_GOLRenderSimluation;


        EG_GeneralRenderer  r_depthRenderer;
        EG_GeneralRenderer  r_fullColorRenderer;
        EG_GeneralRenderer  r_skyboxRenderer;
        EG_GeneralRenderer  r_dummyRenderer;
        EG_GeneralRenderer  r_GUITextRenderer;
        EG_GeneralRenderer  r_GUIRenderer;


        EG_GeneralRenderer  r_textureRenderer;
        EG_GeneralRenderer  r_particleCompositeRenderer;
        void init();



};

#endif

