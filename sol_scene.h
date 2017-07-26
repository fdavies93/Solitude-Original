#ifndef _SOL_SCENE_DEFINED_
#define _SOL_SCENE_DEFINED_
#include "sol_sceneLayer.h"
#include "sol_objectStaticAnimation.h"
#include "sol_objectStaticBitmap.h"
#include "sol_logicCamera.h"
#include "sol_spaceFillingVector.h"
#include <string>
#include <list>
using namespace std;

class sol_scene{//e.g. a stage, a screen
    private:
        double width, height;
        list <sol_sceneLayer*> layers;//the reason this is in logic as well as graphics is to make translation between the two easier
        spaceFillingVector <sol_objectStaticAnimation*> staticAnimations;
        spaceFillingVector <sol_objectStaticBitmap*> staticBitmaps;
        sol_logicCamera* activeCamera;//declared as a pointer for quick changing
    public:
        void changeActiveCamera(sol_logicCamera*);
        sol_logicCamera* getActiveCamera(){return activeCamera;};
        sol_scene(double,double);
        list <sol_sceneLayer*> getLayers(){return layers;};
        void addLayer(int, string, double, double);//depth, name, xScroll, yScroll
        void addStaticAnimation(sol_objectStaticAnimation*, double, double, string);//object, x, y, layer
        void addObject(sol_gameObject*, double, double, string);//object, x, y, layer
};

#endif
