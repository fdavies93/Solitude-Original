#include "sol_graphicsControl.h"
#include <iostream>
#include <list>
using namespace std;

sol_graphicsControl::sol_graphicsControl(string animationFile, string bitmapFile){
    cache = new graphicsCache(animationFile, bitmapFile);
}

void sol_graphicsControl::addLayer(int depth, string name){
	list<sol_graphicsLayer*>::iterator i;
    sol_graphicsLayer* curLayer;
    for(i = layers.begin(); i != layers.end(); i++){
        curLayer = *i;
        if(curLayer->getDepth() == depth){
            cout << "Can't add layer at same depth twice in sol_graphicsControl::addLayer.\n";
            return;
        }
        if(curLayer->getDepth() > depth){
            if(i != layers.end()){
                layers.insert(i, new sol_graphicsLayer(name,depth));
                return;
            }
        }
    }
    layers.push_back(new sol_graphicsLayer(name,depth));
    return;
}

void sol_graphicsControl::addAnimation(string animName, string layerName, int newX, int newY, int frame){
    //does this for each INDIVIDUAL animation on screen rather than each TYPE of animation
	list<sol_graphicsLayer*>::iterator i;
    sol_graphicsLayer* curLayer;
    animation* curAnim;
    curAnim = cache->getAnimation(animName);
    if(curAnim){
        //needs protection against crashing when loading
        for(i = layers.begin(); i != layers.end(); i++){
            curLayer = *i;
            if(curLayer->getName() == layerName){
                if(curAnim){
                    curLayer->addAnimation(new sol_screenAnimation(curAnim,newX,newY,frame));//leak here
                }
                return;
            }
        }
    }
    return;
}

void sol_graphicsControl::addBitmap(string bmpName, string layerName, int newX, int newY){
	list<sol_graphicsLayer*>::iterator i;
    sol_graphicsLayer* curLayer;
    sol_screenBitmap* objectToAdd;
    sol_bitmap* curBitmap = NULL;
    //cache->cacheBitmap(bmpName);
    for(i = layers.begin(); i != layers.end(); i++){
        curLayer = *i;
        if(curLayer->getName() == layerName){
            curBitmap = cache->getBitmap(bmpName);
            assert(curBitmap);
            //cout << "addBitmap; Name: " << bmpName << ", Address: " <<  curBitmap << "\n";
            objectToAdd = new sol_screenBitmap(curBitmap,newX,newY);
            curLayer->addBitmap(objectToAdd);
            return;
        }
    }
    cout << "Could not add bitmap " << bmpName << " to layer " << layerName << " in sol_graphicsControl::AddBitmap.\n";
    return;
}

void sol_graphicsControl::printFrame(){
	list<sol_graphicsLayer*>::iterator i;
    sol_graphicsLayer* curLayer;
    for(i = layers.begin(); i != layers.end(); i++){
        curLayer = *i;
        curLayer->print();
    }
}

void sol_graphicsControl::clearLayers(){
	list<sol_graphicsLayer*>::iterator i;
    sol_graphicsLayer* curLayer;
    for(i = layers.begin(); i != layers.end(); i++){
        curLayer = *i;
        curLayer->clearLayer();
        delete curLayer;
    }
    layers.clear();
}

animationData* sol_graphicsControl::getAnimationData(string myName){
    return cache->getAnimationData(myName);
}
