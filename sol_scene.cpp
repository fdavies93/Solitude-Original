#include "sol_scene.h"
#include "sol_logicConstants.h"
#include <iostream>
using namespace std;

sol_scene::sol_scene(double newWidth, double newHeight){
    width = newWidth;
    height = newHeight;
    activeCamera = new sol_logicCamera;
    activeCamera->x = 0;
    activeCamera->y = 0;
    activeCamera->width = 10;
    activeCamera->height = 10;
    //activeCamera = &newCamera;
}

void sol_scene::changeActiveCamera(sol_logicCamera* newCamera){
    delete activeCamera;
    activeCamera = newCamera;
}

void sol_scene::addLayer(int depth, string name, double xScroll, double yScroll){
	list<sol_sceneLayer*>::iterator i;
    sol_sceneLayer* curLayer;
    for(i = layers.begin(); i != layers.end(); i++){
        curLayer = *i;
        if(curLayer->getDepth() == depth){
            cout << "Can't add layer at same depth twice in sol_scene::addLayer.\n";
            return;
        }
        if(curLayer->getDepth() > depth){
            if(i != layers.end()){
                layers.insert(i, new sol_sceneLayer(name,depth,xScroll,yScroll));
                return;
            }
        }
    }
    layers.push_back(new sol_sceneLayer(name,depth,xScroll,yScroll));
    return;
}

void sol_scene::addObject(sol_gameObject* newObject, double newX, double newY, string newLayer){
    newObject->x = newX;
    newObject->y = newY;
    switch(newObject->getSuperType()){
        case GAME_OBJECT_STATIC_ANIMATION:
            newObject->setId(staticAnimations.addObject((sol_objectStaticAnimation*)newObject));
        break;
        case GAME_OBJECT_STATIC_BITMAP:
            newObject->setId(staticBitmaps.addObject((sol_objectStaticBitmap*)newObject));
        break;
    }
	list<sol_sceneLayer*>::iterator i;
    sol_sceneLayer* curLayer;
    for(i = layers.begin(); i != layers.end(); i++){
        curLayer = *i;
        if(curLayer->getName() == newLayer){
            //cout << newObject->getWidth() << "\n";
            curLayer->addObject(newObject);
            return;
        }
    }
    cout << "Failed to add animation to " << newLayer << "in sol_scene::addStaticAnimation.\n";
}
