#include "CB_CollisionBound.h"

CB_Vector2D CB_CollisionBound::NO_INTERSECT (DBL_MAX, DBL_MAX);

CB_CollisionBound::CB_CollisionBound()
{
    type = CB_COLLISION_NONE;
    active = true;
}

CB_CollisionBound::~CB_CollisionBound()
{
}

void CB_CollisionBound::setBound(double x1, double y1, double x2, double y2)
{
    first.x = x1;
    first.y = y1;
    second.x = x2;
    second.y = y2;
}

CB_Vector2D CB_CollisionBound::getIntersection(CB_CollisionBound * bound)
{
    double det = (second - first).determinant(bound->first - bound->second);
    double t = (bound->first - first).determinant(bound->first - bound->second) / det;
    double u = (second - first).determinant(bound->first - first) / det;
    if((t < 0) || (u < 0) || (t > 1) || (u > 1))
    {
        return NO_INTERSECT;
    }
    return first * (1 - t) + second * t;
}

CB_Vector2D CB_CollisionBound::getIntersection(CB_CollisionBound & bound)
{
    double det = (second - first).determinant(bound.first - bound.second);
    double t = (bound.first - first).determinant(bound.first - bound.second) / det;
    double u = (second - first).determinant(bound.first - first) / det;
    if((t < 0) || (u < 0) || (t > 1) || (u > 1))
    {
        return NO_INTERSECT;
    }
    return first * (1 - t) + second * t;
}

bool CB_CollisionBound::intersects(CB_Vector2D vector)
{
    return vector != NO_INTERSECT;
}

CB_Vector2D CB_CollisionBound::getFirst()
{
    CB_Vector2D vec (first);
    return vec;
}

CB_Vector2D CB_CollisionBound::getSecond()
{
    CB_Vector2D vec (second);
    return vec;
}
