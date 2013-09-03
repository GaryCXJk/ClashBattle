#include "CB_Room.h"

CB_Room::CB_Room(uint32_t w, uint32_t h, uint8_t s)
{
    width = w;
    height = h;
    xRight = w;
    yBottom = h;
    tileSize = s;
    tileMap = new CB_Tile*[w * h];
    isOptimized = false;
    for(uint32_t i = 0; i < w * h; i++)
    {
        tileMap[i] = 0;
    }
    roomMutex = SDL_CreateMutex();
}

CB_Room::CB_Room(uint32_t w, uint32_t h, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint8_t s)
{
    xLeft = x1;
    yTop = y1;
    xRight = x2;
    yBottom = y2;
    width = w;
    height = h;
    tileSize = s;
    tileMap = new CB_Tile*[w * h];
    isOptimized = false;
    for(uint32_t i = 0; i < w * h; i++)
    {
        tileMap[i] = 0;
    }
    roomMutex = SDL_CreateMutex();
}

CB_Room::~CB_Room()
{
    delete tileMap;
}

void CB_Room::optimize()
{
    optimize(false);
}

void CB_Room::optimize(bool force)
{
    if(isOptimized && !force)
    {
        return;
    }
    boundList.clear();
    CB_CollisionEnum bTop[width * height];
    CB_CollisionEnum bBottom[width * height];
    CB_CollisionEnum bLeft[width * height];
    CB_CollisionEnum bRight[width * height];
    for(uint32_t i = 0; i < width * height; i++)
    {
        bTop[i] = CB_COLLISION_NONE;
        bBottom[i] = CB_COLLISION_NONE;
        bLeft[i] = CB_COLLISION_NONE;
        bRight[i] = CB_COLLISION_NONE;
    }

    uint8_t tW;
    uint8_t tH;

    CB_Tile * tile;
    for(uint32_t i = 0; i < width * height; i++)
    {
        uint32_t x = i % width;
        uint32_t y = i / width;
        SDL_mutexP(roomMutex);
        tile = tileMap[i];
        SDL_mutexV(roomMutex);
        if(tile == 0 || tile == CB_Tile::BLANK_TILE)
        {
            continue;
        }
        bTop[i] = tile->getSide(0);
        bBottom[i] = tile->getSide(1);
        bLeft[i] = tile->getSide(2);
        bRight[i] = tile->getSide(3);
        tW = tile->getWidth(tileSize);
        tH = tile->getHeight(tileSize);
        if(tW > width - x)
        {
            tW = width - x;
        }
        if(tH > height - y)
        {
            tH = height - y;
        }
        if(bLeft[i] == CB_COLLISION_DROPTHROUGH)
        {
            bLeft[i] = CB_COLLISION_NONE;
        }
        if(bRight[i] == CB_COLLISION_DROPTHROUGH)
        {
            bRight[i] = CB_COLLISION_NONE;
        }
        if(tW > 1 || tH > 1)
        {
            CB_CollisionEnum eXL = bLeft[i];
            CB_CollisionEnum eXR = bRight[i];
            CB_CollisionEnum eYT = bTop[i];
            CB_CollisionEnum eYB = bBottom[i];
            bRight[i] = CB_COLLISION_NONE;
            bBottom[i] = CB_COLLISION_NONE;
            for(uint32_t iY = 0; iY < tH; iY++)
            {
                uint32_t iX1 = i + iY * width;
                uint32_t iX2 = i + tW - 1 + iY * width;
                bLeft[iX1] = eXL;
                bRight[iX2] = eXR;

                if(x > 0 && bLeft[iX1] != CB_COLLISION_NONE)
                {
                    if(bRight[iX1 - 1] == bLeft[iX1])
                    {
                        bLeft[iX1] = CB_COLLISION_NONE;
                        bRight[iX1 - 1] = CB_COLLISION_NONE;
                    }
                }

                if(x < width - 1 && bRight[iX2] != CB_COLLISION_NONE)
                {
                    if(bLeft[iX2 + 1] == bRight[iX2])
                    {
                        bRight[iX2] = CB_COLLISION_NONE;
                        bLeft[iX2 + 1] = CB_COLLISION_NONE;
                    }
                }
            }
            for(uint32_t iX = 0; iX < tW; iX++)
            {
                uint32_t iY = i + iX;
                bTop[iY] = eYT;
                bBottom[i + iX + (tH - 1) * width] = eYB;

                if(y > 0 && bTop[iY] != CB_COLLISION_NONE)
                {
                    if(bBottom[iY - width] == bTop[iY] && bTop[i] != CB_COLLISION_DROPTHROUGH)
                    {
                        bTop[iY] = CB_COLLISION_NONE;
                        bBottom[iY - width] = CB_COLLISION_NONE;
                    }
                    else if(bBottom[iY - width] == CB_COLLISION_DROPTHROUGH)
                    {
                        bBottom[iY - width] = CB_COLLISION_NONE;
                    }
                    else if(bTop[iY] == CB_COLLISION_DROPTHROUGH && bBottom[iY - width] != CB_COLLISION_NONE)
                    {
                        bTop[iY] = CB_COLLISION_NONE;
                    }
                }
            }
            SDL_mutexP(roomMutex);
            for(uint32_t iY = 0; iY < tH; iY++)
            {
                for(uint32_t iX = 0; iX < tW; iX++)
                {
                    uint32_t iC = i + iX + iY * width;
                    if(tileMap[iC] == 0)
                    {
                        tileMap[iC] = CB_Tile::BLANK_TILE;
                    }
                }
            }
            SDL_mutexV(roomMutex);
        }
        else
        {
            if(y > 0 && bTop[i] != CB_COLLISION_NONE)
            {
                if(bBottom[i - width] == bTop[i] && bTop[i] != CB_COLLISION_DROPTHROUGH)
                {
                    bTop[i] = CB_COLLISION_NONE;
                    bBottom[i - width] = CB_COLLISION_NONE;
                }
                else if(bBottom[i - width] == CB_COLLISION_DROPTHROUGH)
                {
                    bBottom[i - width] = CB_COLLISION_NONE;
                }
                else if(bTop[i] == CB_COLLISION_DROPTHROUGH && bBottom[i - width] != CB_COLLISION_NONE)
                {
                    bTop[i] = CB_COLLISION_NONE;
                }
            }
            if(x > 0 && bLeft[i] != CB_COLLISION_NONE)
            {
                if(bRight[i - 1] == bLeft[i])
                {
                    bLeft[i] = CB_COLLISION_NONE;
                    bRight[i - 1] = CB_COLLISION_NONE;
                }
            }
            if(x < width - 1 && bRight[i] != CB_COLLISION_NONE)
            {
                if(bLeft[i + 1] == bRight[i])
                {
                    bRight[i] = CB_COLLISION_NONE;
                    bLeft[i + 1] = CB_COLLISION_NONE;
                }
            }
        }
        tile->putCustomCollision(&boundList, x * tileSize - getScreenLeft(), getScreenHeight() + getScreenTop() - y * tileSize);
    }
    for(uint32_t y = 0; y < height; y++)
    {
        CB_CollisionEnum cTop = CB_COLLISION_NONE;
        CB_CollisionEnum cBottom = CB_COLLISION_NONE;
        uint32_t pTop = 0;
        uint32_t pBottom = 0;
        for(uint32_t x = 0; x < width; x++)
        {
            uint32_t pos = x + y * width;
            if(bTop[pos] != cTop)
            {
                addBound(pTop, y, x, y, cTop);
                cTop = bTop[pos];
                pTop = x;
            }
            if(bBottom[pos] != cBottom)
            {
                addBound(x, y + 1, pBottom, y + 1, cBottom);
                cBottom = bBottom[pos];
                pBottom = x;
            }
        }
        addBound(pTop, y, width, y, cTop);
        addBound(width, y + 1, pBottom, y + 1, cBottom);
    }
    for(uint32_t x = 0; x < width; x++)
    {
        CB_CollisionEnum cLeft = CB_COLLISION_NONE;
        CB_CollisionEnum cRight = CB_COLLISION_NONE;
        uint32_t pLeft = 0;
        uint32_t pRight = 0;
        for(uint32_t y = 0; y < height; y++)
        {
            uint32_t pos = x + y * width;
            if(bLeft[pos] != cLeft)
            {
                addBound(x, pLeft, x, y, cLeft);
                cLeft = bLeft[pos];
                pLeft = y;
            }
            if(bRight[pos] != cRight)
            {
                addBound(x + 1, y, x + 1, pRight, cRight);
                cRight = bRight[pos];
                pRight = y;
            }
        }
        addBound(x, pLeft, x, height, cLeft);
        addBound(x + 1, height, x + 1, pRight, cRight);
    }

    isOptimized = true;
}

