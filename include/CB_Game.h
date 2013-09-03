#ifndef CB_GAME_H
#define CB_GAME_H
#include "ClashBattle.h"
#include "CB_Event.h"
#include "CB_StateManager.h"
#include "CB_Screen.h"
#include "CB_Renderer.h"

class CB_Game : public CB_Event
{
    public:
        CB_Game();
        virtual ~CB_Game();
        bool init();
        void run();
        void draw();
        void cleanup();
        void execute();
        void onEvent(SDL_Event* event);
        void onResize(int w, int h);
        void onExit();
        void setTitle(string title);
        void setScreenSize(uint32_t width, uint32_t height);
        void setTileSize(uint32_t);
        void setInitState(string);
        bool isRunning();
        uint32_t getTileSize();
    protected:
    private:
        string gameTitle;
        uint32_t screenWidth;
        uint32_t screenHeight;
        uint32_t tileSize;
        bool running;
        string initState;
        SDL_Window* mainWindow;
};

#endif // CB_GAME_H
