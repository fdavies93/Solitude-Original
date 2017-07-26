#ifndef _GRAPHICS_CONTROL_DEFINED_
#define _GRAPHICS_CONTROL_DEFINED_
#include "sol_graphicsStorage.h"
#include "sol_graphicsLayer.h"
#include "sol_graphicsGroup.h"
#include "graphicsCache.h"
#include <vector>
#include <list>
using namespace std;

class sol_graphicsControl{
    private:
        list <sol_graphicsLayer*> layers;

    public:
    graphicsCache* cache;//back to private after test
        void addAnimation(string, string, int, int, int);//animation name, layer name, x, y, frame
        void addBitmap(string, string, int, int);//bitmap name, layer name, x, y
        void addLayer(int, string);//layer depth; layer name
        void clearLayers();//clears all layers etc.
        void nextFrame();
        void printFrame();
        animationData* getAnimationData(string);
        sol_graphicsControl(string, string);
};

#endif
