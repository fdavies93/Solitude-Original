#ifndef _SPRITESHEET_DATA_INCLUDED_
#define _SPRITESHEET_DATA_INCLUDED_
#include <allegro5/allegro.h>
#include <string>
using namespace std;

class spritesheetData{
    public:
    ALLEGRO_BITMAP* myBitmap;
    string filename;
    unsigned int numOnScreen;
    bool isLoaded;
    spritesheetData();
    ~spritesheetData();
};

#endif
