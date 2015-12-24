#ifndef LIST_BOX_H
#define LIST_BOX_H

#include <vector>

#include "Rect.h"
#include "Control.h"

using namespace std;

class ListBox : public Control
{
    public:
        ListBox();
        ListBox(string text, int x, int y, int width, int height, glm::vec3 color, int colNum);

        void addItem(string item);
        void removeItem(int index);
        void setCurrent(int index);

        void setColors(glm::vec3 rectColor, glm::vec3 itemRectColor);

        int getIndex();
        int getCount();

        virtual bool update(MouseState & state);

        void render (pipeline& p, Renderer* r);
        virtual int getType();

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

        vector<string> m_items;
};




#endif // EG_BUTTON_H
