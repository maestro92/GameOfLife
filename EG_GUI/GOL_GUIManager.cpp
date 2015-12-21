#include "GOL_GUIManager.h"



void GOL_GUIManager::init(int screenWidth, int screenHeight,
                          int paletteX, int paletteY,
                          int paletteWidth, int paletteHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    // set m_GUIPipeline
    m_GUIPipeline.matrixMode(PROJECTION_MATRIX);
    m_GUIPipeline.loadIdentity();
    m_GUIPipeline.ortho(0, m_screenWidth, 0, m_screenHeight, -1, 1);

    m_GUIPipeline.matrixMode(MODEL_MATRIX);
    m_GUIPipeline.loadIdentity();


    m_paletteRect.set(paletteX, paletteY, paletteWidth, paletteHeight);

    EG_TextureDataBuffer pixelData = EG_Utility::createEmptyBuffer(paletteWidth, paletteHeight);

    for(int y = 0; y < paletteHeight; y++)
    {
        for(int x = 0; x < paletteWidth; x++)
        {
            if(y == 0 || y == paletteHeight-1 || x == 0 || x == paletteWidth-1)
            {
                pixelData[y][x][0] = 255;
                pixelData[y][x][1] = 0;
                pixelData[y][x][2] = 0;
                pixelData[y][x][3] = 0;
            }
            else
            {
                pixelData[y][x][0] = 255;
                pixelData[y][x][1] = 255;
                pixelData[y][x][2] = 255;
                pixelData[y][x][3] = 255;
            }


            if(y % 100 == 0)
            {
                pixelData[y][x][0] = 255;
                pixelData[y][x][1] = 0;
                pixelData[y][x][2] = 0;
                pixelData[y][x][3] = 0;
            }


            if(x == paletteWidth/2)
            {
                pixelData[y][x][0] = 255;
                pixelData[y][x][1] = 0;
                pixelData[y][x][2] = 0;
                pixelData[y][x][3] = 0;
            }
        }
    }
    m_GUIPaletteTexture = EG_Utility::loadTexture(pixelData, GL_NEAREST);

    int x = m_screenWidth - 200;
    int y = 300;
    int w = paletteX;
    int h = 200;
    m_GOLModelListBox = EG_ListBox("nice", x, y, w, h, GREEN, 1, 1);
    m_GOLModelListBox.setColors(YELLOW, BLACK);
//    m_GOLModelListBox.setID(3);

    m_GOLModelListBox.addItem("1");
    m_GOLModelListBox.addItem("2");
    m_GOLModelListBox.addItem("3");
    m_GOLModelListBox.addItem("4");
}

GLuint GOL_GUIManager::getGUIPaletteTexture()
{
    return m_GUIPaletteTexture;
}

void GOL_GUIManager::initGUIRenderingSetup()
{
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}


