#ifndef CB_COLLISIONLINE_H
#define CB_COLLISIONLINE_H
#include "ClashBattle.h"
#include "util/CB_Vector2D.h"

class CB_CollisionBound
{
    public:
        CB_CollisionBound();
        virtual ~CB_CollisionBound();

        void setBound(double x1, double y1, double x2, double y2);
        CB_Vector2D getIntersection(CB_CollisionBound * bound);
        CB_Vector2D getIntersection(CB_CollisionBound & bound);
        bool intersects(CB_Vector2D);
        CB_Vector2D getFirst();
        CB_Vector2D getSecond();

        CB_CollisionEnum type;
        uint32_t damage;
        bool active;
    protected:
    private:
        CB_Vector2D first;
        CB_Vector2D second;

        static CB_Vector2D NO_INTERSECT;
};

#endif // CB_COLLISIONLINE_H
