#ifndef GUI_MANAGER_H_
#define GUI_MANAGER_H_

#include "pipeline.h"
#include "EG_Utility.h"
#include "EG_Rect.h"
#include "EG_Slider.h"
#include "EG_ListBox.h"
#include "EG_Button.h"
#include "GOL_Model.h"

#include "EG_GeneralRenderer.h"

class GOL_GUIManager
{
    public:
        void init(int paletteX, int paletteY,
                  int paletteWidth, int paletteHeight,
                  int screenWidth, int screenHeight);
        GLuint getGUIPaletteTexture();









        EG_Rect m_paletteRect;
        void initGUIRenderingSetup();

        void setGOLModelListBoxMenuContent(vector<GOL_Model*> models);

        EG_ListBox m_GOLModelListBox;


        EG_GeneralRenderer  r_textRenderer;
        EG_GeneralRenderer  r_RectRenderer;

        void renderGUIComponents();
        void renderText(GLuint TextureId, GLuint FboTarget, EG_Rect rect);

    private:
        EG_QuadModelABS m_textureQuad;
        GLuint m_GUIPaletteTexture;
        pipeline m_GUIPipeline;
        int m_screenWidth;
        int m_screenHeight;
};

#endif
