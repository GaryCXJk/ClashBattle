#ifndef CB_STATE_H
#define CB_STATE_H
#include "ClashBattle.h"
#include "CB_Event.h"
#include "CB_Screen.h"

class CB_State : public CB_Event
{
    public:
        CB_State();
        virtual ~CB_State();
        virtual void start() = 0;
        virtual void prerender() = 0;
        virtual void stop() = 0;
        virtual void run() = 0;
        virtual bool deactivate() = 0;
        virtual bool activate() = 0;
        virtual void draw() = 0;
        virtual void fadeOut() = 0;
        virtual void fadeIn() = 0;
        virtual CB_State * getInstance() = 0;
        bool isPrerendered(){return prerendered;};
        void setPrerendered(){prerendered = true;};
    protected:
    private:
        bool prerendered;
};

#endif // CB_STATE_H
