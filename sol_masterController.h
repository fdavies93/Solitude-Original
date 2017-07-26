#ifndef _SOL_MASTER_CONTROLLER_DEFINED_
#define _SOL_MASTER_CONTROLLER_DEFINED_
#include "sol_logicToGraphicsConverter.h"
#include "sol_graphicsControl.h"
#include "sol_logicController.h"
using namespace std;

//contrary to what you might think, this is not exactly a 'master' controller. rather it performs all operations which must
//mediate between the graphics and logic subsystems and provides means for doing so
//it itself mediates between these subsystems and the hardware

class sol_masterController{
    private:
        sol_logicToGraphicsConverter *renderPipeline;
        sol_graphicsControl *graphicsController;
        sol_logicController *logicController;
        bool quit;
        bool redraw;
        ALLEGRO_EVENT curEvent;
        ALLEGRO_TIMER* timer;
        ALLEGRO_DISPLAY* display;
        ALLEGRO_EVENT_QUEUE* queue;
        void gameLoop();
    public:
        sol_masterController(unsigned int, unsigned int, unsigned int, unsigned int);//display width, display height, frames per second, pixels per metre
        void startGameLoop();
        void endGameLoop();
};

#endif
