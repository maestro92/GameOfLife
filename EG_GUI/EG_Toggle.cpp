#include "EG_Toggle.h"


EG_Toggle::EG_Toggle()
{

}


EG_Toggle::EG_Toggle(string text, int x, int y, int width, int height, glm::vec3 c) :
    EG_Control(text, x, y, width, height, c)
{
    m_down = false;
    m_highlightTexture = -1;
    m_pressedTexture = -1;
}


bool EG_Toggle::update(MouseState & state)
{
    EG_Control::update(state);
    if(m_isInside == true)
    {
        if (state.m_leftButtonDown)
        {
            m_down = true;
//            cout << "pressing the button" << endl;
        }

        /// if it was down, we set it to false
        else if (m_down)
        {
            m_down = false;

            return true;
        }
    }
    return false;
}



bool EG_Toggle::update(MouseState & state, unsigned int& groupFlag)
{
    if(groupFlag & ( 1 << m_id) || (groupFlag==0) )
    {
        bool flag = update(state);
//        cout << "Flag is " << flag << endl;

        if(flag == true)
        {
            groupFlag = groupFlag | ( 1 << m_id);
         //   EG_Utility::debug()
      //      std::bitset<32> x(groupFlag);
       //     cout << x << endl;
        }
        else
        {
            groupFlag = groupFlag & (~( 1 << m_id));
         //   std::bitset<32> x(groupFlag);
         //   cout << x << endl;
        }
        return flag;
    }
    return false;

    /*
    bool flag = update(state);
 //   cout << "Flag is " << flag << endl;

    if(flag)
    {
        groupFlag = groupFlag | ( 1 << m_id);
     //   EG_Utility::debug()
        std::bitset<32> x(groupFlag);
    //    cout << x << endl;
    }
    else
    {
        groupFlag = groupFlag & (~( 1 << m_id));
        std::bitset<32> x(groupFlag);
  //      cout << x << endl;
    }
    return flag;
*/
}

void EG_Toggle::setTextures(GLuint bgTexId, GLuint highlightTexId, GLuint pressedTexId)
{
    m_rectTexture = bgTexId;
    m_highlightTexture = highlightTexId;
    m_pressedTexture = pressedTexId;
}

void EG_Toggle::setColors(glm::vec3 bgColor, glm::vec3 highlightColor, glm::vec3 pressedColor)
{
    m_rectColor = bgColor;
    m_highlightColor = highlightColor;
    m_pressedColor = pressedColor;
}


void EG_Toggle::render(pipeline& p, EG_Renderer* r)
{
    r->enableShader();

    if(m_isInside && m_down)
        r->setData(RENDER_PASS1, "u_color", m_highlightColor);
    else if (m_down)
        r->setData(RENDER_PASS1, "u_color", m_pressedColor);
    else
        r->setData(RENDER_PASS1, "u_color", m_rectColor);

    EG_Control::renderSingle(p, r, m_rect);
    r->disableShader();
}


int EG_Toggle::getType()
{
    return TOGGLE;
}

