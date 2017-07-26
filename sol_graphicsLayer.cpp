#include "sol_graphicsLayer.h"
#include "sol_animation.h"
#include "sol_graphicsConstants.h"
#include <iostream>
using namespace std;

sol_graphicsLayer::sol_graphicsLayer(void){
    name = MEANINGLESS_STRING_CONSTANT;
    depth = 0;
}

sol_graphicsLayer::sol_graphicsLayer(string myName, int myDepth){
    if(name != MEANINGLESS_STRING_CONSTANT){
        name = myName;
        depth = myDepth;
    }
    else{
        cout << "Don't name a layer like this. In sol_graphicsLayer constructor.\n";
    }
}

void sol_graphicsLayer::addAnimation(sol_screenAnimation* animToAdd){
    animations.push_back(animToAdd);
}

void sol_graphicsLayer::addBitmap(sol_screenBitmap* bitmapToAdd){
    //cout << "graphicsLayer::addBitmap; Name: " << bitmapToAdd->getBitmap()->getName() << ", Address: " <<  bitmapToAdd->getBitmap() << "\n";
    bitmaps.push_back(bitmapToAdd);
    //cout << index << "\n";//REPEATS AFTER 4 - somewhat suspicious - but appears to work fine
    //cout << "graphicsLayer::addBitmap; Name: " << bitmaps.back()->getBitmap()->getName() << ", Address: " <<  bitmaps.back()->getBitmap() << ", Number: " << bitmaps.size()-1 << "\n";
}

int sol_graphicsLayer::addObject(sol_virtualGraphicsObject* objectToAdd){
    if(objectToAdd != NULL){
            int objectId;
            switch(objectToAdd->type()){
                case GRAPHICS_OBJECT_ANIMATION:
                    sol_screenAnimation* newAnimation;
                    newAnimation = (sol_screenAnimation*) objectToAdd;
                    animations.push_back(newAnimation);
                break;
                case GRAPHICS_OBJECT_BITMAP:
                    sol_screenBitmap* newBitmap;
                    newBitmap = (sol_screenBitmap*) objectToAdd;
                    bitmaps.push_back(newBitmap);
                break;
                default:
                    cout << "Invalid object type sent to sol_graphicsLayer::addObject.\n";
                    return -1;
                break;
            }
            return 0;
    }
    else{
        cout << "Null pointer sent to sol_graphicsLayer::addObject.\n";
        return -1;
    }
}

/*bool sol_graphicsLayer :: removeBitmap(int bitmapId){
    sol_screenBitmap* bitmapPointer = bitmaps.getObject(bitmapId);
    delete bitmapPointer;
    bitmaps.removeObject(bitmapId);
    return true;
}

bool sol_graphicsLayer :: removeAnimation(int animationId){
    sol_screenAnimation* animationPointer = animations[animationId];
    delete animationPointer;
    animations.
    return true;
}*/

void sol_graphicsLayer :: clearLayer(){
    sol_screenAnimation* animationPointer;
    sol_screenBitmap* bitmapPointer;
    for(int i = 0; i < animations.size(); i++){
        animationPointer = animations[i];
        delete animationPointer;
    }
    animations.clear();
    for(int i = 0; i < bitmaps.size(); i++){
        bitmapPointer = bitmaps[i];
        delete bitmapPointer;
    }
    bitmaps.clear();
}

bool sol_graphicsLayer :: print(){
    for(int animCount = 0; animCount < animations.size(); animCount++){
        animations[animCount]->print();
    }
    for(int bmpCount = 0; bmpCount < bitmaps.size(); bmpCount++){
        bitmaps[bmpCount]->print();
    }
    return true;
}
