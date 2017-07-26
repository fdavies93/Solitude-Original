#include "sol_logicController.h"
#include "sol_logicConstants.h"
using namespace std;

void sol_logicController::addObjectToActiveScene(string templateName, int templateType, double newX, double newY, string newLayer){
    sol_gameObject* newObject;
    switch (templateType){
        case GAME_OBJECT_STATIC_ANIMATION:
        {
            sol_templateStaticAnimation* newTemplate = storage.getStaticAnimation(templateName);
            assert(newTemplate != NULL);
            newObject = new sol_objectStaticAnimation(newTemplate,al_get_timer_count(timer));
        }
        break;
        case GAME_OBJECT_STATIC_BITMAP:
        {
            sol_templateStaticBitmap* newTemplate = storage.getStaticBitmap(templateName);
            assert(newTemplate != NULL);
            newObject = new sol_objectStaticBitmap(newTemplate,al_get_timer_count(timer));
        }
        break;
        default:
            cout << "Invalid object type in sol_logicController::addObjectToActiveScene.\n";
            return;
        break;
    }
    activeScene->addObject(newObject,newX,newY,newLayer);
}

void sol_logicController::addStaticAnimationTemplate(string templateName,string animationName, double width, double height){
    storage.addStaticAnimation(templateName,animationName,width,height);
}

void sol_logicController::addStaticBitmapTemplate(string templateName,string bitmapName, double width, double height){
    storage.addStaticBitmap(templateName,bitmapName,width,height);
}

sol_templateStaticAnimation* sol_logicController::getStaticAnimationTemplate(string templateName){
    return storage.getStaticAnimation(templateName);
}

sol_logicController::sol_logicController(ALLEGRO_TIMER* newTimer){
    timer = newTimer;
    activeScene = new sol_scene(20,20);
}
