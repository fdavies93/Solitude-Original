#ifndef _SOL_LOGIC_CONTROLLER_DEFINED_
#define _SOL_LOGIC_CONTROLLER_DEFINED_
#include "sol_scene.h"
#include "sol_logicStorage.h"
//include #sol_logicEventQueue
using namespace std;

class sol_logicController{
    private:
        //sol_logicEventQueue queue;//situating it outside the active scene allows for
        //pending scenes - to be loaded in another thread
        sol_logicStorage storage;
        ALLEGRO_TIMER* timer;
        sol_templateStaticAnimation* getStaticAnimationTemplate(string);
    public:
        void addStaticAnimationTemplate(string,string, double, double);//template name, animation name, width, height
        void addStaticBitmapTemplate(string, string, double, double);//template name, bitmap name, width, height
        void addObjectToActiveScene(string, int, double, double, string);//template name, object type, x, y, layer
        sol_scene* activeScene;
        sol_logicController(ALLEGRO_TIMER*);

};

#endif
