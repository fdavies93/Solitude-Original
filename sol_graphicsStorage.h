#ifndef _GRAPHICS_STORAGE_DEFINED_
#define _GRAPHICS_STORAGE_DEFINED_
#include <string>
#include <allegro5/allegro.h>
#include <vector>
#include "sol_animation.h"
#include "sol_bitmap.h"
#include "templateBst.h"
#include "animationData.h"
#include "bitmapData.h"
using namespace std;

/* STORE ANIMATIONS, BITMAPS IN TWO BSTS BY NAME; FIND THEM BY SEARCHING THE RESPECTIVE BST
   PERFECTLY BALANCE THE BSTs AT THE END OF LOADXFROMCSV FOR MAXIMUM SEARCH EFFICIENCY */
class sol_graphicsStorage{
    private:
        templateBst <animationData> animationFiles;//NEW FUNCTIONS
        templateBst <bitmapData> bitmapFiles;//NEW FUNCTIONS
        //vector <sol_animation> animations;
        //vector <sol_bitmap> bitmaps;
    public:
        sol_graphicsStorage(string, string);//bitmap file, animation file
        sol_bitmap* getBitmapByName(string);
//        sol_animation* getAnimationByName(string);
        animationData* getAnimationData(string);//NEW FUNCTIONS; returns pointer to animation
        bitmapData* getBitmapData(string);//NEW FUNCTIONS; returns pointer to bitmap
        bool loadBitmapDataFromCSV(string);//NEW FUNCTIONS
        bool loadAllAnimationDataFromCSV(string);//NEW FUNCTIONS
        bool loadAnimationDataFromCSV(string);//NEW FUNCTIONS
        bool loadBitmapsFromCSV(string);
        bool loadAnimationsFromCSV(string);
};
#endif
