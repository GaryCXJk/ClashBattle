#include "test/CB_StateGLTest.h"
#include "CB_StateManager.h"
using namespace std;

CB_StateGLTest::CB_StateGLTest()
{
    theta = 0.0f;
    speed = 1.0f;
    movement = 0.0f;
    movementMultiplier = 1.0f;
}

CB_StateGLTest::~CB_StateGLTest()
{
    //dtor
}

void CB_StateGLTest::start()
{
    theta = 0.0f;
    speed = 0.0f;
    movement = 0.0f;
    movementMultiplier = 1.0f;
    isRun = false;
}

void CB_StateGLTest::stop()
{
}

void CB_StateGLTest::run()
{
    speed+= movement * movementMultiplier;
    theta+= speed;
}

bool CB_StateGLTest::deactivate()
{
    isRun = false;
    if(speed > 1.0f || speed < -1.0f)
    {
        speed*= 0.95f;
    }
    else if(speed > 0.0f)
    {
        speed-= 0.01f;
        if(speed < 0.0f)
        {
            speed = 0.0f;
            return false;
        }
    }
    else
    {
        speed+= 0.01f;
        if(speed > 0.0f)
        {
            speed = 0.0f;
            return false;
        }
    }
    theta+= speed;
    return true;
}

bool CB_StateGLTest::activate()
{
    speed+= 0.01f;
    theta+= speed;
    if(speed > 1.0f)
    {
        speed = 1.0f;
        isRun = true;
        return true;
    }
    return false;
}

void CB_StateGLTest::draw()
{
    float delta = CB_FPS::get(CB_FPS_CALCULATION)->getDelta();
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glPushMatrix();
    glRotatef(theta + delta * speed, 0.0f, 0.0f, 1.0f);

    glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f,   1.0f);
        glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f,  -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);

    glEnd();

    glPopMatrix();
}

void CB_StateGLTest::fadeOut()
{
    float delta = CB_FPS::get(CB_FPS_CALCULATION)->getDelta();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRotatef(theta + delta * speed, 0.0f, 0.0f, 1.0f);

    float fSpeed = speed;
    if(fSpeed < 0.0f)
    {
        fSpeed = -fSpeed;
    }
    if(fSpeed > 1.0f)
    {
        fSpeed = 1.0f;
    }
    float nSpeed = 1.0f - fSpeed;

    glBegin(GL_TRIANGLES);

        glColor4f(1.0f, nSpeed, nSpeed, fSpeed);   glVertex2f(0.0f,   1.0f);
        glColor4f(nSpeed, 1.0f, nSpeed, fSpeed);   glVertex2f(0.87f,  -0.5f);
        glColor4f(nSpeed, nSpeed, 1.0f, fSpeed);   glVertex2f(-0.87f, -0.5f);

    glEnd();

    glDisable(GL_BLEND);
    glPopMatrix();
}

void CB_StateGLTest::fadeIn()
{
    float delta = CB_FPS::get(CB_FPS_CALCULATION)->getDelta();
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glPushMatrix();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glRotatef(theta + delta * speed, 0.0f, 0.0f, 1.0f);

    float nSpeed = 1.0f - speed;

    glBegin(GL_TRIANGLES);

        glColor4f(1.0f, nSpeed, nSpeed, speed);   glVertex2f(0.0f,   1.0f);
        glColor4f(nSpeed, 1.0f, nSpeed, speed);   glVertex2f(0.87f,  -0.5f);
        glColor4f(nSpeed, nSpeed, 1.0f, speed);   glVertex2f(-0.87f, -0.5f);

    glEnd();

    glDisable(GL_BLEND);
    glPopMatrix();
}

void CB_StateGLTest::onKeyDown(SDL_Keycode sym, SDL_Keymod mod)
{
    switch(sym)
    {
        case SDLK_RIGHT:
        {
            movement = 0.01f;
            break;
        }
        case SDLK_LEFT:
        {
            movement = -0.01f;
            break;
        }
        case SDLK_LSHIFT:
        {
            movementMultiplier = 10.0f;
            break;
        }
        case SDLK_SPACE:
        {
            if(!isRun || CB_StateManager::isDeactivating())
            {
                break;
            }
            CB_StateManager::setState("opengltest");
            break;
        }
        default:
        {
            break;
        }
    }
}

void CB_StateGLTest::onKeyUp(SDL_Keycode sym, SDL_Keymod mod)
{
    switch(sym)
    {
        case SDLK_RIGHT:
        {
            if(movement > 0)
            {
                movement = 0.0f;
            }
            break;
        }
        case SDLK_LEFT:
        {
            if(movement < 0)
            {
                movement = 0.0f;
            }
            break;
        }
        case SDLK_LSHIFT:
        {
            movementMultiplier = 1.0f;
        }
        default:
        {
            break;
        }
    }
}
