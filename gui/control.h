
#ifndef EG_GUI_CONTROL_H_
#define EG_GUI_CONTROL_H_


#include "pipeline.h"
#include "define.h"
#include "utility.h"
#include "quad_model.h"
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


        virtual void render() = 0;
        virtual void customRender();

        void updatePipeline(Renderer* r);
        void updatePipeline(Renderer* r, Rect rect);
        /*
        virtual void render(Renderer* r, Rect rect);
        virtual void renderSingle(Renderer* r, Rect rect);
*/
/*
        virtual void renderColored();
        virtual void renderColoredSingle();
        virtual void renderColored(Rect rect);
        virtual void renderColoredSingle(Rect rect);

        virtual void renderTextured();
        virtual void renderTexturedSingle();
        virtual void renderTextured(Rect rect);
        virtual void renderTexturedSingle(Rect rect);
*/
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
        static pipeline m_pipeline;
        static TextEngine m_textEngine;
        static QuadModel m_quadModel;
        static GeneralRenderer r_coloredRectRenderer;        static GeneralRenderer r_texturedRectRenderer;
        static GeneralRenderer r_listBoxHighlightRenderer;
};



#endif // EG_GUI_CONTROLS
