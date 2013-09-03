#ifndef CB_STATEJOYSTICKTEST_H
#define CB_STATEJOYSTICKTEST_H

#include "CB_State.h"
#include "util/CB_Vector2D.h"

class CB_StateJoystickTest : public CB_State
{
    public:
        CB_StateJoystickTest();
        virtual ~CB_StateJoystickTest();
        virtual void start();
        virtual void prerender() {};
        virtual void stop();
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StateJoystickTest(*this);};
        virtual void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
        virtual void onJoyHat(Uint8 which, Uint8 hat, Uint8 value);
    protected:
    private:
        int numSticks;
        int numAxes;
        int numHats;
        int curStick;
        vector<CB_Vector2D*> axes;
        vector<Uint8> hats;
        vector<SDL_Joystick*> sticks;
};

#endif // CB_STATEJOYSTICKTEST_H
