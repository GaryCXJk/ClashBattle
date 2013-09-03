#include "CB_Beep.h"

string CB_Beep::TONE_MAP = "C.D.EF.G.A.B";

CB_Beep::CB_Beep()
{
    tone = new Mix_Chunk();
    playing = false;
}

CB_Beep::~CB_Beep()
{
}

void CB_Beep::setWave(double frequency)
{
    setWave(frequency, CB_BEEPWAVE_SQUARE50);
}

void CB_Beep::setWave(double frequency, CB_BeepWave beepWave)
{
    Mix_Chunk * rTone = getWave(frequency, beepWave, 0);
    tone->abuf = rTone->abuf;
    tone->alen = rTone->alen;
    tone->volume = MIX_MAX_VOLUME;
    delete rTone;
}

void CB_Beep::setWave(string tone)
{
    setWave(tone, CB_BEEPWAVE_SQUARE50);
}

void CB_Beep::setWave(string tone, CB_BeepWave beepWave)
{
    size_t cTone = TONE_MAP.find(tone[0]);
    if(cTone == string::npos)
    {
        return;
    }
    size_t mPos = 2;
    if(tone[1] == '#' || tone[1] == '+')
    {
        cTone++;
    }
    else if(tone[1] == '-')
    {
        cTone--;
    }
    else
    {
        mPos--;
    }
    int octave = 3;
    if(mPos != tone.size())
    {
        octave = strtol(tone.substr(mPos).c_str(), 0, 0) - 1;
    }
    cTone+= 4;
    cTone+= 12 * octave;
    setWave((double)pow(2.0, ((double)cTone - 49.0) / 12.0) * 440.0, beepWave);
}

Mix_Chunk * CB_Beep::getWave(double frequency, CB_BeepWave beepWave, double duration)
{
    Uint8 * buffer;
    int samples = (int)(SAMPLE_RATE / frequency);
    if(samples % 2)
    {
        samples++;
    }
    samples*= 2;

    double freq = (SAMPLE_RATE / (double)samples);

    int channel = 2;

    if(duration > 0)
    {
        samples = SAMPLE_RATE * duration * 2;
    }

    buffer = new Uint8[samples * channel];

    for(int i = 0; i < samples; i++)
    {
        double data = 0;
        double md = 1;
        switch(beepWave)
        {
            case CB_BEEPWAVE_SINE:
                data = sin((double)i * 2.0 * PI * freq / SAMPLE_RATE);
                break;
            case CB_BEEPWAVE_SQUARE75:
                md*= 3;
            case CB_BEEPWAVE_SQUARE25:
                md/= 2;
            case CB_BEEPWAVE_SQUARE50:
                md/= 2;
                data = -1;
                if(i < samples * md)
                {
                    data = 1;
                }
                break;
            case CB_BEEPWAVE_SQUARE67:
                md*= 2;
            case CB_BEEPWAVE_SQUARE33:
                md/= 3;
                data = -1;
                if(i < samples * md)
                {
                    data = 1;
                }
                break;
            case CB_BEEPWAVE_SAW:
                data = -1 + (2 * (double)i / (double) samples);
                break;
            case CB_BEEPWAVE_TRIANGLE:
                data = -1 + min((4 * (double)i / (double) samples), 4 - (4 * (double)i / (double) samples));
                break;
            default:
                break;
        }
        for(int j = 0; j < channel; j++)
        {
            buffer[i * channel + j] = (Uint8)(data * 127);
        }
    }

    Mix_Chunk * rTone = new Mix_Chunk();

    rTone->abuf = buffer;
    rTone->alen = samples * channel;
    rTone->volume = MIX_MAX_VOLUME;

    return rTone;
}

Mix_Chunk * CB_Beep::getMixChunk()
{
    return tone;
}
