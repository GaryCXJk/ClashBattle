#ifndef CB_BOXRENDERER_H
#define CB_BOXRENDERER_H

#include "CB_Renderer.h"
#include "CB_Texture.h"
#include "CB_SpriteSheet.h"

struct CB_BoxRendererData
{
    double x;
    double y;
    double z;
    double w;
    double h;
    double d;
    bool vertexNormals;
    CB_SpriteSheet * sheet;
    string sides[6];
    uint32_t color;
    CB_BoxRendererData()
    {
        color = 0xFFFFFFFF;
    }
};

class CB_BoxRenderer : public CB_Renderer
{
    public:
        CB_BoxRenderer();
        virtual ~CB_BoxRenderer();
        virtual void render(CB_RenderDataRel data);
        virtual void renderShader(CB_RenderDataRel data);
        virtual CB_RenderDataRel prerender(CB_RenderDataRel data);

        void addBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, CB_SpriteSheet * sheet, string * sides, bool vertexNormals);
        void addBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, uint32_t color, bool vertexNormals);
        void addBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, CB_SpriteSheet * sheet, string * sides, uint32_t color, bool vertexNormals);
        CB_RenderDataRel getBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, CB_SpriteSheet * sheet, string * sides, bool vertexNormals);
        CB_RenderDataRel getBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, uint32_t color, bool vertexNormals);
        CB_RenderDataRel getBox(double xOrig, double yOrig, double zOrig, double x, double y, double z, double w, double h, double d, CB_SpriteSheet * sheet, string * sides, uint32_t color, bool vertexNormals);
    protected:
    private:
};

#endif // CB_BOXRENDERER_H
