#ifndef SCREEN_RENDER_INFO_H_
#define SCREEN_RENDER_INFO_H_

#include "EG_QuadModelABS.h"
#include "pipeline.h"

struct ScreenRenderInfo
{
    EG_QuadModelABS q;
    pipeline p;
    int w;
    int h;

    ScreenRenderInfo()
    {

    }

    ScreenRenderInfo(int screenWidth, int screenHeight)
    {
        w = screenWidth;
        h = screenHeight;

        p.matrixMode(PROJECTION_MATRIX);
        p.loadIdentity();
        p.ortho(0, w, 0, h, -1, 1);

        p.matrixMode(MODEL_MATRIX);
        p.loadIdentity();

        q.init(1,1);
    }
};
#endif // SCREEN_RENDER_INFO


