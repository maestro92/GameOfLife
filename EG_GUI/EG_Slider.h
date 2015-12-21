#ifndef EG_SLIDER_H_
#define EG_SLIDER_H_

#include "EG_Control.h"


using namespace std;

class EG_Slider : public EG_Control
{


    public:
        enum SLIDER_VALUE_TYPE
        {
            INT_TYPE = 0,
            FLOAT_TYPE
        };


        EG_Slider();
        EG_Slider(string label, int x, int y, int width, int height,
                  glm::vec3 color, float min, float max);

        void setDefaultValue(float value);
        void setValue(float *value);

        void setColors(glm::vec3 rectColor, glm::vec3 sliderColor);

        void setMaxValue(float max);
        void setMinValue(float min);
        float getValue();

        virtual bool update(MouseState &state);
        virtual bool update(MouseState &state, unsigned int& groupFlag);
        virtual bool update1(MouseState & state, unsigned int& groupFlag);

        virtual void render(pipeline& m_pipeline,
                            EG_Renderer* Renderer,
                            int RenderPassID);

        virtual int getType();
        void setValueType(int t);
        bool getDraggingFlag();

    protected:

        EG_Rect m_sliderQuadRect;
        glm::vec3 m_sliderColor;

        float m_defaultValue;
        float m_minValue;
        float m_maxValue;
        float*  m_current;
        bool m_dragging;
        int m_valueType;


};

#endif

