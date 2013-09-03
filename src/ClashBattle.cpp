#include "ClashBattle.h"

void CB_Perspective(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble fovy, GLdouble zNear, GLdouble zFar)
{
   GLdouble xmin, xmax, ymin, ymax;

   GLdouble width = right - left;
   GLdouble height = top - bottom;

   GLdouble xS = 2 * left / width;
   GLdouble yS = 2 * bottom / height;

   GLdouble aspect = width / height;

   GLdouble lMax = zNear * tan(fovy * M_PI / 360.0);

   ymax = lMax * (2 + yS);
   ymin = lMax * yS;

   xmin = lMax * aspect * xS;
   xmax = lMax * aspect * (2 + xS);

   glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}
