#include "gui_manager.h"




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


    m_textureQuad.init(1,1);

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
    int w = 200;
    int h = 200;
    m_GOLModelListBox = EG_ListBox("nice", x, y, w, h, GREEN, 2);
    m_GOLModelListBox.setColors(YELLOW, BLACK);


    Shader* s;

    /// r_GUIRenderer
    s = new Shader("/EG_GUIShaders/EG_Rect.vs", "/EG_GUIShaders/EG_Rect.fs");
    r_RectRenderer.addShader(s);
    r_RectRenderer.addDataPair(RENDER_PASS1, "u_color", DP_VEC3);

    /// r_TextRenderer
    s = new Shader("/EG_GUIShaders/EG_Text.vs", "/EG_GUIShaders/EG_Text.fs");
    r_textRenderer.addShader(s);
    r_textRenderer.addDataPair(RENDER_PASS1, "u_texture",   DP_INT);
    r_textRenderer.addDataPair(RENDER_PASS1, "u_color",     DP_VEC3);
}


void GOL_GUIManager::setGOLModelListBoxMenuContent(vector<GOL_Model*> models)
{
    int count = models.size();
    for(int i=0; i<count; i++)
    {
        m_GOLModelListBox.addItem(models[i]->getName());
    }
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

void GOL_GUIManager::renderText(GLuint TextureId, GLuint FboTarget, EG_Rect rect)
{
    glViewport(0, 0, m_screenWidth, m_screenHeight);

    r_textRenderer.enableShader(RENDER_PASS1);
    r_textRenderer.setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, TextureId);

    m_GUIPipeline.pushMatrix();
        m_GUIPipeline.translate(rect.x, rect.y, 0);
        m_GUIPipeline.scale(rect.w, rect.h, 1.0);

        r_textRenderer.loadUniformLocations(m_GUIPipeline, RENDER_PASS1);
        m_textureQuad.render();
    m_GUIPipeline.popMatrix();
    r_textRenderer.disableShader(RENDER_PASS1);

}


