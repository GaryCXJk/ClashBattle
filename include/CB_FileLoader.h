#ifndef CB_FILELOADER_H
#define CB_FILELOADER_H
#include "ClashBattle.h"
#include <cstdio>
using namespace std;

struct CB_FileBinary
{
    size_t length;
    uint8_t * data;
    CB_FileBinary()
    {
        length = 0;
        data = 0;
    }
};

class CB_FileLoader
{
    public:
        CB_FileLoader();
        virtual ~CB_FileLoader();
        static char * loadText(const char* fileName);
        static CB_FileBinary loadBinary(const char* fileName);
    protected:
    private:
};

#endif // CB_FILELOADER_H
