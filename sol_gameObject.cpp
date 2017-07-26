#include "sol_gameObject.h"
#include "sol_logicConstants.h"
#include <allegro5/allegro.h>
using namespace std;

sol_gameObject::sol_gameObject(){
    x = 0;
    y = 0;
    id = 0;
}

int sol_gameObject::getSuperType(){
    return GAME_OBJECT_VIRTUAL;
}

void sol_gameObject::setId(unsigned int newId){
    id = newId;
}
