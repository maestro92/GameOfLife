#include "Control.h"

TextEngine Control::m_textEngine;
EG_QuadModelABS Control::m_quadModel;// = EG_QuadModelABS(1,1);


Control::Control() : Control("Martin :)", 0,0,1,1, BLUE)
{}

Control::Control(string text, int x, int y, int width, int height, glm::vec3 color)
{
    m_text = text;
    setRect(x,y,width,height);
    m_isInside = false;
    m_rectColor = color;
    m_rectTexture = -1;
//    m_quadModel.init(1,1);
}

Control::~Control()
{

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




void Control::renderSingle(pipeline& p, Renderer* r, Rect& rect)
{
    p.pushMatrix();
        p.translate(rect.x, rect.y, 0);
        p.scale(rect.w, rect.h, 0);
        r->loadUniformLocations(p, RENDER_PASS1);
        m_quadModel.render();
    p.popMatrix();
}


void Control::render(pipeline& p, Renderer* r)
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


void Control::init(string font, int size, int sreenWidth, int screenHeight)
{
    m_textEngine = TextEngine("", size, sreenWidth, screenHeight);
    m_quadModel = EG_QuadModelABS(1,1);
}



