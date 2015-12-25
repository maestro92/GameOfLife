#ifndef GENERAL_RENDERER_H_
#define GENERAL_RENDERER_H_

#include "renderer.h"

class GeneralRenderer : public Renderer
{
    public:
        GeneralRenderer();
        ~GeneralRenderer();

        virtual void loadUniformLocations();
        virtual void loadUniformLocations(int pass);

        virtual void loadUniformLocations(pipeline& p);
        virtual void loadUniformLocations(pipeline& p, int pass);
};
#endif // EG_FIRE_EFFECT_RENDERER_H_
