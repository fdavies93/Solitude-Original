#include "spritesheetData.h"
using namespace std;

spritesheetData::spritesheetData(){
    myBitmap = NULL;
    filename = " ";
    numOnScreen = 0;
    isLoaded = false;
}

spritesheetData::~spritesheetData(){
    al_destroy_bitmap(myBitmap);
}
