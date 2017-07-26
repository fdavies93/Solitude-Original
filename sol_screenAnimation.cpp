#include "sol_screenAnimation.h"
#include "sol_graphicsConstants.h"
#include <allegro5/allegro.h>
using namespace std;

sol_screenAnimation::sol_screenAnimation(animation* theAnimation, int newX, int newY, int newFrame){
    storedAnimation = theAnimation;
    //storedAnimation->numOnScreen += 1;
    //storedAnimation->mySpriteSheet->numOnScreen += 1;
    //cout << storedAnimation->numOnScreen << "\n";
    x = newX;
    y = newY;
    curFrame = newFrame;
}

sol_screenAnimation::~sol_screenAnimation(){
    //storedAnimation->numOnScreen -= 1;
    //storedAnimation->mySpriteSheet->numOnScreen -= 1;
    //cout << storedAnimation->numOnScreen << "\n";
}

animation* sol_screenAnimation::GetAnimation(){
    return storedAnimation;
}

int sol_screenAnimation::type(){
    return GRAPHICS_OBJECT_ANIMATION;
}

bool sol_screenAnimation::print(){
    if(storedAnimation->getIsLoaded()){
        ALLEGRO_BITMAP* theBitmap = storedAnimation->getFrame(curFrame);
        al_draw_bitmap(theBitmap,x,y,0);//here is the leak
    }
    return true;
}

int sol_screenAnimation::nextFrame(){
    curFrame++;
    if(curFrame >= storedAnimation->getNumberOfFrames()){
        curFrame = 0;
    }
    return curFrame;
}
