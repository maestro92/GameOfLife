#include "Label.h"

Label::Label()
{

}

Label::Label(string text, int x, int y, int width, int height, glm::vec3 color) :
          Control(text, x, y, width, height, color)
{

}

int Label::getType()
{
    return LABEL;
}


void Label::render()
{

}
