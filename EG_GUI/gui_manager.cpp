#include "gui_manager.h"


void GUIManager::init(int screenWidth, int screenHeight,
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

    TextureDataBuffer pixelData = Utility::createEmptyBuffer(paletteWidth, paletteHeight);

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
    m_GUIPaletteTexture = Utility::loadTexture(pixelData, GL_NEAREST);

    int x = m_screenWidth - 200;
    int y = 300;
    int w = 200;
    int h = 300;
    m_GOLModelListBox = ListBox("nice", x, y, w, h, GREEN, 2);
    m_GOLModelListBox.setColors(YELLOW, BLACK);


    Shader* s;


    /// r_textureRenderer
    s = new Shader("texture.vs", "texture.fs");
    r_textureRenderer.addShader(s);
    r_textureRenderer.addDataPair(RENDER_PASS1, "u_texture",    DP_INT);


    /// r_GUIRenderer
    s = new Shader("/EG_GUIShaders/rect.vs", "/EG_GUIShaders/rect.fs");
    r_RectRenderer.addShader(s);
    r_RectRenderer.addDataPair(RENDER_PASS1, "u_color", DP_VEC3);
}


void GUIManager::setGOLModelListBoxMenuContent(vector<GOL_Model*> models)
{
    int count = models.size();
    for(int i=0; i<count; i++)
    {
        m_GOLModelListBox.addItem(models[i]->getName());
    }
}

GLuint GUIManager::getGUIPaletteTexture()
{
    return m_GUIPaletteTexture;
}

void GUIManager::initGUIRenderingSetup()
{
    glViewport(0, 0, m_screenWidth, m_screenHeight);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}



void GUIManager::renderTextureFullScreen(GLuint TextureId)
{

}


void GUIManager::renderTextureFullScreen(GLuint TextrureId, GLuint FboTarget)
{


}


void GUIManager::renderTexture(GLuint TextureId, int x, int y, int width, int height)
{

}


void GUIManager::renderTexture(GLuint TextureId, GLuint FboTarget, int x, int y, int width, int height)
{
    glViewport(0, 0, m_screenWidth, m_screenHeight);

    r_textureRenderer.enableShader(RENDER_PASS1);
    r_textureRenderer.setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, TextureId);

    m_GUIPipeline.pushMatrix();
        m_GUIPipeline.translate(x, y, 0);
        m_GUIPipeline.scale(width, height, 1.0);

        r_textureRenderer.loadUniformLocations(m_GUIPipeline, RENDER_PASS1);
        m_textureQuad.render();
    m_GUIPipeline.popMatrix();
    r_textureRenderer.disableShader(RENDER_PASS1);
}


void GUIManager::renderTexture(GLuint TextureId, GLuint FboTarget, Rect rect)
{
    renderTexture(TextureId, FboTarget, rect.x, rect.y, rect.w, rect.h);
}


void GUIManager::renderTextureSingle(GLuint TextureId, int x, int y, int width, int height)
{

}

void GUIManager::renderTextureSingle(GLuint TextureId, GLuint FboTarget, int x, int y, int width, int height)
{
    r_textureRenderer.enableShader();
    r_textureRenderer.setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, TextureId);

    m_GUIPipeline.pushMatrix();
        m_GUIPipeline.translate(x, y, 0);
        m_GUIPipeline.scale(width, height, 1.0);

        r_textureRenderer.loadUniformLocations(m_GUIPipeline);
        m_textureQuad.render();
    m_GUIPipeline.popMatrix();
    r_textureRenderer.disableShader();
}

void GUIManager::renderTextureSingle(GLuint TextureId, GLuint FboTarget, Rect rect)
{

}


/*
void GUIManager::renderText(GLuint TextureId, GLuint FboTarget, Rect rect)
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
*/

