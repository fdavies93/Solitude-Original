#include "sol_logicToGraphicsConverter.h"
#include "sol_logicConstants.h"
#include "sol_graphicsConstants.h"
#include "graphicsLoader.h"
using namespace std;

sol_logicToGraphicsConverter::sol_logicToGraphicsConverter(sol_graphicsControl* newGraphicsPointer, unsigned int ppm, ALLEGRO_TIMER* newTimer){
    graphicsPointer = newGraphicsPointer;
    pixelsPerMetre = ppm;
    timer = newTimer;
}

bool sol_logicToGraphicsConverter::buildGraphics(sol_scene* scenePointer){
    //data is
    graphicsPointer->clearLayers();
    list <sol_sceneLayer*> layers = scenePointer->getLayers();
	list<sol_sceneLayer*>::iterator i;
    sol_sceneLayer* curLayer;
    sol_logicCamera* theCamera = scenePointer->getActiveCamera();
    spaceFillingVector <sol_gameObject*> *layerObjects;//is this it? the leak? it seems probable
    sol_gameObject* curObject;

    string curObjectType;
    string curObjectLayer;
    int curObjectScreenX;
    int curObjectScreenY;
    int curObjectFrame;

    sol_objectStaticAnimation* thisAnimation;
    sol_objectStaticBitmap* thisBitmap;

    for(i = layers.begin(); i != layers.end(); i++){
        curLayer = *i;
        //cout << curLayer->getName() << "\n";
        graphicsPointer->addLayer(curLayer->getDepth(),curLayer->getName());
        layerObjects = curLayer->getAllObjects();
        for(int i2 = 0; i2 < layerObjects->size(); i2++){
            if(layerObjects->spaceFull(i2)){
                curObject = layerObjects->getObject(i2);

                //adjusting for the 'special case' of a 0.0 parallax
                //in this case the position should be taken as the position on screen
                if(curLayer->getHorizontalScrollSpeed()){
                    curObjectScreenX = ((curObject->x * pixelsPerMetre) - (theCamera->x * pixelsPerMetre)) * curLayer->getHorizontalScrollSpeed();
                }
                else{
                    curObjectScreenX = curObject->x * pixelsPerMetre;//does not move relative to screen
                }
                if(curLayer->getVerticalScrollSpeed()){
                    curObjectScreenY = ((curObject->y * pixelsPerMetre) - (theCamera->y * pixelsPerMetre)) * curLayer->getVerticalScrollSpeed();
                }
                else{
                    curObjectScreenY = curObject->y * pixelsPerMetre;//does not move relative to screen
                }

                if(curObjectScreenX < theCamera->width * pixelsPerMetre * 2
                   && curObjectScreenX + curObject->getWidth() >= -theCamera->width
                   && curObjectScreenY < theCamera->height * pixelsPerMetre * 2
                   && curObjectScreenY + curObject->getHeight() >= -theCamera->height){
                //if object is within 2 cameras of view
                //cache the graphics
                    switch (curObject->getSuperType()){
                        case GAME_OBJECT_STATIC_ANIMATION:
                            thisAnimation = (sol_objectStaticAnimation*) curObject;
                            curObjectType = thisAnimation->getType()->getAnimationName();
                            graphicsPointer->cache->cacheAnimation(curObjectType);
                        break;
                        case GAME_OBJECT_STATIC_BITMAP:
                            thisBitmap = (sol_objectStaticBitmap*) curObject;
                            curObjectType = thisBitmap->getType()->getBitmapName();
                            graphicsPointer->cache->cacheBitmap(curObjectType);
                        break;
                    }
                }

                curObjectLayer = curLayer->getName();

                if((curObjectScreenX < theCamera->width * pixelsPerMetre
                   && curObjectScreenX + curObject->getWidth() >= 0)
                   && curObjectScreenY < theCamera->height * pixelsPerMetre
					&& curObjectScreenY + curObject->getHeight() >= 0){
                    switch (curObject->getSuperType())//note: the functions that add by name may cause bottlenecking
                    {
                        case GAME_OBJECT_STATIC_ANIMATION:
                            curObjectFrame = (al_get_timer_count(timer) - thisAnimation->getTickCreated()) % (graphicsPointer->getAnimationData(thisAnimation->getType()->getName())->getNumberOfFrames());//another possible bottleneck
                            graphicsPointer->addAnimation(curObjectType,curObjectLayer,curObjectScreenX,curObjectScreenY,curObjectFrame);//leaking here
                            //graphicsPointer->printFrame();
                            //al_flip_display();
                        break;
                        case GAME_OBJECT_STATIC_BITMAP:
                            //curObjectScreenX = ((thisBitmap->x * pixelsPerMetre) - (theCamera->x * pixelsPerMetre)) * curLayer->getHorizontalScrollSpeed();
                            //curObjectScreenY = ((thisBitmap->y * pixelsPerMetre) - (theCamera->y * pixelsPerMetre)) * curLayer->getVerticalScrollSpeed();
                            graphicsPointer->addBitmap(curObjectType,curObjectLayer,curObjectScreenX,curObjectScreenY);
                        break;
                    }
                }
            }
        }
    }
    //graphicsPointer->printFrame();
    //graphicsPointer->cache->loader->addMessage(GRAPHICS_MESSAGE_TEST,NULL);
    //cout << "stopped\n";
    while(!graphicsPointer->cache->messagesEmpty()){
        graphicsPointer->cache->runNextMessage();
    }
    graphicsPointer->cache->loader->activate();
    graphicsPointer->cache->uncacheDead();
    graphicsPointer->cache->sweepNumOnScreen();

    //cout << "stopped\n";
}
