#ifndef CB_STATECAMERATEST_H
#define CB_STATECAMERATEST_H

#include "CB_State.h"
#include "CB_Camera.h"
#include "CB_Screen.h"


class CB_StateCameraTest : public CB_State
{
    public:
        CB_StateCameraTest();
        virtual ~CB_StateCameraTest();
        virtual void start();
        virtual void prerender(){};
        virtual void stop();
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StateCameraTest(*this);};
        virtual void onKeyDown(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onKeyUp(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle);
        virtual void onMouseWheel(bool up, bool down);
        void drawBox(double x, double y, double z, double w, double h, double d);
    protected:
    private:
        float speed;
        float interpolation;
        float theta;
        float tSpeed;
        CB_Camera * camera;
        bool manualMode;
        double x;
        double y;
        double z;
        double fLScale;
        double xRot;
        double yRot;
        double mXL;
        double mXR;
        double mYU;
        double mYD;
};

#endif // CB_STATECAMERATEST_H
