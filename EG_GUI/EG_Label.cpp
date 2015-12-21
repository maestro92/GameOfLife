#include "EG_Label.h"

EG_Label::EG_Label()
{

}

EG_Label::EG_Label(string text, int x, int y, int width, int height, glm::vec3 color) :
          EG_Control(text, x, y, width, height, color)
{

}

int EG_Label::getType()
{
    return LABEL;
}
