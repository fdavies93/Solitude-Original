#include "animation.h"
#include <iostream>
using namespace std;

animation::animation(){
    isLoaded = false;
    numOnScreen = 0;
    mySpriteSheet = NULL;
}

void animation::addFrame(ALLEGRO_BITMAP* newBitmap){
    frames.push_back(newBitmap);
}

void animation::setName(string newName){
    name = newName;
}

void animation::setIsLoaded(bool newState){
    isLoaded = newState;
}

void animation::setSpriteSheet(spritesheetData* theSheet){
    mySpriteSheet = theSheet;
}

bool animation::getIsLoaded(){
    return isLoaded;
}

string animation::getName(){
    return name;
}

ALLEGRO_BITMAP* animation::getFrame(unsigned int index){
    if(index < frames.size()){
        return frames[index];//the leak?
    }
    else{
        return NULL;
    }
}

unsigned int animation::getNumberOfFrames(){
    return frames.size();
}

animation::~animation(){
    for(unsigned int i = 0; i < frames.size(); i++){
        al_destroy_bitmap(frames[i]);
    }
}
