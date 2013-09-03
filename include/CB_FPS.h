#ifndef CB_FPS_H
#define CB_FPS_H
#include "ClashBattle.h"

class CB_FPS
{
    public:
        CB_FPS();
        virtual ~CB_FPS();
        static uint32_t create(uint32_t targetFPS);
        static CB_FPS * get(uint32_t id);
        void setCurrentTime();
        uint32_t getCurrentSetTime();
        void setTargetFPS(uint32_t newTargetFPS);
        uint32_t getTargetTicksPerFrame();
        uint32_t getTargetRemainder();
        uint32_t getTargetFrames();
        float getDelta();
        uint32_t getDeltaTick();
        void endFrame();
    protected:
    private:
        static uint8_t init();
        uint32_t targetFPS;
        uint32_t lastTick;
        uint32_t deltaRemainder;
        uint32_t subTick;

        static map<uint32_t,CB_FPS*> fpsMap;
        static uint8_t initVar;
};

const uint32_t CB_FPS_CALCULATION = 0;
const uint32_t CB_FPS_RENDER = 1;

#endif // CB_FPS_H
