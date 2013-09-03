#include "test/CB_StatePolygonSweepTest.h"
#include "CB_StateManager.h"

CB_StatePolygonSweepTest::CB_StatePolygonSweepTest()
{
    //ctor
}

CB_StatePolygonSweepTest::~CB_StatePolygonSweepTest()
{
    //dtor
}

void CB_StatePolygonSweepTest::start()
{
    theta = 0;
    box.setBox(30, 30, 40, 40);
    box.addVector(new CB_Vector2D(20, 50));
    mover.setBox(30, 70, 40, 40);
    mover.addVector(new CB_Vector2D(20, 90));
    sweep = box.sweep(CB_Vector2D(20, 0));
}

void CB_StatePolygonSweepTest::stop()
{

}

void CB_StatePolygonSweepTest::run()
{
    theta+= 0.01;
    pita+= 0.01;
    mover.clear();
    mover.setBox(sin(theta)*20+30, cos(theta)*20+30, 40, 40);
    mover.addVector(new CB_Vector2D(sin(theta)*20+20, cos(theta)*20+50));
    sweep.clearExcept(box.vectors);
    sweep = box.sweep(CB_Vector2D(sin(theta)*20, cos(theta)*20));
}

void CB_StatePolygonSweepTest::draw()
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
    vector<CB_Vector2D*>::iterator itV;
    vector<CB_Vector2D*> vecs;
    CB_Vector2D curVec;

    vecs = box.vectors;
    glBegin(GL_POLYGON);
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    for(itV = vecs.begin(); itV < vecs.end(); itV++)
    {
        curVec = **itV;
        glVertex2d(curVec.x, curVec.y);
    }
    curVec = **vecs.begin();
    glVertex2d(curVec.x, curVec.y);
    glEnd();

    vecs = mover.vectors;
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);
    for(itV = vecs.begin(); itV < vecs.end(); itV++)
    {
        curVec = **itV;
        glVertex2d(curVec.x, curVec.y);
    }
    curVec = **vecs.begin();
    glVertex2d(curVec.x, curVec.y);
    glEnd();

    vecs = sweep.vectors;
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f);
    for(itV = vecs.begin(); itV < vecs.end(); itV++)
    {
        curVec = **itV;
        glVertex2d(curVec.x, curVec.y);
    }
    curVec = **vecs.begin();
    glVertex2d(curVec.x, curVec.y);
    glEnd();

    glPopMatrix();
}
