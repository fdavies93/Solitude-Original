#ifndef GRAPHICS_THREAD_DATA_INCLUDED
#define GRAPHICS_THREAD_DATA_INCLUDED
#include "graphicsCache.h"
#include "graphicsLoader.h"
using namespace std;

struct graphicsThreadData{
    graphicsLoader *loaderPointer;
    graphicsCache *cachePointer;
};

#endif
