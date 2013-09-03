#ifndef CB_STATEROOMTEST_H
#define CB_STATEROOMTEST_H

#include "ClashBattle.h"
#include "CB_State.h"
#include "CB_Room.h"
#include "CB_Tile.h"
#include "CB_SpriteSheet.h"
#include "renderer/CB_BoxRenderer.h"
#include "renderer/CB_SpriteRenderer.h"
#include "renderer/CB_GroupRenderer.h"
#include "renderer/CB_DepthScaleRenderer.h"

class CB_StateRoomTest : public CB_State
{
    public:
        CB_StateRoomTest();
        virtual ~CB_StateRoomTest();
        virtual void start();
        virtual void prerender();
        virtual void stop();
        virtual void run();
        virtual bool deactivate() {return false;};
        virtual bool activate() {return true;};
        virtual void draw();
        virtual void fadeOut() {};
        virtual void fadeIn() {};
        virtual CB_State * getInstance() {return new CB_StateRoomTest(*this);};
        virtual void onKeyDown(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onKeyUp(SDL_Keycode sym, SDL_Keymod mod);
        virtual void onMouseMove(int mouseX, int mouseY, int relX, int relY, bool left, bool right, bool middle);
        virtual void onLeftButtonUp(int mouseX, int mouseY);
        virtual void onRightButtonUp(int mouseX, int mouseY);
    protected:
    private:
        CB_Room * room;
        vector<CB_CollisionBound*> bounds;
        CB_SpriteSheet * sheet;
        CB_Tile * tileSolid;
        CB_Tile * tileWide;
        CB_Tile * tileHigh;
        CB_Tile * tileBig2x2;
        CB_Tile * tileDrop;
        CB_Tile * currentTile;

        double speed;
        double interpolation;
        double mXL;
        double mXR;
        double mYU;
        double mYD;
        double mZP;
        double mZM;
        double rXL;
        double rXR;
        double rYU;
        double rYD;
        int xMouse;
        int yMouse;
        CB_Vector2D pos;
        CB_Vector2D rot;
        double resetTime;
        double zoom;
};

#endif // CB_STATEROOMTEST_H
