#ifndef CB_COLLISIONAREA_H
#define CB_COLLISIONAREA_H
#include "ClashBattle.h"
#include "util/CB_Vector2D.h"
#include "CB_CollisionBound.h"

class CB_CollisionArea
{
    public:
        CB_CollisionArea();
        CB_CollisionArea(vector<CB_Vector2D*>);
        virtual ~CB_CollisionArea();
        void clear();
        void clearExcept(vector<CB_Vector2D*>);
        void setBox(double, double, double, double);
        void addVector(CB_Vector2D*);
        void addVector(const CB_Vector2D&);
        bool hasVector(CB_Vector2D*);
        uint32_t size();
        uint32_t getAngles();
        uint32_t getAngles(vector<CB_Vector2D*>);
        bool isConcave();
        bool isConcave(vector<CB_Vector2D*>);
        vector<CB_Vector2D*> optimize();
        vector<CB_Vector2D*> reverse();
        vector<CB_Vector2D*> reverse(vector<CB_Vector2D*>);
        bool isInRange(double, double, double, double);
        bool isOverlap(const CB_CollisionArea&);
        CB_Vector2D getProjection(const CB_Vector2D&, const CB_Vector2D&, const CB_Vector2D&);
        bool isBoundsCollide(const CB_Vector2D&, const CB_Vector2D&);
        bool isProjectionOverlap(const CB_Vector2D&, const CB_Vector2D&, const CB_Vector2D&, const CB_Vector2D&);
        CB_CollisionArea sweep(const CB_Vector2D& direction);
        vector<CB_CollisionArea*> getConvexPolygons();

        vector<CB_Vector2D*> vectors;
    protected:
    private:
};

#endif // CB_COLLISIONAREA_H
