#ifndef CB_ROOM_H
#define CB_ROOM_H
#include "ClashBattle.h"
#include "CB_Entity.h"
#include "CB_CollisionBound.h"
#include "CB_Tile.h"

class CB_Room
{
    public:
        CB_Room(uint32_t w, uint32_t h, uint8_t s);
        CB_Room(uint32_t w, uint32_t h, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t s);
        virtual ~CB_Room();
        void optimize();
        void optimize(bool force);
        void addTile(uint32_t x, uint32_t y, CB_Tile * tile);
        void removeTile(uint32_t x, uint32_t y);
        CB_Tile * getTileAt(uint32_t x, uint32_t y);
        bool isFree(uint32_t x, uint32_t y, CB_Tile * tile);
        bool isFree(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
        vector<CB_CollisionBound*> getBounds();
        void addProp(CB_RenderDataRel data);
        uint32_t getScreenWidth();
        uint32_t getScreenHeight();
        uint32_t getScreenLeft();
        uint32_t getScreenTop();
        uint32_t getWidth();
        uint32_t getHeight();
        uint8_t getTileSize();
        void prepareRender();
    protected:
    private:
        void addBound(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, CB_CollisionEnum tileEnum);
        vector<CB_Entity*> entityList;
        vector<CB_CollisionBound*> boundList;
        vector<CB_RenderDataRel> propsList;
        CB_Tile** tileMap;
        uint8_t tileSize;
        uint32_t xLeft;
        uint32_t yTop;
        uint32_t xRight;
        uint32_t yBottom;
        uint32_t width;
        uint32_t height;
        bool isOptimized;
        SDL_mutex * roomMutex;
};

#endif // CB_ROOM_H
