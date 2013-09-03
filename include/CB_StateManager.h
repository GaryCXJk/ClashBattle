#ifndef CB_STATEMANAGER_H
#define CB_STATEMANAGER_H
#include "ClashBattle.h"
#include "CB_State.h"

class CB_StateManager
{
    public:
        CB_StateManager();
        virtual ~CB_StateManager();
        static void onEvent(SDL_Event* event);
        static void addState(string state, CB_State* stateObject);
        static void setState(string state);
        static void run();
        static void draw();
        static bool isDeactivating();
        static bool isActivating();
    protected:
    private:
        static CB_State* activeState;
        static CB_State* deactivatingState;
        static CB_State* activatingState;
        static map<string, CB_State*> stateMap;
};

#endif // CB_STATEMANAGER_H
