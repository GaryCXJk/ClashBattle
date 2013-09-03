#ifndef CB_QUATERNION_H
#define CB_QUATERNION_H

#include "ClashBattle.h"
#include "util/CB_Vector3D.h"

class CB_Quaternion
{
    public:
        CB_Quaternion();
        CB_Quaternion(double, double, double, double);
        virtual ~CB_Quaternion();
        CB_Quaternion operator * (const CB_Quaternion&);
        CB_Vector3D operator * (const CB_Vector3D&);
        void normalize();
        CB_Quaternion getConjugate();
        void fromEuler(double pitch, double yaw, double roll);
        float * getMatrix();
        double x;
        double y;
        double z;
        double w;
    protected:
    private:
};

#endif // CB_QUATERNION_H