void CB_Room::addTile(uint32_t x, uint32_t y, CB_Tile * tile)
{
    uint32_t i = x + y * width;
    if(i >= width * height)
    {
        return;
    }
    SDL_mutexP(roomMutex);
    tileMap[i] = tile;
    SDL_mutexV(roomMutex);
}

void CB_Room::removeTile(uint32_t x, uint32_t y)
{
    uint32_t i = x + y * width;
    if(i >= width * height)
    {
        return;
    }
    SDL_mutexP(roomMutex);
    CB_Tile * tile = tileMap[i];
    tileMap[i] = CB_Tile::BLANK_TILE;
    SDL_mutexV(roomMutex);
    if(tile == 0)
    {
        return;
    }
    else if(tile == CB_Tile::BLANK_TILE)
    {
        uint32_t cX = x;
        while(true)
        {
            uint32_t cY = y;
            while(true)
            {
                uint32_t cI = cX + cY * width;
                SDL_mutexP(roomMutex);
                CB_Tile * tile = tileMap[cI];
                SDL_mutexV(roomMutex);
                if(tile == 0)
                {
                    break;
                }
                if(tile != CB_Tile::BLANK_TILE)
                {
                    if(cX + tile->getWidth(tileSize) > x && cY + tile->getHeight(tileSize) > y)
                    {
                        removeTile(cX, cY);
                        return;
                    }
                    break;
                }
                if(cY == 0)
                {
                    break;
                }
                cY--;
            }
            if(cX == 0)
            {
                break;
            }
            cX--;
        }
    }

    SDL_mutexP(roomMutex);
    uint32_t tileW = min(width - x, (uint32_t)tile->getWidth(tileSize));
    uint32_t tileH = min(height - y, (uint32_t)tile->getHeight(tileSize));
    SDL_mutexV(roomMutex);

    for(uint32_t tY = 0; tY < tileH; tY++)
    {
        for(uint32_t tX = 0; tX < tileW; tX++)
        {
            SDL_mutexP(roomMutex);
            uint32_t tI = x + tX + (y + tY) * width;
            if(tileMap[tI] == CB_Tile::BLANK_TILE)
            {
                tileMap[tI] = 0;
            }
            SDL_mutexV(roomMutex);
        }
    }
}

