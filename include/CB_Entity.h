#ifndef CB_ENTITY_H
#define CB_ENTITY_H
#include "ClashBattle.h"

class CB_Entity
{
    public:
        CB_Entity();
        virtual ~CB_Entity();
        virtual void start() = 0;
        virtual void end() = 0;
        virtual void run() = 0;
        virtual void draw() = 0;
        virtual void onAI() = 0;
        virtual void onMove(float movement) = 0;
        virtual void onJump() = 0;
        virtual void onDuck() = 0;
        virtual void onDodge(uint8_t direction) = 0;
        virtual void onAttack(uint16_t attack) = 0;
        virtual void onHit(uint16_t strength, uint8_t type) = 0;
        virtual void setTileSize(double  newTileSize){tileSize = newTileSize;}
        virtual double getTileSize(){return tileSize;}
    protected:
    private:
        double tileSize;
        double x;
        double y;
        double vSpeed;
        double hSpeed;
};

#endif // CB_ENTITY_H
