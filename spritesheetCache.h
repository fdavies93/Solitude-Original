#ifndef _SPRITESHEET_CACHE_DEFINED_
#define _SPRITESHEET_CACHE_DEFINED_
#include <allegro5/allegro.h>
#include <string>
using namespace std;

struct spritesheetCache{
    ALLEGRO_BITMAP* bitmap;
    string name;
    unsigned int numOnScreen;
};

#endif
