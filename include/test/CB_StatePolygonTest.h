#ifndef CB_STATEPOLYGONTEST_H
#define CB_STATEPOLYGONTEST_H

#include "CB_State.h"
#include "CB_CollisionArea.h"
#include "util/CB_Vector2D.h"

class CB_StatePolygonTest : public CB_State
{
    public:
        CB_StatePolygonTest();
        virtual ~CB_StatePolygonTest();
        virtual void start();
        virtual void prerender(){};
        virtual void stop();
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StatePolygonTest(*this);};
    protected:
    private:
        vector<CB_CollisionArea*> areas;
        CB_CollisionArea mArea;
        double theta;
};

#endif // CB_STATEPOLYGONTEST_H
