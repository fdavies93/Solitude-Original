#ifndef _GRAPHICS_CACHE_INCLUDED_
#define _GRAPHICS_CACHE_INCLUDED_

#include <string>
#include <list>
#include <queue>
#include "templateBst.h"
#include "animation.h"
#include "spritesheetData.h"
#include "sol_graphicsStorage.h"
#include "graphicsCacheMessage.h"
using namespace std;

class graphicsLoader;
static void* startGraphicsThread(ALLEGRO_THREAD*, void*);

//MURDER YOUR DARLINGS
class graphicsCache{
    friend class graphicsLoader;
    friend void* startGraphicsThread(ALLEGRO_THREAD*, void*);
    private:
        sol_graphicsStorage* storage;

        ALLEGRO_BITMAP* loadGraphic(string);

        ALLEGRO_MUTEX* graphicsCacheMutex;
        ALLEGRO_COND* graphicsCacheCond;
        bool graphicsCacheLocked;

        ALLEGRO_MUTEX* bitmapCacheMutex;
        ALLEGRO_COND* bitmapCacheCond;
        bool bitmapCacheLocked;

        ALLEGRO_MUTEX* animationCacheMutex;
        ALLEGRO_COND* animationCacheCond;
        bool animationCacheLocked;

        list<spritesheetData*> cachedGraphics;//time to murder some darlings
        list<animation*> cachedAnimations;
        list<sol_bitmap*> cachedBitmaps;
        //vector<string> lockedAnimations;
        //vector<string> lockedBitmaps;
        //vector<string> lockedGraphics;

        ALLEGRO_MUTEX* messageMutex;
        queue<graphicsCacheMessage*> messages;
    public:
        graphicsLoader* loader;//move back to private after tests

        void addMessage(cacheMessageTypes,void*);
        void runNextMessage();
        void sweepNumOnScreen();//reset all numbers on screen of all objects to 0; called once per tick
        void uncacheDead();

        //spritesheetData* getGraphic(string);

        bool messagesEmpty();
        spritesheetData* cacheGraphic(string);
        bool cacheAnimation(string);//grabs animation from storage, loads bmp into frame
        bool cacheBitmap(string);
        spritesheetData* getGraphic(string);
        animation* getAnimation(string);
        sol_bitmap* getBitmap(string);
        void test_printBitmap(string);
        void test_printAnimation(string,unsigned int);
        graphicsCache(string, string);//bitmap filename, animation filename
        animationData* getAnimationData(string);
};
#include "graphicsLoader.h"
#endif
