#ifndef CB_VECTOR3D_H
#define CB_VECTOR3D_H

#include "ClashBattle.h"

class CB_Vector3D
{
    public:
        CB_Vector3D();
        CB_Vector3D(double, double, double);
        virtual ~CB_Vector3D();
        CB_Vector3D operator * (double);
        CB_Vector3D operator - (const CB_Vector3D&);
        CB_Vector3D operator + (const CB_Vector3D&);
        CB_Vector3D crossProduct(const CB_Vector3D& vec);
        void normalize();
        CB_Vector3D getNormalized();
        double length();
        double x;
        double y;
        double z;
    protected:
    private:
};

#endif // CB_VECTOR3D_H
