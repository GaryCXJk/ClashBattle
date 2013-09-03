#include "CB_Event.h"

CB_Event::CB_Event()
{
    //ctor
}

CB_Event::~CB_Event()
{
    //dtor
}

void CB_Event::onEvent(SDL_Event* event)
{
    switch(event->type)
    {
        case SDL_KEYDOWN:
        {
            onKeyDown(event->key.keysym.sym, (SDL_Keymod)event->key.keysym.mod);
            break;
        }
        case SDL_KEYUP:
        {
            onKeyUp(event->key.keysym.sym, (SDL_Keymod)event->key.keysym.mod);
            break;
        }
        case SDL_MOUSEMOTION:
        {
            onMouseMove(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel, (event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            switch(event->button.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    onLeftButtonDown(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    onRightButtonDown(event->button.x, event->button.y);
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        }
        case SDL_MOUSEWHEEL:
        {
            //onMouseWheel(event->button.button == SDL_BUTTON_WHEELUP, event->button.button == SDL_BUTTON_WHEELDOWN);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            switch(event->button.button)
            {
                case SDL_BUTTON_LEFT:
                {
                    onLeftButtonUp(event->button.x, event->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT:
                {
                    onRightButtonUp(event->button.x, event->button.y);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        case SDL_JOYAXISMOTION:
        {
            onJoyAxis(event->jaxis.which, event->jaxis.axis, event->jaxis.value);
            break;
        }
        case SDL_JOYHATMOTION:
        {
            onJoyHat(event->jhat.which, event->jhat.hat, event->jhat.value);
            break;
        }
        case SDL_WINDOWEVENT:
        {
            switch(event->window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                {
                    onResize(event->window.data1, event->window.data2);
                    break;
                }
            }
            break;
        }
        case SDL_QUIT:
        {
            onExit();
            break;
        }
    }
}

void CB_Event::onKeyDown(SDL_Keycode sym, SDL_Keymod mod)
{

}

void CB_Event::onKeyUp(SDL_Keycode sym, SDL_Keymod mod)
{

}

void CB_Event::onMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle)
{

}

void CB_Event::onMouseWheel(bool up, bool down)
{

}

void CB_Event::onLeftButtonDown(int mouseX, int mouseY)
{

}

void CB_Event::onLeftButtonUp(int mouseX, int mouseY)
{

}

void CB_Event::onRightButtonDown(int mouseX, int mouseY)
{

}

void CB_Event::onRightButtonUp(int mouseX, int mouseY)
{

}

void CB_Event::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{

}

void CB_Event::onJoyHat(Uint8 which, Uint8 hat, Uint8 value)
{

}

void CB_Event::onResize(int w, int h)
{

}

void CB_Event::onExit()
{

}
