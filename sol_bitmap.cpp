#include "sol_bitmap.h"
#include <allegro5/allegro.h>
#include <iostream>
using namespace std;

ALLEGRO_BITMAP* sol_bitmap::getBitmap(){
    //cout << this;
    //cout << name << "\n";
    //al_draw_bitmap(bitmap, 0, 0, 1);
    //al_flip_display();
    return bitmap;
}



string sol_bitmap::getName(){
    return name;
}

void sol_bitmap::setIsLoaded(bool newState){
    isLoaded = newState;
}

void sol_bitmap::setSpriteSheet(spritesheetData* sheet){
    mySpriteSheet = sheet;
}

void sol_bitmap::setBitmap(ALLEGRO_BITMAP* newBitmap){
    bitmap = newBitmap;
}

bool sol_bitmap::getIsLoaded(){
    return isLoaded;
}

sol_bitmap::sol_bitmap(string myName){
    //al_draw_bitmap(bitmap,0,0,1);
    //al_flip_display();
    isLoaded = false;
    name = myName;
    bitmap = NULL;
    numOnScreen = 0;
    mySpriteSheet = NULL;
}

sol_bitmap::~sol_bitmap(){
    al_destroy_bitmap(bitmap);
}
