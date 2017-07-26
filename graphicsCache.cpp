#include "graphicsCache.h"
#include "graphicsLoader.h"
#include "templateBst.cpp"
#include <iostream>
using namespace std;

graphicsCache::graphicsCache(string bitmapFileName, string animationFileName){
    storage = new sol_graphicsStorage(bitmapFileName, animationFileName);
    loader = new graphicsLoader;

    graphicsCacheMutex = al_create_mutex();
    graphicsCacheCond = al_create_cond();

    bitmapCacheMutex = al_create_mutex();
    bitmapCacheCond = al_create_cond();

    animationCacheMutex = al_create_mutex();
    animationCacheCond = al_create_cond();

    graphicsCacheLocked = false;
    bitmapCacheLocked = false;
    animationCacheLocked = false;

    messageMutex = al_create_mutex();

    loader->start(this);
}

void graphicsCache::sweepNumOnScreen(){
    list<animation*>::iterator curAnim;
    list<sol_bitmap*>::iterator curBmp;
    list<spritesheetData*>::iterator curGraphic;
    for(curAnim = cachedAnimations.begin(); curAnim != cachedAnimations.end(); curAnim++){
        (*curAnim)->numOnScreen = 0;
    }
    for(curBmp = cachedBitmaps.begin(); curBmp != cachedBitmaps.end(); curBmp++){
        (*curBmp)->numOnScreen = 0;
    }
    for(curGraphic = cachedGraphics.begin(); curGraphic != cachedGraphics.end(); curGraphic++){
        (*curGraphic)->numOnScreen = 0;
    }
}

spritesheetData* graphicsCache::cacheGraphic(string graphicName){
    list<spritesheetData*>::iterator curGraphic;
    for(curGraphic = cachedGraphics.begin(); curGraphic != cachedGraphics.end(); curGraphic++){
        if((*curGraphic)->filename == graphicName){
            (*curGraphic)->numOnScreen++;
            return *curGraphic;
        }
    }
    spritesheetData* newSpriteSheet = new spritesheetData;
    newSpriteSheet->filename = graphicName;
    newSpriteSheet->numOnScreen = 1;
    al_lock_mutex(graphicsCacheMutex);
    cachedGraphics.push_back(newSpriteSheet);
    al_unlock_mutex(graphicsCacheMutex);
    string* filename = new string(graphicName);
    loader->addMessage(GRAPHICS_MESSAGE_LOAD_SPRITESHEET,filename);
    return newSpriteSheet;
}

bool graphicsCache::cacheAnimation(string animationName){
    list<animation*>::iterator curAnim;
    for(curAnim = cachedAnimations.begin(); curAnim != cachedAnimations.end(); curAnim++){//stops it caching the same thing twice
        if((*curAnim)->getName() == animationName){
            (*curAnim)->numOnScreen++;
            (*curAnim)->mySpriteSheet->numOnScreen++;
            return true;
        }
    }

    animation* newAnimation = new animation;
    animationData* animationMetaData = storage->getAnimationData(animationName);
    assert(animationMetaData);
    newAnimation->setSpriteSheet(cacheGraphic(animationMetaData->getFileName()));
    newAnimation->setName(animationName);
    newAnimation->setIsLoaded(false);
    newAnimation->numOnScreen = 1;
    al_lock_mutex(animationCacheMutex);
    cachedAnimations.push_back(newAnimation);
    al_unlock_mutex(animationCacheMutex);

    loader->addMessage(GRAPHICS_MESSAGE_LOAD_ANIMATION,newAnimation);
    return true;
}

//the way forward is to calculate the number of each spritesheet AFTER it's been loaded...

bool graphicsCache::cacheBitmap(string bitmapName){
    //al_lock_mutex(bitmapCacheMutex);
    list<sol_bitmap*>::iterator curBmp;
    for(curBmp = cachedBitmaps.begin(); curBmp != cachedBitmaps.end(); curBmp++){//stops it caching the same thing twice
        if((*curBmp)->getName() == bitmapName){
            //al_unlock_mutex(bitmapCacheMutex);
            (*curBmp)->numOnScreen++;
            return true;
        }
    }
    bitmapData* bitmapMetaData = storage->getBitmapData(bitmapName);//get metadata
    assert(bitmapMetaData);
    sol_bitmap* newBitmap = new sol_bitmap(bitmapName);
    newBitmap->setSpriteSheet(cacheGraphic(bitmapMetaData->fileName));
    newBitmap->numOnScreen = 1;
    al_lock_mutex(bitmapCacheMutex);
    cachedBitmaps.push_back(newBitmap);
    al_unlock_mutex(bitmapCacheMutex);
    loader->addMessage(GRAPHICS_MESSAGE_LOAD_BITMAP,newBitmap);
    //revised function ends here
    return true;
}

