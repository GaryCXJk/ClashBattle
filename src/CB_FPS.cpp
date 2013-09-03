#include "CB_FPS.h"

map<uint32_t,CB_FPS*> CB_FPS::fpsMap;
uint8_t CB_FPS::initVar = init();
CB_FPS::CB_FPS()
{
targetFPS = 60;
lastTick = 0;
deltaRemainder = 0;
subTick = 0;
}

CB_FPS::~CB_FPS()
{
    //dtor
}

uint8_t CB_FPS::init()
{
    fpsMap[0] = new CB_FPS();
    fpsMap[1] = new CB_FPS();
    return 0;
}

uint32_t CB_FPS::create(uint32_t targetFPS)
{
    uint32_t current = fpsMap.size();
    fpsMap[current] = new CB_FPS();
    fpsMap[current]->targetFPS = targetFPS;
    return current;
}

CB_FPS* CB_FPS::get(uint32_t id)
{
    if(fpsMap.count(id) == 0)
    {
        return 0;
    }
    return fpsMap[id];
}

void CB_FPS::setCurrentTime()
{
    lastTick = SDL_GetTicks() - deltaRemainder;
}

uint32_t CB_FPS::getCurrentSetTime()
{
    return lastTick;
}

void CB_FPS::setTargetFPS(uint32_t newTargetFPS)
{
    targetFPS = newTargetFPS;
}

uint32_t CB_FPS::getTargetTicksPerFrame()
{
    return 1000 / targetFPS;
}

uint32_t CB_FPS::getTargetRemainder()
{
    return 1000 % targetFPS;
}

uint32_t CB_FPS::getTargetFrames()
{
    return getTargetTicksPerFrame() + ((getTargetRemainder() * subTick) / targetFPS);
}

float CB_FPS::getDelta()
{
    return (float)getDeltaTick() / (float)getTargetFrames();
}

uint32_t CB_FPS::getDeltaTick()
{
    return SDL_GetTicks() - lastTick;
}

void CB_FPS::endFrame()
{
    deltaRemainder = getDeltaTick() - getTargetFrames();
    if((getTargetRemainder() * subTick) / targetFPS > 0)
    {
        subTick = 0;
    }
    else
    {
        subTick++;
    }
}
