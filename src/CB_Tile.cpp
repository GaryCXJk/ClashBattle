#include "CB_Tile.h"

CB_Tile * CB_Tile::BLANK_TILE = new CB_Tile(1, 1, CB_COLLISION_NONE);

CB_Tile::CB_Tile(uint8_t _width, uint8_t _height)
{
    width = _width;
    height = _height;
}

CB_Tile::CB_Tile(uint8_t _width, uint8_t _height, CB_CollisionEnum _type)
{
    width = _width;
    height = _height;

    type[0] = _type;
    type[1] = _type;
    type[2] = _type;
    type[3] = _type;
}

CB_Tile::CB_Tile(uint8_t _width, uint8_t _height, CB_CollisionEnum top, CB_CollisionEnum bottom, CB_CollisionEnum left, CB_CollisionEnum right)
{
    width = _width;
    height = _height;

    type[0] = top;
    type[1] = bottom;
    type[2] = left;
    type[3] = right;
}

CB_Tile::CB_Tile(uint8_t _width, uint8_t _height, CB_RenderDataRel _data)
{
    width = _width;
    height = _height;
    refData = _data;
}

CB_Tile::CB_Tile(uint8_t _width, uint8_t _height, CB_CollisionEnum _type, CB_RenderDataRel _data)
{
    width = _width;
    height = _height;

    type[0] = _type;
    type[1] = _type;
    type[2] = _type;
    type[3] = _type;

    refData = _data;
}

CB_Tile::CB_Tile(uint8_t _width, uint8_t _height, CB_CollisionEnum top, CB_CollisionEnum bottom, CB_CollisionEnum left, CB_CollisionEnum right, CB_RenderDataRel _data)
{
    width = _width;
    height = _height;

    type[0] = top;
    type[1] = bottom;
    type[2] = left;
    type[3] = right;

    refData = _data;
}

CB_Tile::~CB_Tile()
{
}

void CB_Tile::attachRenderData(CB_RenderDataRel _data)
{
    refData = _data;
}

uint8_t CB_Tile::getWidth(uint8_t s)
{
    uint8_t w = width / s;
    if(width % s > 0)
    {
        ++w;
    }
    return w;
}

uint8_t CB_Tile::getHeight(uint8_t s)
{
    uint8_t h = height / s;
    if(height % s > 0)
    {
        ++h;
    }
    return h;
}

CB_CollisionEnum CB_Tile::getSide(int side)
{
    return type[side];
}

void CB_Tile::putCustomCollision(vector<CB_CollisionBound*> * boundList, uint32_t x, uint32_t y)
{
    vector<CB_CollisionBound*>::iterator it;
    for(it = customCollision.begin(); it < customCollision.end(); it++)
    {
        CB_CollisionBound * colRef = *it;
        CB_Vector2D vec1 = colRef->getFirst();
        CB_Vector2D vec2 = colRef->getSecond();
        CB_CollisionBound * collision = new CB_CollisionBound();
        collision->setBound(x + vec1.x, y - vec1.y, x + vec2.x, y - vec2.y);
        boundList->insert(boundList->end(), collision);
    }
}

void CB_Tile::prepareRender(double x, double y, uint8_t roomTileSize)
{
    if(refData.renderer == 0)
    {
        return;
    }
    CB_RenderDataRel _data = refData;
    _data.position.x+= x;
    _data.position.y+= y;
    _data.sharedUserdata = true;
    _data.tileSize*= CB_Renderer::getScale((double)roomTileSize);
    CB_Renderer::listRender(_data);
}
