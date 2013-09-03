#ifndef CB_STATEGLTEST_H
#define CB_STATEGLTEST_H

#include "CB_State.h"


class CB_StateGLTest : public CB_State
{
    public:
        CB_StateGLTest();
        virtual ~CB_StateGLTest();
        virtual void start();
        virtual void prerender(){};
        virtual void stop();
        virtual void run();
        virtual bool deactivate();
        virtual bool activate();
        virtual void draw();
        virtual void fadeOut();
        virtual void fadeIn();
        virtual CB_State * getInstance() {return new CB_StateGLTest(*this);};
        virtual void onKeyDown(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onKeyUp(SDL_Keycode sym, SDL_Keymod mod);
    protected:
    private:
        float theta;
        float speed;
        float movement;
        float movementMultiplier;
        bool isRun;
};

#endif // CB_STATEGLTEST_H
