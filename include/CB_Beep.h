#ifndef CB_BEEP_H
#define CB_BEEP_H

#include "ClashBattle.h"

enum CB_BeepWave
{
    CB_BEEPWAVE_SINE = 0,
    CB_BEEPWAVE_SQUARE50 = 1,
    CB_BEEPWAVE_SQUARE25 = 2,
    CB_BEEPWAVE_SQUARE75 = 3,
    CB_BEEPWAVE_SQUARE33 = 4,
    CB_BEEPWAVE_SQUARE67 = 5,
    CB_BEEPWAVE_SAW = 6,
    CB_BEEPWAVE_TRIANGLE = 7
};

class CB_Beep
{
    public:
        CB_Beep();
        virtual ~CB_Beep();
        void setWave(double frequency);
        void setWave(double frequency, CB_BeepWave beepWave);
        void setWave(string tone);
        void setWave(string tone, CB_BeepWave beepWave);
        Mix_Chunk * getWave(double frequency, CB_BeepWave beepWave, double duration);
        Mix_Chunk * getMixChunk();
        //void play();
    protected:
    private:
        Mix_Chunk * tone;
        bool playing;
        const static double SAMPLE_RATE = 44100;
        static string TONE_MAP;
};

#endif // CB_BEEP_H
