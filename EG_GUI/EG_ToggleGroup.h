#ifndef EG_TOGGLE_GROUP_H
#define EG_TOGGLE_GROUP_H

#include "EG_Control.h"

class EG_ToggleGroup : public EG_Control
{
    public:
        EG_Toggle();
        EG_Toggle(string text, int x, int y, int width, int height, glm::vec3 c);

        /// http://stackoverflow.com/questions/4271245/why-do-i-get-no-matching-function-when-i-inherit-this-function
        using EG_Control::update;

        virtual bool update(MouseState & state);
        virtual bool update(MouseState & state, unsigned int& groupFlag);

        void setTextures(GLuint bgTexId, GLuint highlightTexId, GLuint pressedTexId);
        void setColors(glm::vec3 bgColor, glm::vec3 highlightColor, glm::vec3 pressedColor);

        virtual void render(pipeline& p, EG_Renderer* r);

        virtual int getType();
};




#endif // EG_BUTTON_H
