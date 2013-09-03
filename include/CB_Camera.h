#ifndef CB_CAMERA_H
#define CB_CAMERA_H
#include "ClashBattle.h"
#include "util/CB_Quaternion.h"
#include "util/CB_Vector3D.h"

class CB_Camera
{
    public:
        static uint32_t createCamera();
        static CB_Camera * getCamera(uint32_t camera);
        void setPosition(double x, double y, double z);
        CB_Vector3D getPosition();
        CB_Vector3D getActualPosition();
        CB_Quaternion getRotation();
        CB_Quaternion getInverseRotation();
        double getFocalLength();
        void setFocalLength(double fL);
        void setRotation(double x, double y, double z);
        void setScale(double s);
        void doCamera();
        void resetCamera();
    protected:
    private:
        CB_Camera();
        virtual ~CB_Camera();
        double xPos;
        double yPos;
        double zPos;
        double focalLength;
        double xRot;
        double yRot;
        double zRot;
        double scale;
        bool hasPushed;
        SDL_mutex * camMutex;

        static map<uint32_t, CB_Camera*> cameraMap;
        static SDL_mutex * sCamMutex;
};

#endif // CB_CAMERA_H
