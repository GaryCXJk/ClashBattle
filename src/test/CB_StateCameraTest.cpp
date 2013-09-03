#include "test/CB_StateCameraTest.h"
#include "CB_StateManager.h"

CB_StateCameraTest::CB_StateCameraTest()
{
    //ctor
}

CB_StateCameraTest::~CB_StateCameraTest()
{
    //dtor
}

void CB_StateCameraTest::start()
{
    speed = -1.0 / 30;
    interpolation = 0.0;
    theta = 0;
    tSpeed = 0;
    uint32_t camId = CB_Camera::createCamera();
    camera = CB_Camera::getCamera(camId);
    CB_Screen::setSize(320, 240);
    CB_Screen::setFov(45);
    manualMode = false;
    x = 160;
    y = 120;
    z = 0;
    fLScale = 1.0;
    mXL = 0;
    mXR = 0;
    mYU = 0;
    mYD = 0;
}

void CB_StateCameraTest::stop()
{

}

void CB_StateCameraTest::run()
{
    interpolation+= speed;
    interpolation = min(1.0f, max(0.0f, interpolation));
    theta+= 0.01 * tSpeed;
    x+= mXR - mXL;
    y+= mYU - mYD;
}

void CB_StateCameraTest::draw()
{
    float iPolRot = (-cos(interpolation * PI) / 2 + 0.5);

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    CB_Screen::setProjection(interpolation);
    //camera->setPosition(160, 120, CB_Screen::getZ());
    //camera->setPosition(160, 120, 0);
    if(!manualMode)
    {
        camera->setFocalLength(CB_Screen::getZ() + sin(theta * 1.5) * 150);
        camera->setPosition(160 + 64 * sin(theta), 120 + 64 * cos(theta), 0);
        camera->setRotation(sin(theta * 2) * 10 * iPolRot, cos(theta * 2) * 10 * iPolRot, 0);
    }
    else
    {
        camera->setFocalLength(CB_Screen::getZ() * fLScale);
        camera->setPosition(x, y, z);
        camera->setRotation(xRot * iPolRot, yRot * iPolRot, 0);
    }
    camera->doCamera();

    glPushMatrix();
    glTranslated(160 + 64 * sin(theta), 120 + 64 * cos(theta), 0);
    drawBox(-4, -4, -4, 8, 8, 8);
    glPopMatrix();

    drawBox(80, 0, -1280, 320, 240, 80);
    drawBox(128, 64, -24, 32, 16, 48);
    drawBox(160, 0, -520, 320, 64, 400);
    drawBox(448, 64, -520, 32, 32, 32);
    drawBox(0, 0, -120, 320, 32, 80);
    drawBox(0, 0, -400, 128, 144, 32);
    drawBox(0, 0, -40, 128, 128, 32);
    drawBox(0, 0, -8, 32, 16, 16);
    drawBox(32, 16, -8, 32, 16, 16);
    glPushMatrix();
    glTranslated(64, 40, 0);
    glRotated(theta * 45, 1.0, 0.0, 0.0);
    drawBox(0, -8, -8, 64, 16, 16);
    glPopMatrix();

    camera->resetCamera();
    glPopMatrix();
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    CB_Screen::setOrtho();
    glMatrixMode(GL_MODELVIEW);
    glBegin(GL_LINES);
    glColor3d(1, 1, 1);
    glVertex2d(0, 0);
    glVertex2d(sin(interpolation * PI) * 100, cos(interpolation * PI) * 100);
    glEnd();
    glPopMatrix();
}

