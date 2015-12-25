#ifndef LIST_BOX_H
#define LIST_BOX_H

#include <vector>

#include "Rect.h"
#include "Control.h"

using namespace std;


struct ListBoxItem
{
    string m_text;
    glm::vec2 m_dim;
    glm::vec3 m_color;
    GLuint m_textureID;
    GLuint m_highlightTextureID;

    ListBoxItem()
    {
        m_text = "Martin";
        m_dim = glm::vec2(5,5);
        m_color = BLUE;
        m_textureID = -1;
    }

    ListBoxItem(string text, glm::vec2 dim, glm::vec3 color, GLuint texture)
    {
        m_text = text;
        m_dim = dim;
        m_color = color;
        m_textureID = texture;
    }
};

class ListBox : public Control
{
    public:
        ListBox();
        ListBox(string text, int x, int y, int width, int height, glm::vec3 color, int colNum);

        void addItem(string text, glm::vec2 dim, glm::vec3 color, GLuint texID);

        void removeItem(int index);
        void setCurrent(int index);

        void setColors(glm::vec3 rectColor, glm::vec3 itemRectColor);

        int getIndex();
        int getCount();

        virtual bool update(MouseState & state);

//        void render (pipeline& p, Renderer* r);
        // virtual void renderTextured();
        void render();
        void customRender();

        virtual int getType();
        vector<ListBoxItem> m_items;



    protected:
        int m_curIndex;
        int m_curIndexX;
        int m_curIndexY;

        int m_colNum;

        int m_curRowNum;
        int m_curColNum;

        float m_itemWidth;
        float m_itemHeight;

        glm::vec3 m_itemRectColor;

  //      vector<string> m_items;

};




#endif // EG_BUTTON_H
