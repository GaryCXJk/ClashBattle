#ifndef CLASHBATTLE_H
#define CLASHBATTLE_H
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif
#include <cmath>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <stdint.h>
#include <float.h>
#ifdef __APPLE__
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_mutex.h>
#else
#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_thread.h>
#include <SDL_mutex.h>
#endif
#define GLEW_STATIC
extern "C"
{
    #include <GL/glew.h>
}
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL_Mixer.h>
#include <SDL_image.h>
#include <angelscript.h>
#include <scriptstdstring/scriptstdstring.h>
#include <scriptbuilder/scriptbuilder.h>
using namespace std;
#include "CB_FPS.h"

#define PI 3.14159265
#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i))

enum CB_StringEncoding
{
    CB_STRING_ENCODING_ASCII = 1,
    CB_STRING_ENCODING_UTF8 = 2
};

enum CB_CollisionEnum
{
    CB_COLLISION_NONE = 0,
    CB_COLLISION_SOLID = 1,
    CB_COLLISION_DROPTHROUGH = 2,
    CB_COLLISION_ZONE = 3
};

void CB_Perspective(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble fovy, GLdouble zNear, GLdouble zFar);

#endif // CLASHBATTLE_H
