#include "button.h"


Button::Button()
{

}


Button::Button(string text, int x, int y, int width, int height, FuncCallBack funcCallBack) :
    Control(text, x, y, width, height, BLUE)
{
    m_down = false;
    m_highlightTexture = -1;
    m_pressedTexture = -1;
    m_funcCallBack = funcCallBack;
}

Button::Button(string text, int x, int y, int width, int height, FuncCallBack funcCallBack,
               glm::vec3 bgColor, glm::vec3 highlightColor, glm::vec3 pressedColor) : Button(text, x, y, width, height, funcCallBack)
{
    setColors(bgColor, highlightColor, pressedColor);
}

Button::Button(string text, int x, int y, int width, int height, FuncCallBack funcCallBack, std::function<void()> callBack,
               glm::vec3 bgColor, glm::vec3 highlightColor, glm::vec3 pressedColor) : Control(text, x, y, width, height, BLUE)
{
    m_down = false;
    m_highlightTexture = -1;
    m_pressedTexture = -1;

    m_funcCallBack = funcCallBack;
    m_callBack = callBack;
    setColors(bgColor, highlightColor, pressedColor);
}


bool Button::update(MouseState & state)
{
    Control::update(state);
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
            m_funcCallBack();
            if(m_callBack != NULL)
                m_callBack();
            return true;
        }
    }
    return false;
}



bool Button::update(MouseState & state, unsigned int& groupFlag)
{
    if(groupFlag & ( 1 << m_id) || (groupFlag==0) )
    {
        bool flag = update(state);
//        cout << "Flag is " << flag << endl;

        if(flag == true)
        {
            groupFlag = groupFlag | ( 1 << m_id);
         //   Utility::debug()
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
     //   Utility::debug()
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

void Button::setTextures(GLuint bgTexId, GLuint highlightTexId, GLuint pressedTexId)
{
    m_rectTexture = bgTexId;
    m_highlightTexture = highlightTexId;
    m_pressedTexture = pressedTexId;
}

void Button::setColors(glm::vec3 bgColor, glm::vec3 highlightColor, glm::vec3 pressedColor)
{
    m_rectColor = bgColor;
    m_highlightColor = highlightColor;
    m_pressedColor = pressedColor;
}


void Button::setFuncCallBack(FuncCallBack funcCallBack)
{
    m_funcCallBack = funcCallBack;
}


void Button::customRender()
{
    render();
}



void Button::render()
{
    Control::r_coloredRectRenderer.enableShader();

    if(m_isInside && !m_down)
        Control::r_coloredRectRenderer.setData(RENDER_PASS1, "u_color", m_highlightColor);
    else if (m_down)
        Control::r_coloredRectRenderer.setData(RENDER_PASS1, "u_color", m_pressedColor);
    else
        Control::r_coloredRectRenderer.setData(RENDER_PASS1, "u_color", m_rectColor);

    updatePipeline(&Control::r_coloredRectRenderer);
    m_quadModel.render();

    Control::m_textEngine.render(m_text, m_rect.x, m_rect.y, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
    Control::r_coloredRectRenderer.disableShader();

 //   cout << "offset_x " << offset_x << endl;
 //   cout << "offset_y " << offset_y << endl;

 //   Control::m_textEngine.render(m_pipeline, offset_x, offset_y, m_text.c_str());

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
            Control::customMatrixRender(m_pipeline, Renderer, RENDER_PASS1);
        m_pipeline.popMatrix();

    }


    else if (m_down)
    {
        p_modelPtr = &m_pressed;
        Control::render(m_pipeline, Renderer, RENDER_PASS1, p_modelPtr);
    }
    else
        Control::render(m_pipeline, Renderer, RENDER_PASS1);



    int offset_x = computeTextStartingX(m_text);
    int offset_y = computeTextStartingY();


    Renderer->disableShader(RenderPassID);

 //   cout << "offset_x " << offset_x << endl;
 //   cout << "offset_y " << offset_y << endl;

 //   Control::m_textEngine.render(m_pipeline, offset_x, offset_y, m_text.c_str());
*/
}


int Button::getType()
{
    return BUTTON;
}
