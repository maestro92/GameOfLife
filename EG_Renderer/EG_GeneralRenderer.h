#ifndef EG_GENERAL_RENDERER_H_
#define EG_GENERAL_RENDERER_H_

#include "EG_Renderer.h"

class EG_GeneralRenderer : public EG_Renderer
{
    public:
        EG_GeneralRenderer();
        ~EG_GeneralRenderer();
        void init(int nShaders);
        virtual void loadUniformLocations(int pass);
        virtual void loadUniformLocations(pipeline& p, int pass);
};
#endif // EG_FIRE_EFFECT_RENDERER_H_