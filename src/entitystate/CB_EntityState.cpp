#include "entitystate/CB_EntityState.h"

CB_EntityState::CB_EntityState(CB_EntityStateManager * _parentManager)
{
    parentManager = _parentManager;
    fallbackState = 0;
}

CB_EntityState::CB_EntityState(CB_EntityStateManager * _parentManager, int32_t _fallbackState)
{
    parentManager = _parentManager;
    fallbackState = _fallbackState;
}

CB_EntityState::~CB_EntityState()
{
    //dtor
}

void CB_EntityState::execute(CB_Entity * entity, void * userdata)
{
    list<CB_StateFunction*>::iterator it;

    for(it = functionList.begin(); it != functionList.end(); it++)
    {
        CB_StateFunction * func = *it;
        (*func) (entity, userdata);
    }
}

void CB_EntityState::addFunction(CB_StateFunction * state)
{
    functionList.push_back(state);
}
