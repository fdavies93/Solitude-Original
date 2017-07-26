#include "graphicsLoader.h"
#include "graphicsThreadData.h"
#include <iostream>
using namespace std;

void* startGraphicsThread(ALLEGRO_THREAD* thread, void* arguments){//handles messages
    //handle all this by creating a data structure and passing it to arguments
    al_init_image_addon();
    graphicsThreadData *myData = (graphicsThreadData *) arguments;
    //graphicsCache *myCache = (graphicsCache *) myData->cachePointer;
    //cout << myCache << "\n";
    graphicsLoader *myLoader = (graphicsLoader *) myData->loaderPointer;
    //cout << "works\n";
    while(!myLoader->stopLoadThread){
        while(!myLoader->activated){
            //cout << "works1\n";
            al_wait_cond(myLoader->messaged,myLoader->messageQueueMutex);
        }
        while(myLoader->messageQueue.size() > 0){
            //cout << myLoader->messageQueue.size();
            myLoader->runMessage(myLoader->messageQueue.front());
        }
        myLoader->activated = false;
        myLoader->shouldActivate = false;
    }
    //cout << "ended\n";
    return NULL;
}

graphicsLoader::graphicsLoader(){
    assert(myCache);
    messageQueueMutex = al_create_mutex();
    messaged = al_create_cond();
    stopLoadThread = false;
    shouldActivate = false;

    spriteActivated = false;
    spriteCondition = al_create_cond();
}

void graphicsLoader::activate(){
    if(!activated && shouldActivate){
        activated = true;
        al_broadcast_cond(messaged);
    }
}

bool graphicsLoader::addMessage(sol_graphicsMessageTypes type, void* object){
    if(type < GRAPHICS_MESSAGE_TYPE_COUNT){
        graphicsThreadMessage* newMessage = new graphicsThreadMessage;
        newMessage->object = object;
        newMessage->type = type;
        al_lock_mutex(messageQueueMutex);
        messageQueue.push(newMessage);
        al_unlock_mutex(messageQueueMutex);
    }
    else{
        cerr << "Message type out of bounds in graphicsLoader::addMessage.\n";
        return false;
    }
    shouldActivate = true;
    return true;
}

bool graphicsLoader::runMessage(graphicsThreadMessage* toRun){
    sol_graphicsMessageTypes type = toRun->type;
    void* object = toRun->object;
    switch(type){
        case GRAPHICS_MESSAGE_LOAD_ANIMATION: {
            animation* theAnimation = (animation *) object;
            cout << "Loading animation " << theAnimation->getName() << ".\n";
            loadAnimation(theAnimation);
            //delete myFileName;
        } break;
        case GRAPHICS_MESSAGE_LOAD_BITMAP: {
            sol_bitmap* theBitmap = (sol_bitmap *) object;
            cout << "Loading bitmap " << theBitmap->getName() << ".\n";
            loadBitmap(theBitmap);
        } break;
        case GRAPHICS_MESSAGE_LOAD_SPRITESHEET: {
            string* myFileName = (string *) object;
            cout << "Loading spritesheet " << *myFileName << ".\n";
            loadSpriteSheet(*myFileName);
            delete myFileName;
        } break;
        case GRAPHICS_MESSAGE_UNLOAD_ANIMATION: {

        } break;
        case GRAPHICS_MESSAGE_UNLOAD_BITMAP: {

        } break;
        case GRAPHICS_MESSAGE_UNLOAD_SPRITESHEET: {

        } break;
        case GRAPHICS_MESSAGE_KILL_DEAD: {
            //uncacheDead();
        } break;
        case GRAPHICS_MESSAGE_STOP: {
            stopLoadThread = true;
        } break;
        case GRAPHICS_MESSAGE_TEST: {
            /*for(unsigned int i = 0; i < 1000000; i++){
                cout << "test\n";
            }*/
        } break;
    }
    al_lock_mutex(messageQueueMutex);
    messageQueue.pop();
    al_unlock_mutex(messageQueueMutex);
}

ALLEGRO_BITMAP* graphicsLoader::loadSpriteSheet(string fileName){
    ALLEGRO_BITMAP* newGraphic = al_load_bitmap(fileName.c_str());
    assert(newGraphic);
    spritesheetData* sheetData = new spritesheetData;
    sheetData->filename = fileName;
    sheetData->myBitmap = newGraphic;
    sheetData->numOnScreen = 1;
    al_lock_mutex(myCache->messageMutex);
    myCache->addMessage(GRAPHICS_CACHE_MESSAGE_LOAD_SPRITESHEET,sheetData);
    al_unlock_mutex(myCache->messageMutex);

    al_unlock_mutex(myCache->graphicsCacheMutex);
    while(!spriteActivated){
        al_wait_cond(spriteCondition,myCache->graphicsCacheMutex);
    }
    ALLEGRO_BITMAP* graphicPointer = myCache->getGraphic(fileName)->myBitmap;

    al_unlock_mutex(myCache->graphicsCacheMutex);
    spriteActivated = false;
    if(graphicPointer){
        return graphicPointer;
    }
    return NULL;
}

void graphicsLoader::loadBitmap(sol_bitmap* theBitmap){
    bitmapData* bitmapMetaData = myCache->storage->getBitmapData(theBitmap->getName());
    assert(bitmapMetaData);
    ALLEGRO_BITMAP* graphic = myCache->getGraphic(bitmapMetaData->fileName)->myBitmap;
    assert(graphic);
    theBitmap->setBitmap(al_create_sub_bitmap(graphic,bitmapMetaData->x,bitmapMetaData->y,bitmapMetaData->width,bitmapMetaData->height));
    //cout << "blah\n";
    theBitmap->setSpriteSheet(myCache->getGraphic(bitmapMetaData->fileName));
    theBitmap->setIsLoaded(true);
}

void graphicsLoader::loadAnimation(animation* toLoad){
    animationData* animationMetaData = myCache->storage->getAnimationData(toLoad->getName());
    assert(animationMetaData);
    ALLEGRO_BITMAP* graphic = myCache->getGraphic(animationMetaData->getFileName())->myBitmap;
    if(graphic){
        ALLEGRO_BITMAP* curFrameBitmap;
        frameData curFrame;
        for(unsigned int curFrameIndex = 0; curFrameIndex < animationMetaData->getNumberOfFrames(); curFrameIndex++){
            curFrame = animationMetaData->getFrameData(curFrameIndex);
            curFrameBitmap = al_create_sub_bitmap(graphic,curFrame.x,curFrame.y,curFrame.width,curFrame.height);
            assert(curFrameBitmap);
            toLoad->addFrame(curFrameBitmap);
        }
        toLoad->setSpriteSheet(myCache->getGraphic(animationMetaData->getFileName()));
        toLoad->setIsLoaded(true);
    }
}

void graphicsLoader::start(graphicsCache* theCache){
    myCache = theCache;
    graphicsThreadData* threadData = new graphicsThreadData;
    threadData->cachePointer = myCache;
    threadData->loaderPointer = this;
    loadThread = al_create_thread(startGraphicsThread, threadData);
    al_start_thread(loadThread);
}
