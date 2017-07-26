#include "sol_objectStaticAnimation.h"
#include "sol_logicConstants.h"
#include <allegro5/allegro.h>
using namespace std;

sol_objectStaticAnimation::sol_objectStaticAnimation(sol_templateStaticAnimation* newType,int64_t newCreationTick){
    assert(newType != NULL);
    type = newType;
    x = 0;
    y = 0;
    tickCreated = newCreationTick;
}

int sol_objectStaticAnimation::getSuperType(){
    return GAME_OBJECT_STATIC_ANIMATION;
}
