#ifndef CB_KEYBINDING_H
#define CB_KEYBINDING_H
#include "ClashBattle.h"
#include "CB_Event.h"

enum CB_KeyBindingType
{
    CB_KEYBINDING_KEYBOARD = 0,
    CB_KEYBINDING_JOYPAD = 1
};

struct CB_KeyBindingDef
{
    CB_KeyBindingType type;
    uint8_t source;
    uint8_t data;
    double value;
};

class CB_KeyBinding : public CB_Event
{
    public:
        CB_KeyBinding();
        virtual ~CB_KeyBinding();
    protected:
    private:
};

#endif // CB_KEYBINDING_H
