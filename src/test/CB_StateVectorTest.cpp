#include "test/CB_StateVectorTest.h"
#include "CB_StateManager.h"
#include "util/CB_Vector2D.h"

CB_StateVectorTest::CB_StateVectorTest()
{
    //ctor
}

CB_StateVectorTest::~CB_StateVectorTest()
{
    //dtor
}

void CB_StateVectorTest::start()
{
    bound1.setBound(20, 20, 60, 60);
    bound2.setBound(50, 10, 10, 40);
    theta = 0;
    speed = 1;
}

void CB_StateVectorTest::stop()
{

}

void CB_StateVectorTest::run()
{
    theta+= speed;
    bound1.setBound(0, sin(0.8*theta*PI/180)*50 + 50, 100, cos(0.8*theta*PI/180)*50 + 50);
    bound2.setBound(sin(theta*PI/180)*50 + 50, cos(theta*PI/180)*50 + 50,100, 100);
}

void CB_StateVectorTest::draw()
{
    if(!CB_StateManager::isDeactivating())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-30, 130, -10, 110, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    double angleRed = ((CB_Vector2D)(bound2.getSecond()-bound2.getFirst())).getAngle(bound1.getSecond()-bound1.getFirst());
    float aColR = (angleRed > 0 ? 0.5f : 0.0f);
    float aColG = (angleRed < 0 ? 0.5f : 0.0f);
    glBegin(GL_LINES);
        glColor3f(1.0f, aColR, aColR);
        glVertex2d(bound1.getFirst().x,bound1.getFirst().y);
        glVertex2d(bound1.getSecond().x,bound1.getSecond().y);
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0.0f, 0.5f + aColG, 0.0f);
        glVertex2d(bound2.getFirst().x,bound2.getFirst().y);
        glVertex2d(bound2.getSecond().x,bound2.getSecond().y);
    glEnd();
    CB_Vector2D vec = bound1.getIntersection(bound2);
    if(bound1.intersects(vec))
    {
        glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2d(vec.x-1, vec.y-1);
            glVertex2d(vec.x+1, vec.y+1);
        glEnd();
        glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2d(vec.x-1, vec.y+1);
            glVertex2d(vec.x+1, vec.y-1);
        glEnd();
        CB_Vector2D vec2 = bound2.getSecond() - vec;
        vec2 = vec2.projection(bound1.getSecond() - vec);
        vec2 = vec + vec2;
        glBegin(GL_LINE_STRIP);
            glColor3f(0.3f, 0.8f, 1.0f);
            glVertex2d(bound2.getSecond().x, bound2.getSecond().y);
            glVertex2d(vec2.x, vec2.y);
            glVertex2d(vec.x, vec.y);
        glEnd();
    }
    glPopMatrix();
}

void CB_StateVectorTest::onKeyDown(SDL_Keycode sym, SDL_Keymod mod)
{
    if(sym == SDLK_SPACE)
    {
        speed = (speed == 0 ? 1 : 0);
    }
}
