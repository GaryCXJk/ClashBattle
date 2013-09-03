#ifndef CB_VECTOR2D_H
#define CB_VECTOR2D_H
#include "ClashBattle.h"

class CB_Vector2D
{
    public:
        CB_Vector2D();
        CB_Vector2D(double xP, double yP);
        virtual ~CB_Vector2D();
        CB_Vector2D operator + (const CB_Vector2D&);
        CB_Vector2D operator - (const CB_Vector2D&);
        CB_Vector2D operator * (double);
        bool operator == (const CB_Vector2D&);
        bool operator != (const CB_Vector2D&);
        double determinant(const CB_Vector2D&);
        double dotProduct(const CB_Vector2D&);
        double length();
        CB_Vector2D normalize();
        CB_Vector2D projection(const CB_Vector2D&);
        double getAngle();
        double getAngle(const CB_Vector2D&);
        CB_Vector2D getRightNormal();

        double x;
        double y;
    protected:
    private:
};

#endif // CB_VECTOR2D_H
