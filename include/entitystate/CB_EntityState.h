#ifndef CB_ENTITYSTATE_H
#define CB_ENTITYSTATE_H

class CB_EntityStateManager;

#include "ClashBattle.h"
#include "CB_Entity.h"
#include "CB_EntityStateManager.h"

typedef void (*CB_StateFunction)(CB_Entity * entity, void * userdata);

class CB_EntityState
{
    public:
        friend class CB_EntityStateManager;
        CB_EntityState(CB_EntityStateManager * _parentManager);
        CB_EntityState(CB_EntityStateManager * _parentManager, int32_t _fallbackState);
        virtual ~CB_EntityState();
        void execute(CB_Entity * entity, void * userdata);
        void addFunction(CB_StateFunction * func);
    protected:
    private:
        CB_EntityStateManager * parentManager;
        int32_t fallbackState;
        list<CB_StateFunction*> functionList;
};

#endif // CB_ENTITYSTATE_H
