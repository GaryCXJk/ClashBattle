#include "util/CB_Quaternion.h"

CB_Quaternion::CB_Quaternion()
{
    x = 0;
    y = 0;
    z = 0;
    w = 1;
}

CB_Quaternion::CB_Quaternion(double _x, double _y, double _z, double _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

CB_Quaternion::~CB_Quaternion()
{
    //dtor
}

CB_Quaternion CB_Quaternion::operator * (const CB_Quaternion &rotQ)
{
    return CB_Quaternion(w * rotQ.x + x * rotQ.w + y * rotQ.z - z * rotQ.y,
                        w * rotQ.y + y * rotQ.w + z * rotQ.x - x * rotQ.z,
                        w * rotQ.z + z * rotQ.w + x * rotQ.y - y * rotQ.x,
                        w * rotQ.w - x * rotQ.x - y * rotQ.y - z * rotQ.z);
}

CB_Vector3D CB_Quaternion::operator * (const CB_Vector3D &vec)
{
    CB_Vector3D normVec(vec);
    normVec.normalize();

    CB_Quaternion vecQuat, resQuat;
    vecQuat.x = normVec.x;
    vecQuat.y = normVec.y;
    vecQuat.z = normVec.z;
    vecQuat.w = 0.0f;

    resQuat = vecQuat * getConjugate();
    resQuat = *this * resQuat;

    return CB_Vector3D(resQuat.x, resQuat.y, resQuat.z);
}

void CB_Quaternion::normalize()
{
    double mag = x * x + y * y + z * z + w * w;
    if(fabs(mag) > 0 && fabs(mag - 1.0) > 0)
    {
        mag = sqrt(mag);
        x/= mag;
        y/= mag;
        z/= mag;
        w/= mag;
    }
}

CB_Quaternion CB_Quaternion::getConjugate()
{
    return CB_Quaternion(-x, -y, -z, w);
}

void CB_Quaternion::fromEuler(double pitch, double yaw, double roll)
{
    double _p = pitch * (PI / 180) / 2;
    double _y = yaw * (PI / 180) / 2;
    double _r = roll * (PI / 180) / 2;

    double sP = sin(_p);
    double sY = sin(_y);
    double sR = sin(_r);
    double cP = cos(_p);
    double cY = cos(_y);
    double cR = cos(_r);

    x = cR * sP * cY + sR * cP * sY;
    y = cR * cP * sY - sR * sP * cY;
    z = sR * cP * cY - cR * sP * sY;
    w = cR * cP * cY + sR * sP * sY;

    normalize();
}

float * CB_Quaternion::getMatrix()
{
    float xx = x*x;
    float xy = x*y;
    float xz = x*z;
    float yy = y*y;
    float yz = y*z;
    float zz = z*z;
    float wx = w*x;
    float wy = w*y;
    float wz = w*z;

    float matrix[16] = {1.0 - 2.0 * (yy +zz), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
                        2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx), 0.0f,
                        2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy), 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f};
    float * mP;
    mP = matrix;
    return mP;
}