CB_Tile * CB_Room::getTileAt(uint32_t x, uint32_t y)
{
    uint32_t i = x + y * width;
    if(i >= width * height)
    {
        return 0;
    }
    CB_Tile * tile;
    SDL_mutexP(roomMutex);
    tile = tileMap[i];
    SDL_mutexV(roomMutex);
    return tile;
}

bool CB_Room::isFree(uint32_t x, uint32_t y, CB_Tile * tile)
{
    return isFree(x, y, tile->getWidth(tileSize), tile->getHeight(tileSize));
}

bool CB_Room::isFree(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    if(x + w > width)
    {
        w = width - x;
    }
    if(y + h > height)
    {
        h = height - y;
    }

    for(uint32_t iY = 0; iY < h; iY++)
    {
        for(uint32_t iX = 0; iX < w; iX++)
        {
            if(getTileAt(x + iX, y + iY) != 0)
            {
                return false;
            }
        }
    }
    return true;
}

void CB_Room::addBound(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, CB_CollisionEnum tileEnum)
{
    if(tileEnum != CB_COLLISION_NONE)
    {
        CB_CollisionBound * bound = new CB_CollisionBound();
        bound->setBound((double)x1 * tileSize - getScreenLeft(), getScreenHeight() + getScreenTop() - (double)y1 * tileSize, (double)x2 * tileSize - getScreenLeft(), getScreenHeight() + getScreenTop() - (double)y2 * tileSize);
        bound->type = tileEnum;
        boundList.push_back(bound);
    }
}

vector<CB_CollisionBound*> CB_Room::getBounds()
{
    return boundList;
}

void CB_Room::addProp(CB_RenderDataRel data)
{
    data.sharedUserdata = true;
    SDL_mutexP(roomMutex);
    propsList.push_back(data);
    SDL_mutexV(roomMutex);
}

uint32_t CB_Room::getScreenWidth()
{
    return (xRight - xLeft) * tileSize;
}

uint32_t CB_Room::getScreenHeight()
{
    return (yBottom- yTop) * tileSize;
}

uint32_t CB_Room::getScreenLeft()
{
    return xLeft * tileSize;
}

uint32_t CB_Room::getScreenTop()
{
    return yTop * tileSize;
}

uint32_t CB_Room::getWidth()
{
    return width;
}

uint32_t CB_Room::getHeight()
{
    return height;
}

uint8_t CB_Room::getTileSize()
{
    return tileSize;
}

void CB_Room::prepareRender()
{
    CB_Tile * tile;
    for(uint32_t i = 0; i < width * height; i++)
    {
        SDL_mutexP(roomMutex);
        tile = tileMap[i];
        SDL_mutexV(roomMutex);
        if(tile == 0)
        {
            continue;
        }
        uint32_t x = i % width;
        uint32_t y = i / width;
        double xStart = (double)x * tileSize - getScreenLeft();
        double yStart = getScreenHeight() + getScreenTop() - (double)y * tileSize;
        tile->prepareRender(xStart, yStart, tileSize);
    }
    vector<CB_RenderDataRel>::iterator it;
    for(it = propsList.begin(); it < propsList.end(); it++)
    {
        CB_Renderer::listRender(*it);
    }
}
