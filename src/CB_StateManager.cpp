#include "CB_StateManager.h"

CB_State* CB_StateManager::activeState = 0;
CB_State* CB_StateManager::deactivatingState = 0;
CB_State* CB_StateManager::activatingState = 0;
map<string, CB_State*> CB_StateManager::stateMap;

CB_StateManager::CB_StateManager()
{
    //ctor
}

CB_StateManager::~CB_StateManager()
{
    //dtor
}

void CB_StateManager::onEvent(SDL_Event* event)
{
    if(activeState)
    {
        activeState->onEvent(event);
    }
}

void CB_StateManager::run()
{
    if(deactivatingState)
    {
        bool keepAlive = deactivatingState->deactivate();
        if(!keepAlive)
        {
            deactivatingState->stop();
            deactivatingState = 0;
        }
    }
    if(activeState)
    {
        activeState->run();
    }
    if(activatingState)
    {
        bool isAlive = activatingState->activate();
        if(isAlive)
        {
            activeState = activatingState;
            activatingState = 0;
        }
    }
}

void CB_StateManager::draw()
{
    if(deactivatingState)
    {
        deactivatingState->fadeOut();
    }
    if(activeState)
    {
        if(!activeState->isPrerendered())
        {
            activeState->prerender();
            activeState->setPrerendered();
        }
        activeState->draw();
    }
    if(activatingState)
    {
        activatingState->fadeIn();
    }
}

void CB_StateManager::addState(string state, CB_State* stateObject)
{
    stateMap[state] = stateObject;
}

void CB_StateManager::setState(string state)
{
    if(activeState)
    {
        deactivatingState = activeState;
    }
    activeState = 0;
    if(stateMap.count(state) > 0)
    {
        activatingState = stateMap[state]->getInstance();
    }
    if(activatingState)
    {
        activatingState->start();
    }
}

bool CB_StateManager::isDeactivating()
{
    return (deactivatingState != 0);
}

bool CB_StateManager::isActivating()
{
    return (activatingState != 0);
}
