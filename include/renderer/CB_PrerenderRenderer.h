#ifndef CB_PRERENDERRENDERER_H
#define CB_PRERENDERRENDERER_H

#include "CB_Renderer.h"


class CB_PrerenderRenderer : public CB_Renderer
{
    public:
        CB_PrerenderRenderer();
        virtual ~CB_PrerenderRenderer();
        virtual void render(CB_RenderDataRel data);
        virtual void renderShader(CB_RenderDataRel data);
    protected:
    private:
};

#endif // CB_PRERENDERRENDERER_H
