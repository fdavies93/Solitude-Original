#include "sol_objectStaticBitmap.h"
#include "sol_logicConstants.h"
#include <allegro5/allegro.h>
using namespace std;

sol_objectStaticBitmap::sol_objectStaticBitmap(sol_templateStaticBitmap* newType,int64_t newCreationTick){
    assert(newType != NULL);
    type = newType;
    x = 0;
    y = 0;
    tickCreated = newCreationTick;
}

int sol_objectStaticBitmap::getSuperType(){
    return GAME_OBJECT_STATIC_BITMAP;
}
