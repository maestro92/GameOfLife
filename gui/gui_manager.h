#ifndef GUI_MANAGER_H_
#define GUI_MANAGER_H_

#include "pipeline.h"
#include "utility.h"
#include "Rect.h"
#include "Slider.h"
#include "list_box.h"
#include "button.h"
#include "gol_model.h"

#include "general_renderer.h"

class GUIManager
{
    public:
        void init(int paletteX, int paletteY,
                  int paletteWidth, int paletteHeight,
                  int screenWidth, int screenHeight);
        GLuint getGUIPaletteTexture();



        Rect m_paletteRect;
        void initGUIRenderingSetup();

        void setGOLModelListBoxMenuContent(vector<GOLModel*> models);

        ListBox m_GOLModelListBox;



        void renderTextureFullScreen(GLuint TextureId);
        void renderTextureFullScreen(GLuint TextrureId, GLuint FboTarget);
        void renderTexture(GLuint TextureId, int x, int y, int width, int height);
        void renderTexture(GLuint TextureId, GLuint FboTarget, int x, int y, int width, int height);
        void renderTexture(GLuint TextureId, GLuint FboTarget, Rect rect);

        void renderTextureSingle(GLuint TextureId, int x, int y, int width, int height);
        void renderTextureSingle(GLuint TextureId, GLuint FboTarget, int x, int y, int width, int height);
        void renderTextureSingle(GLuint TextureId, GLuint FboTarget, Rect rect);

        void renderGUI();

        GeneralRenderer  r_textureRenderer;


        void renderGUIComponents();
     //   void renderText(GLuint TextureId, GLuint FboTarget, Rect rect);

    private:
        QuadModel m_textureQuad;
        GLuint m_GUIPaletteTexture;
        pipeline m_GUIPipeline;
        int m_screenWidth;
        int m_screenHeight;
};

#endif
