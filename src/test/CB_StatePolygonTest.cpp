#include "test/CB_StatePolygonTest.h"
#include "CB_StateManager.h"

CB_StatePolygonTest::CB_StatePolygonTest()
{
    //ctor
}

CB_StatePolygonTest::~CB_StatePolygonTest()
{
    //dtor
}

void CB_StatePolygonTest::start()
{
    theta = 0;
    CB_CollisionArea area;
    area.addVector(new CB_Vector2D(20, 20));
    area.addVector(new CB_Vector2D(10, 40));
    area.addVector(new CB_Vector2D(10, 80));
    area.addVector(new CB_Vector2D(60, 80));
    area.addVector(new CB_Vector2D(20, 60));
    area.addVector(new CB_Vector2D(30, 60));
    area.addVector(new CB_Vector2D(30, 50));
    area.addVector(new CB_Vector2D(40, 40));
    area.addVector(new CB_Vector2D(20, 50));

    vector<CB_CollisionArea*> nAr = area.getConvexPolygons();
    areas.insert(areas.begin(), nAr.begin(), nAr.end());

    mArea.setBox(0, 0, 5, 5);
}

void CB_StatePolygonTest::stop()
{

}

void CB_StatePolygonTest::run()
{
    theta += 0.1;
    mArea.clear();
    mArea.setBox(sin(theta / 11) * 45.5 + 45.5, cos(theta / 91) * 45.5 + 45.5, 5, 5);
}

void CB_StatePolygonTest::draw()
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

    vector<CB_CollisionArea*>::iterator it;

    vector<CB_Vector2D*>::iterator itV;
    for(it = areas.begin(); it < areas.end(); it++)
    {
        CB_CollisionArea area = **it;

        vector<CB_Vector2D*> vecList = area.vectors;
        if(area.isOverlap(mArea))
        {
            glBegin(GL_POLYGON);
        }
        else
        {
            glBegin(GL_LINE_STRIP);
        }
        glColor3f(sin(it - areas.begin()) / 2 + 0.5, 0.0f, cos(it - areas.begin()) / 2 + 0.5);
        CB_Vector2D curVec;
        for(itV = vecList.begin(); itV < vecList.end(); itV++)
        {
            curVec = **itV;
            glVertex2d(curVec.x, curVec.y);
        }
        curVec = **vecList.begin();
        glVertex2d(curVec.x, curVec.y);
        glEnd();
    }
    vector<CB_Vector2D*> boxVecs = mArea.vectors;
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0f, 1.0f, 0.0f);
    CB_Vector2D curVec;
    for(itV = boxVecs.begin(); itV < boxVecs.end(); itV++)
    {
        curVec = **itV;
        glVertex2d(curVec.x, curVec.y);
    }
    curVec = **boxVecs.begin();
    glVertex2d(curVec.x, curVec.y);
    glEnd();

    glPopMatrix();
}
