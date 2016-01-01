#include "list_box.h"



ListBox::ListBox()
{
}

ListBox::ListBox(string text, int x, int y, int width, int height,
                 glm::vec3 color, glm::vec3 itemRectColor, int colNum, std::function<void()> callBack) :
                Control(text, x, y, width, height, color)
{
    m_colNum = colNum;

    m_curIndex = 0;
    m_curIndexX = 0;
    m_curIndexY = 0;

    m_curRowNum = 0;
    m_curColNum = 0;

    m_itemWidth = (float)((float)width / (float)m_colNum);
    m_itemHeight = 75;

    setColors(color, itemRectColor);
    m_funcCallBack = callBack;
}


void ListBox::setContent(vector<GOLModel*> models)
{
    int count = models.size();
    for(int i=0; i<count; i++)
    {
        addItem(models[i]->getName(), glm::vec2(models[i]->m_width, models[i]->m_height), WHITE, models[i]->getTexture());
    }
}

void ListBox::addItem(string text, glm::vec2 dim, glm::vec3 color, GLuint texID)
{
    ListBoxItem item(text, dim, color, texID);
    m_items.push_back(item);

    if(m_curColNum == m_colNum-1)
    {
        m_curRowNum++;
        m_curColNum = 0;
    }
    else
        m_curColNum++;
}



void ListBox::removeItem(int index)
{
/// vector for loop vs iterator
/// http://stackoverflow.com/questions/131241/why-use-iterators-instead-of-array-indices

    int i=0;
    for(vector<ListBoxItem>::iterator it = m_items.begin(); it != m_items.end(); it++)
    {
        if(i==index)
        {
            m_items.erase(it);
            break;
        }
        i++;
    }

    /// if the last item is the item being removed

    if(index >= (int) m_items.size())
        m_curIndex = (int)m_items.size() - 1;
}

/*
void ListBox::removeItem(int index)
{
/// vector for loop vs iterator
/// http://stackoverflow.com/questions/131241/why-use-iterators-instead-of-array-indices

    int i=0;
    for(vector<string>::iterator it = m_items.begin(); it != m_items.end(); it++)
    {
        if(i==index)
        {
            m_items.erase(it);
            break;
        }
        i++;
    }

    /// if the last item is the item being removed

    if(index >= (int) m_items.size())
        m_curIndex = (int)m_items.size() - 1;
}
*/

void ListBox::setCurrent(int index)
{
    m_curIndex = index;
}

int ListBox::getIndex()
{
    return m_curIndex;
}

int ListBox::getCount()
{
    return (int)m_items.size();
}

void ListBox::setColors(glm::vec3 rectColor, glm::vec3 itemRectColor)
{
    m_rectColor = rectColor;
    m_itemRectColor = itemRectColor;
}

bool ListBox::update(MouseState & state)
{
    Control::update(state);

    int x = state.m_pos.x;
    int y = state.m_pos.y;



    if( m_isInside && state.m_leftButtonDown)
    {
        int x_index = (x - m_rect.x) / m_itemWidth;
        int y_index = (m_rect.y + m_rect.h - y) / m_itemHeight;


        bool bx = x_index >= 0 && x_index < m_colNum;
        bool by = y_index >= 0 && y_index < ( (int)m_items.size() / m_colNum) ;


        if( bx && by )
        {
            m_curIndex = y_index * m_colNum + x_index;

        //    Utility::debug("m_curIndex", m_curIndex);
        //    Utility::debug("xi, yi", glm::vec2(x_index, y_index));

            m_curIndexX = x_index;
            m_curIndexY = y_index;
            m_funcCallBack();
            return true;
        }



        /*
        int tempIndex = (m_rect.y + m_rect.h - y) / m_itemHeight;

        if( tempIndex >= 0 && tempIndex < (int)m_items.size())
        {
            m_curIndex = tempIndex;
            return true;
        }
        */

    }
    return false;
}


