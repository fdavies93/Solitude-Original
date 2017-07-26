#ifndef _GRAPHICS_CACHE_MESSAGE_
#define _GRAPHICS_CACHE_MESSAGE_
#include "sol_graphicsConstants.h"
using namespace std;

struct graphicsCacheMessage{
    cacheMessageTypes type;
    void* object;
};

#endif
