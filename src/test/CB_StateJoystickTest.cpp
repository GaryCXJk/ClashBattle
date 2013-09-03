#include "test/CB_StateJoystickTest.h"
#include "CB_StateManager.h"

CB_StateJoystickTest::CB_StateJoystickTest()
{
    //ctor
}

CB_StateJoystickTest::~CB_StateJoystickTest()
{
    //dtor
}

void CB_StateJoystickTest::start()
{
    numSticks = SDL_NumJoysticks();
    numAxes = 0;
    numHats = 0;
    SDL_Joystick * aStick;
    for(int i = 0; i < numSticks; i++)
    {
        aStick = SDL_JoystickOpen(i);
        sticks.push_back(aStick);
        numAxes+= SDL_JoystickNumAxes(aStick);
        numHats+= SDL_JoystickNumHats(aStick);
    }
    for(int i = 0; i < numAxes; i++)
    {
        axes.push_back(new CB_Vector2D());
    }
    for(int i = 0; i < numHats; i++)
    {
        hats.push_back(0);
    }
    curStick = 0;
}

void CB_StateJoystickTest::stop()
{
    for(int i = 0; i < numSticks; i++)
    {
        SDL_JoystickClose(sticks[i]);
    }
}

void CB_StateJoystickTest::run()
{
}

void CB_StateJoystickTest::draw()
{
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-160, 160, -120, 120, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glColor3f(1.0, 1.0, 1.0);
    for(int i = 0; i < numAxes; i++)
    {
        glBegin(GL_LINES);
        glVertex2d(0, 0);
        glVertex2d(100 * axes[i]->x, -100 * axes[i]->y);
        glEnd();
    }
    for(int i = 0; i < numHats; i++)
    {
        glBegin(GL_LINES);
        glVertex2d(100, 0);
        glVertex2d(100, hats[i] + i);
        glEnd();
    }
    glPopMatrix();
}

void CB_StateJoystickTest::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
    Uint8 dAxis = axis % 2;
    Uint8 nAxis = (axis - dAxis) / 2;
    double val = (double)value / 32767.0;
    val = min(1.0, max(-1.0, val));
    if(dAxis == 0)
    {
        axes[nAxis]->x = val;
    }
    else
    {
        axes[nAxis]->y = val;
    }
}

void CB_StateJoystickTest::onJoyHat(Uint8 which, Uint8 hat, Uint8 value)
{
    hats[hat] = value;
}
