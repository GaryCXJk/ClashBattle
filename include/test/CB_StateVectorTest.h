#ifndef CB_STATEVECTORTEST_H
#define CB_STATEVECTORTEST_H
#include "CB_State.h"
#include "CB_CollisionBound.h"
#include "util/CB_Vector2D.h"

class CB_StateVectorTest : public CB_State
{
    public:
        CB_StateVectorTest();
        virtual ~CB_StateVectorTest();
        virtual void start();
        virtual void prerender(){};
        virtual void stop();
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StateVectorTest(*this);};
        void onKeyDown(SDL_Keycode sym, SDL_Keymod mod);
    protected:
    private:
        CB_CollisionBound bound1;
        CB_CollisionBound bound2;
        double theta;
        double speed;
};

#endif // CB_STATEVECTORTEST_H
