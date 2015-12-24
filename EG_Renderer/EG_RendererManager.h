#ifndef EG_RENDERER_MANAGER_H_
#define EG_RENDERER_MANAGER_H_

#include "EG_QuadModelABS.h"
#include "general_renderer.h"
#include "Rect.h"
// #include "GOL_ScreenRenderInfo.h"
class EG_RendererManager
{
    public:

        EG_RendererManager();
        ~EG_RendererManager();

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


        void renderText(GLuint TextureId, GLuint FboTarget, Rect rect);

        EG_QuadModelABS m_textureQuad;
        pipeline m_texturePipeline;
        int m_screenWidth;
        int m_screenHeight;
    private:
   //     ScreenRenderInfo m_screenRenderInfo;
};

#endif

