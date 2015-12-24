
#ifndef EG_GUI_CONTROL_H_
#define EG_GUI_CONTROL_H_


#include "pipeline.h"
#include "define.h"
#include "utility.h"
#include "EG_QuadModelABS.h"
#include "text_engine.h"
#include "rect.h"

#define NO_SDL_GLEXT
#include <GL/glew.h>

#include "define.h"
#include <iostream>
#include <string>
#include <bitset>

using namespace std;




class Control
{
    public:

        enum CONTROL_TYPE
        {   LABEL = 0,
            BUTTON,
            LIST_BOX,
            SLIDER,
            TOGGLE,
        };

        Control();
        Control(string text, int x, int y, int width, int height, glm::vec3 color);

        virtual ~Control();

        // for labels, or basic controls, there'll only be one background
        virtual void setTexture(GLuint id);

        // assuming that each vertex will only have one color, so i'm gonna just pass one color in
        virtual void setColor(glm::vec3 color);

        virtual bool update(MouseState & state);
        virtual bool update(MouseState & state, unsigned int& groupFlag);

        static void renderSingle(pipeline& p,
                                 Renderer* r,
                                 Rect& rect);

        virtual void render(pipeline& p, Renderer* r);




        virtual int getType() = 0;
        void setID(int& ID);
        void setRect(int x, int y, int w, int h);
        void setText(string text);


        GLuint m_rectTexture;
        bool m_isInside;
        int m_id;
        string m_text;
        Rect m_rect;
        glm::vec3 m_rectColor;

        /// http://stackoverflow.com/questions/7083612/defining-a-static-variable-of-base-class

        static void init(string font, int size, int sreenWidth, int screenHeight);
        static TextEngine m_textEngine;
        static EG_QuadModelABS m_quadModel;

};



#endif // EG_GUI_CONTROLS
