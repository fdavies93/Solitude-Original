#ifndef _ANIMATION_DEFINED_
#define _ANIMATION_DEFINED_
#include <allegro5/allegro.h>
#include <vector>
#include <string>
#include "spritesheetData.h"
using namespace std;
class animation{
    private:
        vector <ALLEGRO_BITMAP*> frames;
        string name;
        bool isLoaded;
    public:
        spritesheetData* mySpriteSheet;
        unsigned int numOnScreen;
        void addFrame(ALLEGRO_BITMAP*);
        void setName(string);
        void setSpriteSheet(spritesheetData*);
        void setIsLoaded(bool);
        bool getIsLoaded();
        string getName();
        ALLEGRO_BITMAP* getFrame(unsigned int);
        unsigned int getNumberOfFrames();
        animation();
        ~animation();
};

#endif