/*ALLEGRO_BITMAP* graphicsCache::loadGraphic(string fileName){//bit more efficient just to chuck stuff in here
    spritesheetCache* graphicPointer = NULL;
    al_lock_mutex(graphicsCacheMutex);
    graphicPointer = cachedGraphics.get(fileName);
    al_unlock_mutex(graphicsCacheMutex);
    if(!graphicPointer){
        string *graphicName = new string(fileName);
        ALLEGRO_BITMAP* newGraphic = al_load_bitmap(fileName.c_str());
        assert(newGraphic);
        loader->addMessage(GRAPHICS_MESSAGE_LOAD_SPRITESHEET,graphicName);
    }
    //assert(graphicPointer);
    return graphicPointer;
}*/

/*
void graphicsCache::test_printBitmap(string bitmapName){
    sol_bitmap* bitmapPointer;
    for(int curBitmap=0; curBitmap < cachedBitmaps.size(); curBitmap++){
        bitmapPointer = cachedBitmaps[curBitmap];
        if(bitmapName == bitmapPointer->getName()){
            break;
        }
        else if(curBitmap == cachedBitmaps.size()-1){
            return;
        }
    }
    al_draw_bitmap(bitmapPointer->getBitmap(),0,0,0);
}

void graphicsCache::test_printAnimation(string animationName,unsigned int theFrame){
    animation* animationPointer;
    for(int curAnimation=0; curAnimation < cachedAnimations.size(); curAnimation++){
        animationPointer = cachedAnimations[curAnimation];
        if(animationName == animationPointer->getName()){
            break;
        }
        else if(curAnimation == cachedAnimations.size()-1){
            return;
        }
    }
    al_draw_bitmap(animationPointer->getFrame(theFrame),0,0,0);
}*/

animation* graphicsCache::getAnimation(string animationName){
    list<animation*>::iterator curAnim;
    al_lock_mutex(animationCacheMutex);
    if(!animationCacheLocked){
        animation* animationPointer;
        //cout << "getting...\n";
        for(curAnim = cachedAnimations.begin(); curAnim != cachedAnimations.end(); curAnim++){
            animationPointer = *curAnim;
            if(animationName == animationPointer->getName()){
                if(animationPointer->getIsLoaded()){
                    return animationPointer;
                }
                else{
                    return NULL;
                }
            }
        }
    }
    al_unlock_mutex(animationCacheMutex);
    return NULL;
}

sol_bitmap* graphicsCache::getBitmap(string bitmapName){
    list<sol_bitmap*>::iterator curBitmap;
    sol_bitmap* bitmapPointer;
    for(curBitmap = cachedBitmaps.begin(); curBitmap != cachedBitmaps.end(); curBitmap++){
        bitmapPointer = *curBitmap;
        if(bitmapName == bitmapPointer->getName()){
            //cout << "Name: " << bitmapName << ", Address: " <<  bitmapPointer << "\n";
            return bitmapPointer;
        }
    }
    return NULL;
}

spritesheetData* graphicsCache::getGraphic(string filename){
    spritesheetData* graphicsPointer;
    list<spritesheetData*>::iterator curGraphic;
    for(curGraphic = cachedGraphics.begin(); curGraphic != cachedGraphics.end(); curGraphic++){
        graphicsPointer = *curGraphic;
        if(graphicsPointer->filename == filename){
            return graphicsPointer;
        }
    }
    return NULL;
}

animationData* graphicsCache::getAnimationData(string myName){
    return storage->getAnimationData(myName);
}

void graphicsCache::addMessage(cacheMessageTypes messageType, void* messageObject){
    graphicsCacheMessage* newMessage = new graphicsCacheMessage;
    newMessage->type = messageType;
    newMessage->object = messageObject;
    al_lock_mutex(messageMutex);
    messages.push(newMessage);
    al_unlock_mutex(messageMutex);
}

