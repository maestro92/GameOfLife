#ifndef EG_RENDERER_MANAGER_H_
#define EG_RENDERER_MANAGER_H_

#include "EG_QuadModelABS.h"
#include "EG_GeneralRenderer.h"
#include "EG_Rect.h"
// #include "GOL_ScreenRenderInfo.h"
class EG_RendererManager
{
    public:

        EG_RendererManager();
        ~EG_RendererManager();

        EG_GeneralRenderer  r_GOLUpdate;
        EG_GeneralRenderer  r_GOLUserInput;
        EG_GeneralRenderer  r_GOLUserInputWithPattern;

        EG_GeneralRenderer  r_GOLRenderInput;
        EG_GeneralRenderer  r_GOLRenderInputWithPattern;

        EG_GeneralRenderer  r_GOLRenderIntermediate;
        EG_GeneralRenderer  r_GOLRenderSimluation;

        EG_GeneralRenderer  r_textureRenderer;

        EG_GeneralRenderer  r_textRenderer;
        EG_GeneralRenderer  r_RectRenderer;

        void init(int screenWidth, int screenHeight);

        void renderTextureFullScreen(GLuint TextureId);
        void renderTextureFullScreen(GLuint TextrureId, GLuint FboTarget);
        void renderTexture(GLuint TextureId, int x, int y, int width, int height);
        void renderTexture(GLuint TextureId, GLuint FboTarget, int x, int y, int width, int height);
        void renderTexture(GLuint TextureId, GLuint FboTarget, EG_Rect rect);

        void renderTextureSingle(GLuint TextureId, int x, int y, int width, int height);
        void renderTextureSingle(GLuint TextureId, GLuint FboTarget, int x, int y, int width, int height);
        void renderTextureSingle(GLuint TextureId, GLuint FboTarget, EG_Rect rect);

        void renderText(GLuint TextureId, GLuint FboTarget, EG_Rect rect);

        EG_QuadModelABS m_textureQuad;
        pipeline m_texturePipeline;
        int m_screenWidth;
        int m_screenHeight;
    private:
   //     ScreenRenderInfo m_screenRenderInfo;
};

#endif

