#ifndef EG_RECT_H_
#define EG_RECT_H_

#include "define.h"

struct EG_Rect
{
    int x;
    int y;
    int w;
    int h;

    EG_Rect()
    {
        set(0, 0, 1, 1);
    }

    EG_Rect(int x, int y, int w, int h)
    {
        set(x, y, w, h);
    }

    void set(int x, int y, int w, int h)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }
};

#endif // EG_RECT_H_
