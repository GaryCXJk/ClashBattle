#include "entitystate/CB_EntityStateManager.h"

CB_EntityStateManager::CB_EntityStateManager()
{
    stateManagerMutex = SDL_CreateMutex();
    createState("idle", 0);
    /*
    createState("move", 10);
    createState("duck", 20);
    createState("jump", 30);
    createState("block", 100);
    createState("dodge", 110);
    createState("select", 150);
    createState("intro", 160);
    createState("taunt", 170);
    createState("defeat", 180);
    createState("victory", 190);
    createState("attack", 200);
    createState("hit", 500);*/
    createState("init", -1);
    createState("preframe", -2);
    createState("postframe", -3);
}

CB_EntityStateManager::~CB_EntityStateManager()
{
    //dtor
}

bool CB_EntityStateManager::hasState(int32_t stateNo)
{
    bool retBool = false;
    SDL_mutexP(stateManagerMutex);
    retBool = stateMap.count(stateNo);
    SDL_mutexV(stateManagerMutex);
    return retBool;
}

bool CB_EntityStateManager::hasState(string stateName)
{
    bool retBool = false;
    SDL_mutexP(stateManagerMutex);
    retBool = strToStateMap.count(stateName);
    SDL_mutexV(stateManagerMutex);
    if(!retBool)
    {
        return false;
    }
    return hasState(strToStateMap[stateName]);
}

void CB_EntityStateManager::setState(int32_t stateNo)
{
    if(!hasState(stateNo))
    {
        return;
    }
    SDL_mutexP(stateManagerMutex);
    currentState = stateNo;
    SDL_mutexV(stateManagerMutex);
}

void CB_EntityStateManager::setState(string stateName)
{
    if(!hasState(stateName))
    {
        return;
    }
    int32_t stateNo;
    SDL_mutexP(stateManagerMutex);
    stateNo = strToStateMap[stateName];
    SDL_mutexV(stateManagerMutex);
    setState(stateNo);
}

int32_t CB_EntityStateManager::getState(string stateName)
{
    if(!hasState(stateName))
    {
        return 0;
    }
    int32_t stateNo;
    SDL_mutexP(stateManagerMutex);
    stateNo = strToStateMap[stateName];
    SDL_mutexV(stateManagerMutex);
    return stateNo;
}

int32_t CB_EntityStateManager::createState(string stateName, int32_t stateNo)
{
    if(hasState(stateName))
    {
        return getState(stateName);
    }
    SDL_mutexP(stateManagerMutex);
    strToStateMap[stateName] = stateNo;
    SDL_mutexV(stateManagerMutex);
    if(!hasState(stateNo))
    {
        SDL_mutexP(stateManagerMutex);
        stateMap[stateNo] = new CB_EntityState(this);
        SDL_mutexV(stateManagerMutex);
    }
    return stateNo;
}
