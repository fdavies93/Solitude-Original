#include "sol_screenBitmap.h"
#include "allegro5/allegro.h"
using namespace std;

int sol_screenBitmap::type(){
    return GRAPHICS_OBJECT_BITMAP;
}

bool sol_screenBitmap::print(){
    if(bitmap->getIsLoaded()){
        ALLEGRO_BITMAP* test = bitmap->getBitmap();
        assert(test);
        al_draw_bitmap(test, x, y, 0);
    }
	return true;
}

sol_bitmap* sol_screenBitmap::getBitmap(){
    return bitmap;
}

/*sol_screenBitmap::sol_screenBitmap(){
    x = 0;
    y = 0;
}*/

sol_screenBitmap::~sol_screenBitmap(){
    //bitmap->numOnScreen -= 1;
    //bitmap->mySpriteSheet->numOnScreen -= 1;
}

sol_screenBitmap::sol_screenBitmap(sol_bitmap* myBitmap, int myX, int myY){
    bitmap = myBitmap;
    //bitmap->numOnScreen += 1;
    //bitmap->mySpriteSheet->numOnScreen += 1;
    x = myX;
    y = myY;
}
