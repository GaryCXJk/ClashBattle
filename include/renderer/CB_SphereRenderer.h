#ifndef CB_SPHERERENDERER_H
#define CB_SPHERERENDERER_H

#include "CB_Renderer.h"
#include "CB_SpriteSheet.h"

struct CB_SphereRendererData
{
    double radius;
    uint16_t slices;
    uint16_t stacks;
    bool vertexNormals;
    CB_SpriteSheet * sheet;
    vector<string> sides;
    uint32_t color;
    CB_SphereRendererData()
    {
        color = 0xFFFFFFFF;
    }
};

class CB_SphereRenderer : public CB_Renderer
{
    public:
        CB_SphereRenderer();
        virtual ~CB_SphereRenderer();
        virtual void render(CB_RenderDataRel data);
        virtual void renderShader(CB_RenderDataRel data);

        void addSphere(double x, double y, double z, double radius, uint16_t slices, uint16_t stacks, CB_SpriteSheet * sheet, vector<string> sides, bool vertexNormals);
        void addSphere(double x, double y, double z, double radius, uint16_t slices, uint16_t stacks, uint32_t color, bool vertexNormals);
        void addSphere(double x, double y, double z, double radius, uint16_t slices, uint16_t stacks, CB_SpriteSheet * sheet, vector<string> sides, uint32_t color, bool vertexNormals);
        CB_RenderDataRel getSphere(double x, double y, double z, double radius, uint16_t slices, uint16_t stacks, CB_SpriteSheet * sheet, vector<string> sides, uint32_t color, bool vertexNormals);
    protected:
    private:
};

#endif // CB_SPHERERENDERER_H
