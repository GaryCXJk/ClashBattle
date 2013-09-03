#ifndef CB_GROUPRENDERER_H
#define CB_GROUPRENDERER_H

#include "CB_Renderer.h"

struct CB_GroupRendererData
{
    CB_RenderList renderList;
    CB_Vector3D offset;
};

class CB_GroupRenderer : public CB_Renderer
{
    public:
        CB_GroupRenderer();
        virtual ~CB_GroupRenderer();
        virtual void render(CB_RenderDataRel _data);
        virtual void renderShader(CB_RenderDataRel _data);
        CB_RenderDataRel getGroup(double x, double y, double z, double offX, double offY, double offZ, CB_RenderList renderList);
    protected:
    private:
};

#endif // CB_GROUPRENDERER_H
