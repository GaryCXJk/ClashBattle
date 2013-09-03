#include "CB_Screen.h"

double CB_Screen::width;
double CB_Screen::height;
double CB_Screen::screenWidth;
double CB_Screen::screenHeight;
double CB_Screen::fov;
double CB_Screen::interpolation;
double CB_Screen::orthoZoom = 1.0;
double CB_Screen::tileSize = 32;
SDL_mutex * CB_Screen::sScreenMutex = SDL_CreateMutex();
CB_Camera * CB_Screen::mainCamera = 0;

CB_Screen::CB_Screen()
{
    //ctor
}

CB_Screen::~CB_Screen()
{
    //dtor
}

void CB_Screen::setProjection(float _interpolation)
{
    SDL_mutexP(sScreenMutex);
    interpolation = _interpolation;
    float ipolCube = interpolation * interpolation * interpolation;
    float orthoPMatrix[16];
    setOrtho();
    glGetFloatv(GL_PROJECTION_MATRIX, orthoPMatrix);
    setPerspective();
    float displPMatrix[16];
    glGetFloatv(GL_PROJECTION_MATRIX, displPMatrix);
    for(uint32_t idx = 0; idx < 16; idx++)
    {
        displPMatrix[idx] = displPMatrix[idx] * ipolCube + orthoPMatrix[idx] * (1.0 - ipolCube);
    }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLoadMatrixf(displPMatrix);
    SDL_mutexV(sScreenMutex);
}

void CB_Screen::setProjection(float _interpolation, float * matrix1, float * matrix2)
{
    SDL_mutexP(sScreenMutex);
    float ipolCube = _interpolation * _interpolation * _interpolation;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float displPMatrix[16];
    for(uint32_t idx = 0; idx < 16; idx++)
    {
        displPMatrix[idx] = matrix2[idx] * ipolCube + matrix1[idx] * (1.0 - ipolCube);
    }
    glLoadMatrixf(displPMatrix);
    SDL_mutexV(sScreenMutex);
}

void CB_Screen::setOrtho()
{
    SDL_mutexP(sScreenMutex);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width * orthoZoom / 2.0, width * orthoZoom / 2.0, -height * orthoZoom / 2.0, height * orthoZoom / 2.0, -10000, 50000);
    SDL_mutexV(sScreenMutex);
}

void CB_Screen::setPerspective()
{
    SDL_mutexP(sScreenMutex);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    CB_Perspective(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0, fov, 1, 50000);
    SDL_mutexV(sScreenMutex);
}

double CB_Screen::getZ()
{
    SDL_mutexP(sScreenMutex);
    double rZ = (0.5 * height / (tan(0.5 * fov * PI / 180)));
    SDL_mutexV(sScreenMutex);
    return rZ;
}

double CB_Screen::getFOV()
{
    SDL_mutexP(sScreenMutex);
    double rF = fov;
    SDL_mutexV(sScreenMutex);
    return rF;
}

double CB_Screen::getInterpolation()
{
    SDL_mutexP(sScreenMutex);
    double rI = interpolation;
    SDL_mutexV(sScreenMutex);
    return rI;
}

double CB_Screen::getOrthoZoom()
{
    SDL_mutexP(sScreenMutex);
    double rZ = orthoZoom;
    SDL_mutexV(sScreenMutex);
    return rZ;
}

CB_Camera * CB_Screen::getCamera()
{
    SDL_mutexP(sScreenMutex);
    CB_Camera * cam = mainCamera;
    SDL_mutexV(sScreenMutex);
    return cam;
}

void CB_Screen::setCamera(uint32_t camId)
{
    SDL_mutexP(sScreenMutex);
    mainCamera = CB_Camera::getCamera(camId);
    SDL_mutexV(sScreenMutex);
}

CB_Vector2D CB_Screen::getCameraToPlaneOnWorldZ(double x, double y, double z)
{
    CB_Camera * _camera = getCamera();
    CB_Vector3D pointVec(x, y, _camera->getFocalLength() - getZ());
    pointVec = _camera->getRotation() * pointVec * pointVec.length();
    pointVec = pointVec + _camera->getPosition();
    CB_Vector3D differenceVec = _camera->getActualPosition() - pointVec;
    if(differenceVec.z == 0)
    {
        differenceVec.z = 0.00001;
    }
    CB_Vector3D aVec = pointVec - (differenceVec * ((pointVec.z - z) / differenceVec.z));

    return CB_Vector2D(aVec.x, aVec.y);
}