void graphicsCache::runNextMessage(){
    al_lock_mutex(messageMutex);
    graphicsCacheMessage* nextMessage = messages.front();
    al_unlock_mutex(messageMutex);
    switch(nextMessage->type){
        case GRAPHICS_CACHE_MESSAGE_LOAD_ANIMATION: {

        }
        break;
        case GRAPHICS_CACHE_MESSAGE_LOAD_BITMAP: {
        }
        break;
        case GRAPHICS_CACHE_MESSAGE_LOAD_SPRITESHEET: {
            spritesheetData* theSpriteSheet = (spritesheetData*) nextMessage->object;
            ALLEGRO_BITMAP* newBitmap = al_clone_bitmap(theSpriteSheet->myBitmap);
            al_destroy_bitmap(theSpriteSheet->myBitmap);
            //theSpriteSheet->myBitmap = newBitmap;
            list<spritesheetData*>::iterator curGraphic;
            for(curGraphic = cachedGraphics.begin(); curGraphic != cachedGraphics.end(); curGraphic++){
                if((*curGraphic)->filename == theSpriteSheet->filename){
                    (*curGraphic)->myBitmap = newBitmap;
                    (*curGraphic)->isLoaded = true;
                }
            }
            /*al_lock_mutex(graphicsCacheMutex);
            cachedGraphics.push_back(theSpriteSheet);
            al_unlock_mutex(graphicsCacheMutex);*/

            //al_destroy_bitmap(theSpriteSheet->myBitmap);
            //delete theSpriteSheet;

            al_lock_mutex(messageMutex);
            messages.pop();
            al_unlock_mutex(messageMutex);

            loader->spriteActivated = true;
            al_broadcast_cond(loader->spriteCondition);
        }
        break;
    }
}
/*
spritesheetData* graphicsCache::getGraphic(string filename){
    for(unsigned int i = 0; i < cachedGraphics.size(); i++){
        if(cachedGraphics[i]->filename == filename){
            return cachedGraphics[i];
        }
    }
    return NULL;
}*/

bool graphicsCache::messagesEmpty(){
    return messages.empty();
}

void graphicsCache::uncacheDead(){
    list<animation*>::iterator curAnim;
    list<sol_bitmap*>::iterator curBmp;
    list<spritesheetData*>::iterator curGraphic;
    animation* animPointer;
    sol_bitmap* bmpPointer;
    spritesheetData* graphicPointer;
    unsigned int curIndex = 0;
    for(curAnim = cachedAnimations.begin(); curAnim != cachedAnimations.end(); curAnim++){
        //cout << "Animation: " << (*curAnim)->getName() << ", Number: " << (*curAnim)->numOnScreen << "\n";
        //cachedAnimations[curAnim]->numOnScreen = 0;
        animPointer = *curAnim;
        //if(animPointer == NULL){cout << "NULL" << "\n";}
        if(animPointer->numOnScreen == 0){
            cout << "Unloading animation " << animPointer->getName() << "\n";
            delete animPointer;
            al_lock_mutex(animationCacheMutex);
            cachedAnimations.erase(curAnim);
            al_unlock_mutex(animationCacheMutex);
            curAnim--;
        }
        else if(animPointer->mySpriteSheet){
            animPointer->mySpriteSheet->numOnScreen++;
        }
    }
    for(curBmp = cachedBitmaps.begin(); curBmp != cachedBitmaps.end(); curBmp++){
        //cout << "Bitmap: " << (*curBmp)->getName() << ", Number: " << (*curBmp)->numOnScreen << "\n";
        bmpPointer = *curBmp;
        if(bmpPointer->numOnScreen == 0){
            cout << "Unloading bitmap " << bmpPointer->getName() << "\n";
            delete bmpPointer;
            al_lock_mutex(bitmapCacheMutex);
            cachedBitmaps.erase(curBmp);
            al_unlock_mutex(bitmapCacheMutex);
            curBmp--;
        }
        else if(bmpPointer->mySpriteSheet){
                bmpPointer->mySpriteSheet->numOnScreen++;
        }
        //cachedBitmaps[curBmp]->numOnScreen = 0;
    }
    for(curGraphic = cachedGraphics.begin(); curGraphic != cachedGraphics.end(); curGraphic++){
        graphicPointer = *curGraphic;
        //cout << "Spritesheet: " << (*curGraphic)->filename << ", Number: " << (*curGraphic)->numOnScreen << "\n";
        if(graphicPointer->numOnScreen == 0){
            cout << "Unloading spritesheet " << graphicPointer->filename << "\n";
            delete graphicPointer;
            al_lock_mutex(graphicsCacheMutex);
            cachedGraphics.erase(curGraphic);
            al_unlock_mutex(graphicsCacheMutex);
            curGraphic--;
        }
        //cachedGraphics[curGraphic]->numOnScreen = 0;
    }
    //sweepNumOnScreen();
}
