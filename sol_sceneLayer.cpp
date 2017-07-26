#include "sol_sceneLayer.h"
using namespace std;

sol_sceneLayer::sol_sceneLayer(string newName, int newDepth, double newXScroll, double newYScroll){
    name = newName;
    depth = newDepth;
    horizontalScrollSpeed = newXScroll;
    verticalScrollSpeed = newYScroll;
}

void sol_sceneLayer::addObject(sol_gameObject* newObject){
    objectsPointed.addObject(newObject);
}
