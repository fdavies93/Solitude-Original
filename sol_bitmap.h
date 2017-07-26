#ifndef _SOL_BITMAP_DEFINED_
#define _SOL_BITMAP_DEFINED_
#include <string>
#include <allegro5/allegro.h>
#include "spritesheetData.h"
using namespace std;

class sol_bitmap{//Bitmaps do not individually load from CSVs; they are loaded en mass from one file. This is because only 6 pieces of data are needed to define a bitmap.
    private:
        string name;
        ALLEGRO_BITMAP* bitmap;
        bool isLoaded;
    public:
        spritesheetData* mySpriteSheet;
        unsigned int numOnScreen;
        ALLEGRO_BITMAP* getBitmap();
        string getName();
        void setSpriteSheet(spritesheetData*);
        void setBitmap(ALLEGRO_BITMAP*);
        void setIsLoaded(bool);
        bool getIsLoaded();
        sol_bitmap(string);//name
        ~sol_bitmap();
};

#endif
