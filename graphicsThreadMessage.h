#ifndef _GRAPHICS_THREAD_MESSAGE_DEFINED_
#define _GRAPHICS_THREAD_MESSAGE_DEFINED_
#include <allegro5/allegro.h>
#include "spritesheetData.h"
#include "sol_graphicsConstants.h"
using namespace std;

struct graphicsThreadMessage{
    sol_graphicsMessageTypes type;//as defined by sol_graphicsConstants
    void* object;//type based on above
};

#endif