void ListBox::render()
{
    Control::r_coloredRectRenderer.enableShader();
        Control::r_coloredRectRenderer.setData(RENDER_PASS1, "u_color", m_rectColor);
        updatePipeline(&Control::r_coloredRectRenderer);
        m_quadModel.render();

        // renderColoredSingle(m_rect);


        // render the itemRectBox
        if( m_curIndex >= 0)
        {
            int offset_x = m_rect.x + m_curIndexX * m_itemWidth;
            int offset_y = m_rect.y + m_rect.h - ((m_curIndexY + 1) * m_itemHeight);

            Rect itemRect(offset_x, offset_y, m_itemWidth, m_itemHeight);
            Control::r_coloredRectRenderer.setData(RENDER_PASS1, "u_color", m_itemRectColor);
            updatePipeline(&Control::r_coloredRectRenderer, itemRect);
            m_quadModel.render();


            /*
            int offset_x = m_rect.x;
            int offset_y = m_rect.y + m_rect.h - ((m_curIndex + 1) * m_itemHeight);

            Rect itemRect(offset_x, offset_y, m_itemWidth.w, m_itemHeight);
            r->setData(RENDER_PASS1, "u_color", m_itemRectColor);
            Control::renderSingle(p, r, itemRect);
            */
        }

    Control::r_coloredRectRenderer.disableShader();


    for(int y = 0; y < m_curRowNum; y++)
    {
        for(int x = 0; x < m_colNum; x++)
        {
            int index = y * m_colNum + x;
            if( index == m_items.size())
            {
                break;
            }
            else
            {
                int offset_x = m_rect.x + x * m_itemWidth;
                int offset_y = m_rect.y + m_rect.h - ((y + 1) * m_itemHeight) + 10;

                Control::m_textEngine.render(m_items[index].m_text, offset_x, offset_y, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
            }
        }
    }


    /*
    Control::render(m_pipeline, Renderer, RENDER_PASS1);
    int offset_x;
    int offset_y = 0;
 //   Control::m_textEngine.render(m_pipeline, offset_x, offset_y, m_label.c_str());
    if( m_curIndex >= 0)
    {
        offset_x = 0;

        offset_y = m_curIndex * m_itemHeight;


        Renderer->enableShader(RenderPassID);
            m_pipeline.pushMatrix();
                glm::vec3 shift(offset_x, offset_y, 0);
                m_pipeline.translate(shift);
                Renderer->loadUniformLocations(m_pipeline, RenderPassID);
                m_cur.render();
            m_pipeline.popMatrix();
        Renderer->disableShader(RenderPassID);
    }


    for (int i = 0; i< (int) m_items.size(); i++)
    {

   //     Control::m_textEngine.render(m_pipeline, offset_x, offset_y, m_label.c_str());
    }
    */
}


void ListBox::customRender()
{
    Renderer* r = &Control::r_texturedRectRenderer;
    Renderer* hlr = &Control::r_listBoxHighlightRenderer;

        for(int y = 0; y < m_curRowNum; y++)
        {
            for(int x = 0; x < m_colNum; x++)
            {
                int index = y * m_colNum + x;

          //      Utility::debug("index", index);

                if( index == m_items.size())
                    break;

                // render texture
                int offset_x = m_rect.x + x * m_itemWidth;
                int offset_y = m_rect.y + m_rect.h - ((y + 1) * m_itemHeight);
                Rect itemRect(offset_x, offset_y, m_itemWidth, m_itemHeight);

          //      Utility::debug("offset_x", offset_x);
        //        Utility::debug("offset_y", offset_y);
/*
                if (index == m_curIndex && m_curIndex >= 0)
                    r->setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, m_items[index].m_textureID);

                else
                    r->setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, m_items[index].m_textureID);


                updatePipeline(r, itemRect);
                m_quadModel.render();
*/

                if (index == m_curIndex && m_curIndex >= 0)
                {
                    float gap = 2;
                    hlr->enableShader();
                        hlr->setData(RENDER_PASS1, "u_x1", itemRect.x + gap);
                        hlr->setData(RENDER_PASS1, "u_x2", itemRect.x + itemRect.w - gap);

                        hlr->setData(RENDER_PASS1, "u_y1", itemRect.y + gap);
                        hlr->setData(RENDER_PASS1, "u_y2", itemRect.y + itemRect.h - gap);

                    updatePipeline(hlr, itemRect);
                    m_quadModel.render();
                    hlr->disableShader();
                }

                r->enableShader();
                    Rect tempRect = getListBoxItemModelRect(itemRect, index);
/*
                    Rect tempRect = itemRect;
                    tempRect.x = itemRect.x + 45;
                    tempRect.y = itemRect.y + 35;
                    tempRect.w = (int)(m_items[index].m_dim.x);
                    tempRect.h = (int)(m_items[index].m_dim.y);
*/
//                    tempRect.w = (int)(m_items[index].m_dim.x * 1.2);
//                    tempRect.h = (int)(m_items[index].m_dim.y * 1.2);
                    r->setData(RENDER_PASS1, "u_texture", 0, GL_TEXTURE0, m_items[index].m_textureID);
                    updatePipeline(r, tempRect);
                    m_quadModel.render();

                r->disableShader();

                // render text
                offset_x = m_rect.x + x * m_itemWidth;
                offset_y = m_rect.y + m_rect.h - ((y + 1) * m_itemHeight) + 10;

                Control::m_textEngine.render(m_items[index].m_text, offset_x, offset_y, 0.4f, glm::vec3(0.5, 0.8f, 0.2f));
            }
        }
}

Rect ListBox::getListBoxItemModelRect(Rect& itemRect, int index)
{
    Rect modelRect = itemRect;

    int offset_x = (itemRect.w - m_items[index].m_dim.x)/2;
    int offset_y = (itemRect.h - m_items[index].m_dim.y)*2/3;

    modelRect.x = itemRect.x + offset_x;
    modelRect.y = itemRect.y + offset_y;
    modelRect.w = (int)(m_items[index].m_dim.x);
    modelRect.h = (int)(m_items[index].m_dim.y);

    return modelRect;
}


int ListBox::getType()
{
    return LIST_BOX;
}

