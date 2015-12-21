#ifndef GOL_GUI_MANAGER_H_
#define GOL_GUI_MANAGER_H_

#include "pipeline.h"
#include "EG_Utility.h"
#include "EG_Rect.h"
#include "EG_Slider.h"
#include "EG_ListBox.h"
#include "EG_Button.h"


class GOL_GUIManager
{
    public:
        void init(int paletteX, int paletteY,
                  int paletteWidth, int paletteHeight,
                  int screenWidth, int screenHeight);
        GLuint getGUIPaletteTexture();
        EG_Rect m_paletteRect;
        void initGUIRenderingSetup();


        EG_ListBox m_GOLModelListBox;

    private:
        GLuint m_GUIPaletteTexture;
        pipeline m_GUIPipeline;
        int m_screenWidth;
        int m_screenHeight;
};

#endif
