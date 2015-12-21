#include "EG_Control.h"

EG_Text EG_Control::m_textEngine;
EG_QuadModelABS EG_Control::m_quadModel;


EG_Control::EG_Control() : EG_Control("Martin :)", 0,0,1,1, BLUE)
{}

EG_Control::EG_Control(string text, int x, int y, int width, int height, glm::vec3 color)
{
    m_text = text;
    setRect(x,y,width,height);
    m_isInside = false;
    m_rectColor = color;
    m_rectTexture = -1;
    m_quadModel.init(1,1);
}

EG_Control::~EG_Control()
{

}

void EG_Control::setID(int& ID)
{
    m_id = ID;
    ID++;
}

void EG_Control::setText(string text)
{
    m_text = text;
}

void EG_Control::setTexture(GLuint id)
{
    m_rectTexture = id;
}

void EG_Control::setColor(glm::vec3 color)
{
    m_rectColor = color;
}

void EG_Control::setRect(int x, int y, int w, int h)
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = w;
    m_rect.h = h;
}

bool EG_Control::update(MouseState & state)
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


bool EG_Control::update(MouseState & state, unsigned int& groupFlag)
{
    bool flag = update(state);
    if(flag)
    {
        groupFlag = groupFlag | ( 1 << m_id);
     //   EG_Utility::debug()
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


int EG_Control::computeTextStartingX(string s)
{
    int textWidth = m_textEngine.getTextWidth(s.c_str());
    int sx = m_rect.w - textWidth;
    return m_rect.x + sx/2;
}


int EG_Control::computeTextStartingY()
{
    int textHeight = m_textEngine.getTextHeight();
    int sy = m_rect.h - textHeight;

    return m_rect.y + sy/2;
}


void EG_Control::renderSingle(pipeline& p,
                              EG_Renderer* r,
                              EG_Rect& rect)
{
    p.pushMatrix();
        p.translate(rect.x, rect.y, 0);
        p.scale(rect.w, rect.h, 0);
        r->loadUniformLocations(p, RENDER_PASS1);
        m_quadModel.render();
    p.popMatrix();
}


void EG_Control::render(pipeline& p,
                        EG_Renderer* r)
{
    r->enableShader();
    p.pushMatrix();
        p.scale(m_rect.w, m_rect.h, 0);
        p.translate(m_rect.x, m_rect.y, 0);
        r->loadUniformLocations(p, RENDER_PASS1);
        m_quadModel.render();
    p.popMatrix();
    r->disableShader();
}



