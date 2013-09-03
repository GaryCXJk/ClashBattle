#ifndef CB_TILE_H
#define CB_TILE_H
#include "ClashBattle.h"
#include "CB_CollisionBound.h"
#include "CB_Renderer.h"

class CB_Tile
{
    public:
        CB_Tile(uint8_t _width, uint8_t _height);
        CB_Tile(uint8_t _width, uint8_t _height, CB_CollisionEnum _type);
        CB_Tile(uint8_t _width, uint8_t _height, CB_CollisionEnum top, CB_CollisionEnum bottom, CB_CollisionEnum left, CB_CollisionEnum right);
        //CB_Tile(uint8_t width, uint8_t height, CB_CollisionEnum top, CB_CollisionEnum bottom, CB_CollisionEnum left, CB_CollisionEnum right, vector<CB_CollisionBound*> collisions);
        CB_Tile(uint8_t _width, uint8_t _height, CB_RenderDataRel _data);
        CB_Tile(uint8_t _width, uint8_t _height, CB_CollisionEnum _type, CB_RenderDataRel _data);
        CB_Tile(uint8_t _width, uint8_t _height, CB_CollisionEnum top, CB_CollisionEnum bottom, CB_CollisionEnum left, CB_CollisionEnum right, CB_RenderDataRel _data);
        //CB_Tile(uint8_t width, uint8_t height, CB_CollisionEnum top, CB_CollisionEnum bottom, CB_CollisionEnum left, CB_CollisionEnum right, vector<CB_CollisionBound*> collisions, CB_RenderDataRel data);
        virtual ~CB_Tile();
        void attachRenderData(CB_RenderDataRel _data);
        uint8_t getWidth(uint8_t s);
        uint8_t getHeight(uint8_t s);
        CB_CollisionEnum getSide(int side);
        void putCustomCollision(vector<CB_CollisionBound*> * boundList, uint32_t x, uint32_t y);
        void prepareRender(double x, double y, uint8_t roomTileSize);
        static CB_Tile * BLANK_TILE;
    protected:
    private:
        uint8_t width;
        uint8_t height;
        CB_CollisionEnum type[4];
        vector<CB_CollisionBound*> customCollision;
        CB_RenderDataRel refData;
};

#endif // CB_TILE_H
