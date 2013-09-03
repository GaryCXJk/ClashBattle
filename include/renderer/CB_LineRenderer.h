#ifndef CB_LINERENDERER_H
#define CB_LINERENDERER_H

#include "CB_Renderer.h"

struct CB_LineRendererData
{
    CB_Vector3D start;
    CB_Vector3D end;
    double width;
    uint32_t color;
    CB_LineRendererData()
    {
        width = 1;
        color = 0xFFFFFFFF;
    }
};

class CB_LineRenderer : public CB_Renderer
{
    public:
        CB_LineRenderer();
        virtual ~CB_LineRenderer();
        virtual void render(CB_RenderDataRel data);
        virtual void renderShader(CB_RenderDataRel data);

        void addLine(double xOrig, double yOrig, double zOrig, double xStart, double yStart, double zStart, double xEnd, double yEnd, double zEnd);
        void addLine(double xOrig, double yOrig, double zOrig, double xStart, double yStart, double zStart, double xEnd, double yEnd, double zEnd, double width);
        void addLine(double xOrig, double yOrig, double zOrig, double xStart, double yStart, double zStart, double xEnd, double yEnd, double zEnd, double width, uint32_t color);
        CB_RenderDataRel getLine(double xOrig, double yOrig, double zOrig, double xStart, double yStart, double zStart, double xEnd, double yEnd, double zEnd, double width, uint32_t color);
    protected:
    private:
};

#endif // CB_LINERENDERER_H
