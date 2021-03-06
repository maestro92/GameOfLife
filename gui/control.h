#ifndef GUI_CONTROL_H_
#define GUI_CONTROL_H_

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

enum TEXT_LAYOUT
{
    LEFT_ALIGNED,
    TOP_ALIGNED,
    CENTER,
};


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

        void setTextLayout(bool setLineBreakFlag, int xLayoutFlag, int yLayoutFlag);
        void setRectTextLayout(LineBreakInfo& lineBreakInfo, float& startingX, float& startingY,
                                string text, float fontSize, Rect rect, bool setLineBreakFlag, int xLayoutFlag, int yLayoutFlag);

        void updateLineBreakInfo();

        void setFont(int size, glm::vec3 color);

        GLuint m_rectTexture;
        std::function<void()> m_funcCallBack;


        inline int toGUICoord(int y)
        {
            return Control::m_screenHeight - y;
        }

        inline float toGUICoord(float y)
        {
            return Control::m_screenHeight - y;
        }

        float computeCenteredTextStartingX(float textWidth, float rectWidth, float offsetX = 0);
        float computeCenteredTextStartingX(string text, float fontSize, float rectWidth, float offsetX = 0);

        float computeCenteredTextStartingY(float textHeight, float fontSize, float rectHeight, float offsetY = 0);
        float computeCenteredTextStartingY(string text, float fontSize, float rectHeight, float offsetY = 0);


        void emptyOnClick();
        static void init(string font, int size, int screenWidth, int screenHeight);

        static TextEngine m_textEngine;
    protected:
        bool m_isInside;
        int m_id;
        string m_text;
        Rect m_rect;
        Font m_font;

        glm::vec3 m_rectColor;

        vector<LineBreakInfo> m_lineBreakInfos;
        vector<float> m_textStartingXs;
        vector<float> m_textStartingYs;


        /// http://stackoverflow.com/questions/7083612/defining-a-static-variable-of-base-class

        static pipeline m_pipeline;
        static int m_screenWidth;
        static int m_screenHeight;
        static QuadModel m_quadModel;
        static Renderer r_coloredRectRenderer;        static Renderer r_texturedRectRenderer;
        static Renderer r_listBoxHighlightRenderer;
};



#endif // EG_GUI_CONTROLS
