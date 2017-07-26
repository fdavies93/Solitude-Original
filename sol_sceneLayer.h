#ifndef _SOL_SCENE_LAYER_DEFINED_
#define _SOL_SCENE_LAYER_DEFINED_
#include <vector>
#include <string>
#include "sol_gameObject.h"
#include "sol_spaceFillingVector.h"
using namespace std;

class sol_sceneLayer{
    private:
        string name;
        int depth;
        spaceFillingVector <sol_gameObject*> objectsPointed;//objects stored seperately to allow for inter-layer collisions and movement between layers
        double horizontalScrollSpeed, verticalScrollSpeed;//how far it moves based on movement of camera
        //e.g. if horizontalScrollSpeed is 0.5, vertical 0.5 and the position of the camera is 200, 200 then it will print from (100,100)
    public:
        void addObject(sol_gameObject*);//new object
        spaceFillingVector <sol_gameObject*> *getAllObjects(){return &objectsPointed;};
        sol_sceneLayer(string,int,double,double);//name, depth, horizontalScrollSpeed, verticalScrollSpeed
        int getDepth(){return depth;};
        string getName(){return name;};
        double getHorizontalScrollSpeed(){return horizontalScrollSpeed;};
        double getVerticalScrollSpeed(){return verticalScrollSpeed;};
};

#endif
