#include "CB_Game.h"

int CB_StateRun(void * data)
{
    CB_Game * game = (CB_Game*)data;
    game->run();
    return 0;
}

/**
 * Creates a new instance of CB_Game.
 */
CB_Game::CB_Game()
{
    running = true;
    mainWindow = 0;
    gameTitle = "ClashBattle";
    screenWidth = 640;
    screenHeight = 480;
}

CB_Game::~CB_Game()
{
    //dtor
}

bool CB_Game::init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

    if((mainWindow = SDL_CreateWindow(gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_OPENGL)) == NULL)
    {
        return false;
    }

    SDL_GL_CreateContext(mainWindow);

    GLenum err = glewInit();
    if(GLEW_OK != err)
    {
        printf("Error: %s\n", glewGetErrorString(err));
    }
    SDL_JoystickEventState(SDL_ENABLE);

    glViewport(0, 0, screenWidth, screenHeight);

    CB_Screen::setScreenSize(screenWidth, screenHeight);
    CB_Screen::setSize(screenWidth, screenHeight);
    CB_Screen::setFov(45);

    CB_Renderer::init();

    CB_StateManager::setState(initState);

    CB_ShaderManager::addShader("basic");

    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, 1, -1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glColor3f(0.0f, 0.0f, 0.0f);

    SDL_GL_SwapBuffers();

    //ZGameStateManager::SetActiveAppState(GAMESTATE_SPLASH);*/

    return true;
}

void CB_Game::run()
{
    SDL_Event event;
    CB_FPS* calcFPS = CB_FPS::get(CB_FPS_CALCULATION);
    while(isRunning())
    {
        while(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT) > 0)
        {
            CB_StateManager::onEvent(&event);
            onEvent(&event);
        }
        calcFPS->setCurrentTime();
        CB_StateManager::run();
        SDL_Delay(calcFPS->getTargetFrames() - calcFPS->getDeltaTick());
        calcFPS->endFrame();
    }
}

void CB_Game::draw()
{
    CB_StateManager::draw();
    SDL_GL_SwapWindow(mainWindow);
}

void CB_Game::execute()
{
    init();
    SDL_Event event;
    CB_FPS* renderFPS = CB_FPS::get(CB_FPS_RENDER);
    SDL_CreateThread(CB_StateRun, NULL, this);
    while(running)
    {
        while(SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0)
        {
            onEvent(&event);
        }
        SDL_PumpEvents();
        renderFPS->setCurrentTime();
        while(renderFPS->getDeltaTick() < renderFPS->getTargetFrames())
        {

        }
        draw();
        CB_Renderer::process();
        renderFPS->endFrame();
    }
}

void CB_Game::onEvent(SDL_Event* event)
{
    CB_Event::onEvent(event);
}

void CB_Game::onResize(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
    glViewport(0, 0, w, h);
}

void CB_Game::onExit()
{
    running = false;
}

void CB_Game::setTitle(string title)
{
    gameTitle = title;
}

void CB_Game::setScreenSize(uint32_t width, uint32_t height)
{
    screenWidth = width;
    screenHeight = height;
}

void CB_Game::setTileSize(uint32_t size)
{
    tileSize = size;
}

void CB_Game::setInitState(string state)
{
    initState = state;
}

bool CB_Game::isRunning()
{
    bool isRun = running;
    return isRun;
}

uint32_t CB_Game::getTileSize()
{
    return tileSize;
}
