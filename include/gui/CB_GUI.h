#ifndef CB_GUI_H
#define CB_GUI_H

#include "ClashBattle.h"
#include "CB_Event.h"

class CB_GUI : public CB_Event
{
    public:
        CB_GUI();
        virtual ~CB_GUI();
    protected:
    private:
        vector<CB_GUI*> element;
};

#endif // CB_GUI_H
