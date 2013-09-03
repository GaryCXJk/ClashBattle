#ifndef CB_ENTITYSTATEMANAGER_H
#define CB_ENTITYSTATEMANAGER_H

class CB_EntityState;

#include "ClashBattle.h"
#include "CB_EntityState.h"

class CB_EntityStateManager
{
    public:
        CB_EntityStateManager();
        virtual ~CB_EntityStateManager();
        bool hasState(int32_t stateNo);
        bool hasState(string stateName);
        void setState(int32_t stateNo);
        void setState(string stateName);
        int32_t getState(string stateName);
        int32_t createState(string stateName, int32_t stateNo);
        int32_t createState(string stateName, int32_t stateNo, string fallbackState);
    protected:
    private:
        map<int32_t,CB_EntityState*> stateMap;
        map<string,int32_t> strToStateMap;
        CB_Entity * parentEntity;

        int32_t currentState;

        SDL_mutex * stateManagerMutex;
};

#endif // CB_ENTITYSTATEMANAGER_H
