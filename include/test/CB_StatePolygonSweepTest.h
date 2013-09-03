#ifndef CB_STATEPOLYGONSWEEPTEST_H
#define CB_STATEPOLYGONSWEEPTEST_H

#include "CB_State.h"
#include "util/CB_Vector2D.h"
#include "CB_CollisionArea.h"

class CB_StatePolygonSweepTest : public CB_State
{
    public:
        CB_StatePolygonSweepTest();
        virtual ~CB_StatePolygonSweepTest();
        virtual void start();
        virtual void prerender(){};
        virtual void stop();
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StatePolygonSweepTest(*this);};
    protected:
    private:
        CB_CollisionArea box;
        CB_CollisionArea mover;
        CB_CollisionArea sweep;
        double theta;
        double pita;
        bool sweepOrCreate;
};

#endif // CB_STATEPOLYGONSWEEPTEST_H