void CB_StateCameraTest::onKeyDown(SDL_Keycode sym, SDL_Keymod mod)
{
    switch(sym)
    {
        case SDLK_SPACE:
        {
            speed = -speed;
            break;
        }
        case SDLK_RETURN:
        {
            tSpeed = 1 - tSpeed;
            break;
        }
        case SDLK_TAB:
        {
            manualMode = !manualMode;
            break;
        }
        case SDLK_ESCAPE:
        {
            SDL_Event event;
            event.type = SDL_QUIT;
            SDL_PushEvent(&event);
            break;
        }
        default:
        {
            break;
        }
    }
    if(!manualMode)
    {
        return;
    }
    switch(sym)
    {
        case SDLK_a:
        case SDLK_LEFT:
        {
            mXL = 1;
            break;
        }
        case SDLK_d:
        case SDLK_RIGHT:
        {
            mXR = 1;
            break;
        }
        case SDLK_w:
        case SDLK_UP:
        {
            mYU = 1;
            break;
        }
        case SDLK_s:
        case SDLK_DOWN:
        {
            mYD = 1;
            break;
        }
        default:
        {
            break;
        }
    }
}

void CB_StateCameraTest::onKeyUp(SDL_Keycode sym, SDL_Keymod mod)
{
    switch(sym)
    {
        case SDLK_a:
        case SDLK_LEFT:
        {
            mXL = 0;
            break;
        }
        case SDLK_d:
        case SDLK_RIGHT:
        {
            mXR = 0;
            break;
        }
        case SDLK_w:
        case SDLK_UP:
        {
            mYU = 0;
            break;
        }
        case SDLK_s:
        case SDLK_DOWN:
        {
            mYD = 0;
            break;
        }
        default:
        {
            break;
        }
    }
}

void CB_StateCameraTest::onMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle)
{
    yRot = (mouseX - (CB_Screen::getScreenWidth() / 2)) / (CB_Screen::getScreenWidth() / 2) * 45;
    xRot = (mouseY - (CB_Screen::getScreenHeight() / 2)) / (CB_Screen::getScreenHeight() / 2) * 45;
}

void CB_StateCameraTest::onMouseWheel(bool up, bool down)
{
    if(up)
    {
        fLScale-= 0.05;
    }
    else
    {
        fLScale+= 0.05;
    }
    fLScale = max(0.1, fLScale);
}

void CB_StateCameraTest::drawBox(double x, double y, double z, double w, double h, double d)
{
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(x + w, y, z);
        glColor3d(0.0, 1.0, 0.0);
        glVertex3d(x, y, z);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x, y + h, z);
        glColor3d(0.0, 0.0, 1.0);
        glVertex3d(x + w, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.0, 1.0);
        glVertex3d(x + w, y, z + d);
        glColor3d(1.0, 1.0, 0.0);
        glVertex3d(x + w, y, z);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x + w, y + h, z);
        glColor3d(0.0, 1.0, 1.0);
        glVertex3d(x + w, y + h, z + d);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.0, 1.0);
        glVertex3d(x, y, z);
        glColor3d(1.0, 1.0, 0.0);
        glVertex3d(x, y, z + d);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x, y + h, z + d);
        glColor3d(0.0, 1.0, 1.0);
        glVertex3d(x, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(0.3, 0.5, 1.0);
        glVertex3d(x, y + h, z + d);
        glColor3d(1.0, 0.3, 0.5);
        glVertex3d(x + w, y + h, z + d);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x + w, y + h, z);
        glColor3d(0.5, 1.0, 0.3);
        glVertex3d(x, y + h, z);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(0.3, 0.5, 1.0);
        glVertex3d(x + w, y, z);
        glColor3d(1.0, 0.3, 0.5);
        glVertex3d(x, y, z);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x, y, z + d);
        glColor3d(0.5, 1.0, 0.3);
        glVertex3d(x + w, y, z + d);
    glEnd();
    glBegin(GL_QUADS);
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(x, y, z + d);
        glColor3d(0.0, 1.0, 0.0);
        glVertex3d(x + w, y, z + d);
        glColor3d(1.0, 1.0, 1.0);
        glVertex3d(x + w, y + h, z + d);
        glColor3d(0.0, 0.0, 1.0);
        glVertex3d(x, y + h, z + d);
    glEnd();
}
