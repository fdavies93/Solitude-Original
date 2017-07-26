#include "sol_templateStaticBitmap.h"
#include <allegro5/allegro.h>
using namespace std;

sol_templateStaticBitmap::sol_templateStaticBitmap(string myName, string myBitmap, double myWidth, double myHeight){
    name = myName;
    bitmapName = myBitmap;
    width = myWidth;
    height = myHeight;
}

string sol_templateStaticBitmap::getName(){
    return name;
}

string sol_templateStaticBitmap::getBitmapName(){
    return bitmapName;
}
