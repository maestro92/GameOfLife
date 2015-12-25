#ifndef EG_RENDERER_MANAGER_H_
#define EG_RENDERER_MANAGER_H_

#include "quad_model.h"
#include "general_renderer.h"
#include "Rect.h"
// #include "GOL_ScreenRenderInfo.h"
class RendererManager
{
    public:
        RendererManager();
        ~RendererManager();

        GeneralRenderer  r_GOLUpdate;
        GeneralRenderer  r_GOLUserInput;
        GeneralRenderer  r_GOLUserInputWithPattern;

        GeneralRenderer  r_GOLRenderInput;
        GeneralRenderer  r_GOLRenderInputWithPattern;

        GeneralRenderer  r_GOLRenderIntermediate;
        GeneralRenderer  r_GOLRenderSimluation;


        GeneralRenderer  r_textRenderer;
        GeneralRenderer  r_RectRenderer;

        void init(int screenWidth, int screenHeight);

        QuadModel m_textureQuad;
        pipeline m_texturePipeline;
        int m_screenWidth;
        int m_screenHeight;
    private:
   //     ScreenRenderInfo m_screenRenderInfo;
};

#endif

