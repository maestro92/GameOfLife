#include "Control.h"

TextEngine Control::m_textEngine;
pipeline Control::m_pipeline;
QuadModel Control::m_quadModel;// = QuadModel(1,1);
GeneralRenderer Control::r_coloredRectRenderer;GeneralRenderer Control::r_texturedRectRenderer;
GeneralRenderer Control::r_listBoxHighlightRenderer;


Control::Control() : Control("Martin :)", 0,0,1,1, BLUE)
{}

Control::Control(string text, int x, int y, int width, int height, glm::vec3 color)
{
    m_text = text;
    setRect(x,y,width,height);
    m_isInside = false;
    m_rectColor = color;
    m_rectTexture = -1;
    m_funcCallBack = NULL;

    m_font.color = glm::vec3(0.5, 0.8f, 0.2f);
    m_font.size = 0.8;

    m_textStartingXs.resize(1);
    m_textStartingYs.resize(1);

    m_textStartingXs[0] = Control::getTextStartingX(text, m_font.size, m_rect.w, m_rect.x);
    m_textStartingYs[0] = Control::getTextStartingY(text, m_font.size, m_rect.h, m_rect.y);
    Utility::debug("X", m_textStartingXs[0]);
    Utility::debug("Y", m_textStartingYs[0]);
}

Control::~Control()
{

}




void Control::init(string font, int size, int sreenWidth, int screenHeight)
{
    m_textEngine = TextEngine("", size, sreenWidth, screenHeight);
    m_quadModel = QuadModel(1,1);

    Shader* s;

    /// r_coloredRect and r_texturedRect
    s = new Shader("/EG_GUIShaders/colored_rect.vs", "/EG_GUIShaders/colored_rect.fs");
    r_coloredRectRenderer.addShader(s);
    r_coloredRectRenderer.addDataPair(RENDER_PASS1, "u_color", DP_VEC3);

    s = new Shader("/EG_GUIShaders/textured_rect.vs", "/EG_GUIShaders/textured_rect.fs");
    r_texturedRectRenderer.addShader(s);
    r_texturedRectRenderer.addDataPair(RENDER_PASS1, "u_texture",    DP_INT);


    s = new Shader("/EG_GUIShaders/list_box_item_highlight.vs", "/EG_GUIShaders/list_box_item_highlight.fs");
    r_listBoxHighlightRenderer.addShader(s);
    r_listBoxHighlightRenderer.addDataPair(RENDER_PASS1, "u_x1",    DP_FLOAT);
    r_listBoxHighlightRenderer.addDataPair(RENDER_PASS1, "u_x2",    DP_FLOAT);
    r_listBoxHighlightRenderer.addDataPair(RENDER_PASS1, "u_y1",    DP_FLOAT);
    r_listBoxHighlightRenderer.addDataPair(RENDER_PASS1, "u_y2",    DP_FLOAT);



    m_pipeline.matrixMode(PROJECTION_MATRIX);
    m_pipeline.loadIdentity();
    m_pipeline.ortho(0, sreenWidth, 0, screenHeight, -1, 1);

    m_pipeline.matrixMode(MODEL_MATRIX);
    m_pipeline.loadIdentity();
}





void Control::setID(int& ID)
{
    m_id = ID;
    ID++;
}

void Control::setText(string text)
{
    m_text = text;
}

void Control::setTexture(GLuint id)
{
    m_rectTexture = id;
}

void Control::setColor(glm::vec3 color)
{
    m_rectColor = color;
}

void Control::setRect(int x, int y, int w, int h)
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = w;
    m_rect.h = h;
}

bool Control::update(MouseState & state)
{
    int x = state.m_pos.x;
    int y = state.m_pos.y;

    m_isInside = false;

    if( (x >= m_rect.x && x <= m_rect.x + m_rect.w) &&
        (y >= m_rect.y && y <= m_rect.y + m_rect.h) )
    {
        m_isInside = true;
    }

    return false;
}


bool Control::update(MouseState & state, unsigned int& groupFlag)
{
    bool flag = update(state);
    if(flag)
    {
        groupFlag = groupFlag | ( 1 << m_id);
     //   Utility::debug()
     //   std::bitset<32> x(groupFlag);
     //   cout << x << endl;
    }
    else
    {
        groupFlag = groupFlag & (~( 1 << m_id));
     //   std::bitset<32> x(groupFlag);
     //   cout << x << endl;
    }
    return flag;
}

float Control::getTextStartingX(string text, float size, float rectWidth, float offsetX)
{
    float w = m_textEngine.getTextWidth(text, size);

    float diff = (rectWidth - w)/2;

    return offsetX + diff;
}

float Control::getTextStartingY(string text, float size, float rectHeight, float offsetY)
{
    float h = m_textEngine.getTextHeight(text, size);

    float diff = (rectHeight - h)/2;

    return offsetY + diff;
}


void Control::updatePipeline(Renderer* r)
{
    updatePipeline(r, m_rect);
}

void Control::updatePipeline(Renderer* r, Rect rect)
{
    m_pipeline.pushMatrix();
        m_pipeline.translate(rect.x, rect.y, 0);
        m_pipeline.scale(rect.w, rect.h, 1.0);
        r->loadUniformLocations(m_pipeline, RENDER_PASS1);
    m_pipeline.popMatrix();
}

void Control::customRender()
{

}


void Control::emptyOnClick()
{
    Utility::debug("In " + m_text + " the empty OnClick Func");
}


/*
void Control::renderColored()
{
    render(&Control::r_coloredRectRenderer, m_rect);
}

void Control::renderColoredSingle()
{
    renderSingle(&Control::r_coloredRectRenderer, m_rect);
}

void Control::renderColored(Rect rect)
{
    render(&Control::r_coloredRectRenderer, rect);
}

void Control::renderColoredSingle(Rect rect)
{
    renderSingle(&Control::r_coloredRectRenderer, rect);
}



void Control::renderTextured()
{
    render(&Control::r_texturedRectRenderer, m_rect);
}

void Control::renderTexturedSingle()
{
    renderSingle(&Control::r_texturedRectRenderer, m_rect);
}

void Control::renderTextured(Rect rect)
{
    render(&Control::r_texturedRectRenderer, rect);
}

void Control::renderTexturedSingle(Rect rect)
{
    renderSingle(&Control::r_texturedRectRenderer, rect);
}
*/





