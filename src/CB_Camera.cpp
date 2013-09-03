#include "CB_Camera.h"

map<uint32_t, CB_Camera*> CB_Camera::cameraMap;
SDL_mutex * CB_Camera::sCamMutex = SDL_CreateMutex();

CB_Camera::CB_Camera()
{
    xPos = 0;
    yPos = 0;
    zPos = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    scale = 1;
    hasPushed = false;
    camMutex = SDL_CreateMutex();
}

CB_Camera::~CB_Camera()
{
    //dtor
}

uint32_t CB_Camera::createCamera()
{
    SDL_mutexP(sCamMutex);
    uint32_t idx = cameraMap.size();
    while(cameraMap.count(idx) != 0)
    {
        idx++;
    }
    cameraMap[idx] = new CB_Camera();
    SDL_mutexV(sCamMutex);
    return idx;
}

CB_Camera * CB_Camera::getCamera(uint32_t camera)
{
    CB_Camera * retCam;
    SDL_mutexP(sCamMutex);
    if(cameraMap.count(camera) == 0)
    {
        retCam = 0;
    }
    else
    {
        retCam = cameraMap[camera];
    }
    SDL_mutexV(sCamMutex);
    return retCam;
}

void CB_Camera::setPosition(double x, double y, double z)
{
    SDL_mutexP(camMutex);
    xPos = x;
    yPos = y;
    zPos = z;
    SDL_mutexV(camMutex);
}

CB_Vector3D CB_Camera::getPosition()
{
    SDL_mutexP(camMutex);
    CB_Vector3D vec(xPos, yPos, zPos);
    SDL_mutexV(camMutex);
    return vec;
}

CB_Vector3D CB_Camera::getActualPosition()
{
    CB_Vector3D camFL = CB_Vector3D(0, 0, getFocalLength());
    CB_Quaternion quat = getRotation();
    CB_Vector3D camPos = getPosition();
    CB_Vector3D camVec = camPos + quat * camFL * camFL.length();
    return camVec;
}

CB_Quaternion CB_Camera::getRotation()
{
    CB_Quaternion quat;
    SDL_mutexP(camMutex);
    quat.fromEuler(xRot, yRot, zRot);
    SDL_mutexV(camMutex);
    return quat;
}

CB_Quaternion CB_Camera::getInverseRotation()
{
    CB_Quaternion quat;
    CB_Quaternion quat2;
    CB_Quaternion quat3;
    SDL_mutexP(camMutex);
    quat.fromEuler(-xRot, 0, 0);
    quat2.fromEuler(0, -yRot, 0);
    quat3.fromEuler(0, 0, -zRot);
    quat = quat * (quat2 * quat3);
    SDL_mutexV(camMutex);
    return quat;
}

double CB_Camera::getFocalLength()
{
    double fL;
    SDL_mutexP(camMutex);
    fL = focalLength;
    SDL_mutexV(camMutex);
    return fL;
}

void CB_Camera::setFocalLength(double fL)
{
    SDL_mutexP(camMutex);
    focalLength = fL;
    SDL_mutexV(camMutex);
}

void CB_Camera::setRotation(double x, double y, double z)
{
    SDL_mutexP(camMutex);
    xRot = x;
    yRot = y;
    zRot = z;
    SDL_mutexV(camMutex);
}

void CB_Camera::setScale(double s)
{
    SDL_mutexP(camMutex);
    scale = s;
    SDL_mutexV(camMutex);
}

void CB_Camera::doCamera()
{
    SDL_mutexP(camMutex);
    if(hasPushed)
    {
        resetCamera();
    }
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScaled(scale, scale, scale);
    glTranslated(0, 0, -focalLength);
    glRotated(-xRot, 1.0, 0.0, 0.0);
    glRotated(-yRot, 0.0, 1.0, 0.0);
    glRotated(-zRot, 0.0, 0.0, 1.0);
    glTranslated(-xPos, -yPos, -zPos);
    hasPushed = true;
    SDL_mutexV(camMutex);
}

void CB_Camera::resetCamera()
{
    SDL_mutexP(camMutex);
    glPopMatrix();
    hasPushed = false;
    SDL_mutexV(camMutex);
}
