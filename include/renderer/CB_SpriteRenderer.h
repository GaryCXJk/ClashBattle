#ifndef CB_SPRITERENDERER_H
#define CB_SPRITERENDERER_H

#include "ClashBattle.h"
#include "CB_Renderer.h"
#include "CB_SpriteSheet.h"

struct CB_SpriteRendererData
{
    double pitch;
    double yaw;
    double roll;
    CB_SpriteSheet * sheet;
    string sprite;
    bool mirrored;
};


class CB_SpriteRenderer : public CB_Renderer
{
    public:
        CB_SpriteRenderer();
        virtual ~CB_SpriteRenderer();
        virtual void render(CB_RenderDataRel data);
        virtual void renderShader(CB_RenderDataRel data);

        void addSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite);
        void addSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite, bool mirrored);
        CB_RenderDataRel getSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite);
        CB_RenderDataRel getSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite, bool mirrored);
        void addSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite, CB_RenderList * renderList);
        void addSprite(double x, double y, double z, double pitch, double yaw, double roll, CB_SpriteSheet * sheet, string sprite, bool mirrored, CB_RenderList * renderList);
    protected:
    private:
};

#endif // CB_SPRITERENDERER_H
