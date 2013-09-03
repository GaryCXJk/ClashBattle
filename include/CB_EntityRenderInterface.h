#ifndef CB_ENTITYRENDERINTERFACE_H
#define CB_ENTITYRENDERINTERFACE_H
#include "ClashBattle.h"
#include "CB_Entity.h"

class CB_EntityRenderInterface
{
    public:
        CB_EntityRenderInterface();
        virtual ~CB_EntityRenderInterface();
        virtual void setRenderer(CB_Entity*) = 0;
    protected:
    private:
};

#endif // CB_ENTITYRENDERINTERFACE_H
