#ifndef CB_DEPTHSCALERENDERER_H
#define CB_DEPTHSCALERENDERER_H

#include "ClashBattle.h"
#include "CB_Renderer.h"
#include "CB_Screen.h"

struct CB_DepthScaleRendererData
{
    CB_RenderDataRel childData;
    bool orthoIsBase;
    CB_DepthScaleRendererData()
    {
        orthoIsBase = true;
    }
};

class CB_DepthScaleRenderer : public CB_Renderer
{
    public:
        CB_DepthScaleRenderer();
        virtual ~CB_DepthScaleRenderer();
        virtual void render(CB_RenderDataRel _data);
        virtual void renderShader(CB_RenderDataRel _data);
        CB_RenderDataRel getDepthScaleRenderData(double x, double y, double z, CB_RenderDataRel childData);
        CB_RenderDataRel getDepthScaleRenderData(double x, double y, double z, CB_RenderDataRel childData, bool orthoIsBase);
    protected:
    private:
};

#endif // CB_DEPTHSCALERENDERER_H
