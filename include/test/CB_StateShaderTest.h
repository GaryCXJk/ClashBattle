#ifndef CB_STATESHADERTEST_H
#define CB_STATESHADERTEST_H
#include "ClashBattle.h"
#include "CB_State.h"
#include "CB_FileLoader.h"


class CB_StateShaderTest : public CB_State
{
    public:
        CB_StateShaderTest();
        virtual ~CB_StateShaderTest();
        virtual void start();
        virtual void prerender();
        virtual void stop() {};
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StateShaderTest(*this);};
    protected:
    private:
    GLuint v;
    GLuint f;
    GLuint p;
};

#endif // CB_STATESHADERTEST_H
