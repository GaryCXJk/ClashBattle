#include "util/CB_Vector2D.h"

CB_Vector2D::CB_Vector2D()
{
    x = 0;
    y = 0;
}

CB_Vector2D::CB_Vector2D(double xP, double yP)
{
    x = xP;
    y = yP;
}

CB_Vector2D::~CB_Vector2D()
{
    //dtor
}

CB_Vector2D CB_Vector2D::operator + (const CB_Vector2D& vector)
{
    CB_Vector2D vec;
    vec.x = x + vector.x;
    vec.y = y + vector.y;
    return vec;
}

CB_Vector2D CB_Vector2D::operator - (const CB_Vector2D& vector)
{
    CB_Vector2D vec;
    vec.x = x - vector.x;
    vec.y = y - vector.y;
    return vec;
}

CB_Vector2D CB_Vector2D::operator * (double scale)
{
    CB_Vector2D vec;
    vec.x = x * scale;
    vec.y = y * scale;
    return vec;
}

bool CB_Vector2D::operator == (const CB_Vector2D& vector)
{
    return (x == vector.x && y == vector.y);
}

bool CB_Vector2D::operator != (const CB_Vector2D& vector)
{
    return (x != vector.x || y != vector.y);
}

double CB_Vector2D::determinant(const CB_Vector2D& vector)
{
    return x * vector.y - y * vector.x;
}

double CB_Vector2D::dotProduct(const CB_Vector2D& vector)
{
    return x * vector.x + y * vector.y;
}

double CB_Vector2D::length()
{
    return sqrt(dotProduct(*this));
}

CB_Vector2D CB_Vector2D::normalize()
{
    CB_Vector2D vec;
    double len = sqrt(dotProduct(*this));
    if(len == 0)
    {
        return vec;
    }
    vec.x = x / len;
    vec.y = y / len;
    return vec;
}

CB_Vector2D CB_Vector2D::projection(const CB_Vector2D& vector)
{
    CB_Vector2D vec;
    double dp = dotProduct(vector);
    double sqrVLen = vector.x * vector.x + vector.y * vector.y;
    double dpsvl = 0;
    if(sqrVLen > 0)
    {
        dpsvl = dp / sqrVLen;
    }
    vec.x = dpsvl * vector.x;
    vec.y = dpsvl * vector.y;
    return vec;
}

double CB_Vector2D::getAngle()
{
    return atan2(y, x);
}

double CB_Vector2D::getAngle(const CB_Vector2D& vec)
{
    double angle = atan2(vec.y, vec.x) - atan2(y, x);
    if(angle > PI)
    {
        angle-= 2 * PI;
    }
    if(angle < -PI)
    {
        angle+= 2 * PI;
    }
    return angle;
}

CB_Vector2D CB_Vector2D::getRightNormal()
{
    CB_Vector2D rVec = CB_Vector2D(-y, x);
    return rVec;
}
