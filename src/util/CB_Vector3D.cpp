#include "util/CB_Vector3D.h"

CB_Vector3D::CB_Vector3D()
{
    x = 0;
    y = 0;
    z = 0;
}

CB_Vector3D::CB_Vector3D(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

CB_Vector3D::~CB_Vector3D()
{
    //dtor
}

CB_Vector3D CB_Vector3D::operator * (double length)
{
    return CB_Vector3D(x * length, y * length, z * length);
}

CB_Vector3D CB_Vector3D::operator - (const CB_Vector3D& vec)
{
    return CB_Vector3D(x - vec.x, y - vec.y, z - vec.z);
}

CB_Vector3D CB_Vector3D::operator + (const CB_Vector3D& vec)
{
    return CB_Vector3D(x + vec.x, y + vec.y, z + vec.z);
}

CB_Vector3D CB_Vector3D::crossProduct(const CB_Vector3D& vec)
{
    return CB_Vector3D(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

void CB_Vector3D::normalize()
{
    double mag = x*x + y*y + z*z;
    if(fabs(mag) > 0 && fabs(mag + 1) > 0)
    {
        mag = sqrt(mag);
        x/= mag;
        y/= mag;
        z/= mag;
    }
}

CB_Vector3D CB_Vector3D::getNormalized()
{
    CB_Vector3D rVec = *this;
    double mag = x*x + y*y + z*z;
    if(fabs(mag) > 0 && fabs(mag + 1) > 0)
    {
        mag = sqrt(mag);
        rVec.x/= mag;
        rVec.y/= mag;
        rVec.z/= mag;
    }
    return rVec;
}

double CB_Vector3D::length()
{
    return sqrt(x*x + y*y + z*z);
}
