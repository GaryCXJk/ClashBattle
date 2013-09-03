#ifndef CB_EVENT_H
#define CB_EVENT_H
#include "ClashBattle.h"

class CB_Event
{
    public:
        CB_Event();
        virtual ~CB_Event();
        virtual void onEvent(SDL_Event* event);
        virtual void onKeyDown(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onKeyUp(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle);
        virtual void onMouseWheel(bool up, bool down);
        virtual void onLeftButtonDown(int mouseX, int mouseY);
        virtual void onLeftButtonUp(int mouseX, int mouseY);
        virtual void onRightButtonDown(int mouseX, int mouseY);
        virtual void onRightButtonUp(int mouseX, int mouseY);
        virtual void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
        virtual void onJoyHat(Uint8 which, Uint8 hat, Uint8 value);
        virtual void onResize(int w, int h);
        virtual void onExit();
    protected:
    private:
};

#endif // CB_EVENT_H
