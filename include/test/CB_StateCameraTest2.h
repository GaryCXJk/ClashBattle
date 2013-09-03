#ifndef CB_STATECAMERATEST2_H
#define CB_STATECAMERATEST2_H

#include "CB_State.h"
#include "CB_Camera.h"
#include "CB_Screen.h"
#include "CB_SpriteSheet.h"
#include "CB_Beep.h"
#include "CB_Font.h"
#include "CB_FileLoader.h"
#include "renderer/CB_BoxRenderer.h"
#include "renderer/CB_SpriteRenderer.h"
#include "renderer/CB_LineRenderer.h"
#include "renderer/CB_SphereRenderer.h"
#include <sstream>

class CB_StateCameraTest2 : public CB_State
{
    public:
        CB_StateCameraTest2();
        virtual ~CB_StateCameraTest2();
        virtual void start();
        virtual void prerender();
        virtual void stop();
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StateCameraTest2(*this);};
        virtual void onKeyDown(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onKeyUp(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle);
        virtual void onMouseWheel(bool up, bool down);
        void drawBox(double x, double y, double z, double w, double h, double d);
        void drawBox(double x, double y, double z, double w, double h, double d, uint32_t color);
        void drawBox(double x, double y, double z, double w, double h, double d, CB_SpriteSheet * spriteSheet);
        void drawBox(double x, double y, double z, double w, double h, double d, CB_SpriteSheet * spriteSheet, string * sides);
        void addQuad(float ** verts, float * normals, double u1, double v1, double u2, double v2);
        void addLight(float x, float y, float z, float w, uint32_t ambient, uint32_t diffuse, GLenum light);
        void addLight(float x, float y, float z, float w, uint32_t ambient, uint32_t diffuse, uint32_t specular, GLenum light);
    protected:
    private:
        float speed;
        float interpolation;
        float theta;
        float tSpeed;
        CB_Camera * camera;
        CB_SpriteSheet * sheet;
        Mix_Music * music;
        CB_BoxRenderer * box;
        bool manualMode;
        bool musicPlaying;
        bool beepPlaying;
        bool displayDebug;
        bool displayHelp;
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
        double mZP;
        double mZM;
        string ticker;
        size_t tickerWidth;
        GLuint tickerList;
        GLuint instructionList;

        CB_Beep * beep;
        CB_BeepWave beepWave;
        CB_Font * font;
};

#endif // CB_STATECAMERATEST2_H
