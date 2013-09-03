#ifndef CB_SCREEN_H
#define CB_SCREEN_H

#include "ClashBattle.h"
#include "CB_Camera.h"
#include "util/CB_Vector2D.h"

class CB_Screen
{
    public:
        CB_Screen();
        virtual ~CB_Screen();
        static void setSize(double w, double h){width = w; height = h;};
        static void setScreenSize(double w, double h){screenWidth = w; screenHeight = h;};
        static void setFov(double _fov){fov = _fov;};
        static void setOrthoZoom(double _orthoZoom){orthoZoom = _orthoZoom;};
        static void setTileSize(double _tileSize){tileSize = _tileSize;};
        static double getWidth(){return width;};
        static double getHeight(){return height;};
        static double getScreenWidth(){return screenWidth;};
        static double getScreenHeight(){return screenHeight;};
        static double getTileSize(){return tileSize;};
        static void setProjection(float interpolation);
        static void setProjection(float interpolation, float * matrix1, float * matrix2);
        static void setOrtho();
        static void setPerspective();
        static double getZ();
        static double getFOV();
        static double getInterpolation();
        static double getOrthoZoom();
        static CB_Camera * getCamera();
        static void setCamera(uint32_t camId);
        static CB_Vector2D getCameraToPlaneOnWorldZ(double x, double y, double z);
    protected:
    private:
        static double width;
        static double height;
        static double screenWidth;
        static double screenHeight;
        static double minFov;
        static double maxFov;
        static double fov;
        static double orthoZoom;
        static double tileSize;
        static double interpolation;
        static SDL_mutex * sScreenMutex;
        static CB_Camera * mainCamera;
};

#endif // CB_SCREEN_H
