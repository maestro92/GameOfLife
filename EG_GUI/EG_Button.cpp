#include "EG_Button.h"


EG_Button::EG_Button()
{

}


EG_Button::EG_Button(string text, int x, int y, int width, int height, glm::vec3 c) :
    EG_Control(text, x, y, width, height, c)
{
    m_down = false;
    m_highlightTexture = -1;
    m_pressedTexture = -1;
}


bool EG_Button::update(MouseState & state)
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



bool EG_Button::update(MouseState & state, unsigned int& groupFlag)
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

void EG_Button::setTextures(GLuint bgTexId, GLuint highlightTexId, GLuint pressedTexId)
{
    m_rectTexture = bgTexId;
    m_highlightTexture = highlightTexId;
    m_pressedTexture = pressedTexId;
}

void EG_Button::setColors(glm::vec3 bgColor, glm::vec3 highlightColor, glm::vec3 pressedColor)
{
    m_rectColor = bgColor;
    m_highlightColor = highlightColor;
    m_pressedColor = pressedColor;
}


void EG_Button::render(pipeline& p, EG_Renderer* r)
{
    r->enableShader();

    if(m_isInside && !m_down)
        r->setData(RENDER_PASS1, "u_color", m_highlightColor);
    else if (m_down)
        r->setData(RENDER_PASS1, "u_color", m_pressedColor);
    else
        r->setData(RENDER_PASS1, "u_color", m_rectColor);

    EG_Control::renderSingle(p, r, m_rect);
    r->disableShader();

 //   cout << "offset_x " << offset_x << endl;
 //   cout << "offset_y " << offset_y << endl;

 //   EG_Control::m_textEngine.render(m_pipeline, offset_x, offset_y, m_text.c_str());

    /*
    Renderer->enableShader(RenderPassID);

    if(m_isInside && !m_down)
    {
        p.pushMatrix();
            p.scale(m_rect.w, m_rect.y, 0);
            p.translate(m_rect.x, m_rect.y, 0);
            Renderer->loadUniformLocations(p, RenderPassID);
            m_quadModel.render();
        p.popMatrix();



        float offset_x = 0.025 * m_rect.w;
        float offset_y = 0.05 * m_rect.h;

        m_pipeline.pushMatrix();
            m_pipeline.translate( glm::vec3(m_rect.x + offset_x, m_rect.y + offset_y, 0) );
            m_pipeline.scale(0.95,0.9,1.0);
            EG_Control::customMatrixRender(m_pipeline, Renderer, RENDER_PASS1);
        m_pipeline.popMatrix();

    }


    else if (m_down)
    {
        p_modelPtr = &m_pressedQuadModel;
        EG_Control::render(m_pipeline, Renderer, RENDER_PASS1, p_modelPtr);
    }
    else
        EG_Control::render(m_pipeline, Renderer, RENDER_PASS1);



    int offset_x = computeTextStartingX(m_text);
    int offset_y = computeTextStartingY();


    Renderer->disableShader(RenderPassID);

 //   cout << "offset_x " << offset_x << endl;
 //   cout << "offset_y " << offset_y << endl;

 //   EG_Control::m_textEngine.render(m_pipeline, offset_x, offset_y, m_text.c_str());
*/
}


int EG_Button::getType()
{
    return BUTTON;
}

