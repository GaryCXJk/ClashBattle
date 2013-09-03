#ifndef CB_STATETEXTURETEST_H
#define CB_STATETEXTURETEST_H

#include "CB_State.h"
#include "CB_Texture.h"

class CB_StateTextureTest : public CB_State
{
    public:
        CB_StateTextureTest();
        virtual ~CB_StateTextureTest();
        virtual void start();
        virtual void prerender();
        virtual void stop();
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StateTextureTest(*this);};
    protected:
    private:
        CB_Texture * texture;
        double theta;
        double fov;
        double minFov;
        double maxFov;
        double width;
        double height;
        double zNear;
        float orthoPMatrix[16];
        float displPMatrix[16];
};

#endif // CB_STATETEXTURETEST_H
